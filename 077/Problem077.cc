#include <iostream>
#include <cstdlib>
#include <vector>
using namespace std;

/*
 * Project Euler: Problem 077 (http://projecteuler.net/problem=77)
 */

// It is possible to write ten as the sum of primes in exactly five
// different ways:
// 7 + 3
// 5 + 5
// 5 + 3 + 2
// 3 + 3 + 2 + 2
// 2 + 2 + 2 + 2 + 2
// What is the first value which can be written as the sum of primes
// in over five thousand different ways?

// Same idea as for prob. 76, use generating functions, here:
// GF(p)(x)=Prod[ prime i ] (1 - x^i)^(-1)
// Remember that:
// (1-x^i)^(-1) = sum[k >= 0] x^(i*k)
// GF2(p)=1/(1-x^2)= 1+x^2+x^4+x^6+x^8+...  [1,0,1,0,1,0,1,0,1,...]
// GF3(p)=1/(1-x^3)= 1+x^3+x^6+x^9+x^12+... [1,0,0,1,0,0,1,0,0,1,...]
// GF2(p).GF3(p)=1+x^2+x^3+x^4+x^5+2.x^6+x^7+2.x^8+...
// General rules for multiplication of power series:
// S1(x) = sum[k>=0] Ak.x^k
// S2(x) = sum[k>=0] Bk.x^k
// P(x)=S1(x).S2(x)=sum[k>=0]Ck.x^k
// Ck = sum[0<=j<=k] Aj.Bk-j
// 

void buildPrimes( int limit, vector<int>& p )
{
    p.clear();
    p.push_back( 2 );
    for( int n = 3; n <= limit; n+= 2 )
    {
        bool is_prime = true;
        for(unsigned int r = 0;
            is_prime && ( r < p.size() ) && (p[r]*p[r] <= n); ++r) {
           is_prime = (n % p[r] != 0);
        }
        if (is_prime) {
            //cout << n << " is prime." << endl;
            p.push_back( n );
        }
    }
};

void multiply_series( int dim, int* a, int* b, int* c )
{
    for(int k = 0; k < dim; ++k) {
        c[ k ] = 0;
        for( int j = 0; j <= k; ++j ) c[ k ] += a[ j ]* b[ k - j ];
    }
}

int main( int argc, char** argv )
{
    int n = 5000;
    if ( argc > 1 ) n = atoi( argv[ 1 ] );

    int a[ 100 ];
    int b[ 100 ];
    int c[ 100 ];

    int* p1 = a;
    int* p2 = c;
    int* tmp;

    for( int i = 0; i < 100; ++i ) {
        a[ i ] = 0;
        b[ i ] = 0;
    }

    a[ 0 ] = 1;

    vector<int> primes;
    buildPrimes( 10000, primes );
    for(unsigned int p = 0; p < primes.size(); ++p ) {
        for( int i = 0; i < 100; ++i ) b[ i ] = ( i % primes[p] ? 0 : 1 );
        multiply_series( 100, p1, b, p2 );
        tmp = p1; p1 = p2; p2 = tmp; // swap p1 and p2
    }

    unsigned int value = 0;
    while((value < 100) && (p1[value] <= n)) {
        //cout << "p(" << value << ")= " << p1[value] << endl;
        ++value;
    }
    cout << "Value is " << value << "(" << p1[value] << " ways)" << endl;
    cout << "Answer: " << value << endl;

    return 0;
}
