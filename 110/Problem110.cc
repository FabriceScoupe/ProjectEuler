#include <iostream>
#include <cstdlib>
#include <vector>
#include <map>
#include <cmath>

using namespace std;

/***
In the following equation x, y, and n are positive integers.
1/x+1/y=1/n

It can be verified that when n = 1260 there are 113 distinct solutions and
this is the least value of n for which the total number of distinct solutions
exceeds one hundred.

What is the least value of n for which the number of distinct solutions
exceeds four million?

NOTE: This problem is a much more difficult version of problem 108 and as it
is well beyond the limitations of a brute force approach it requires a clever
implementation.
***/

// See 108: number of solutions for n = (numdiv(n^2)+1)/2
// (number of divisors of n^2 which are <= n).
// if n = Prod[k] Pk^mk (prime factor decomposition)
// numdiv(n^2)=Prod[k](1+2*mk)
// So we are looking for n such as: Prod[k](1+2*mk) > 2*limit-1
// log n = Sum[k] mk.log Pk.
// Find min log n, ie min Sum[k] mk.log Pk, with Prod[k](1+2*mk) > 2*limit-1
// 3^(ceiling log3 2*limit-1) gives an initial n (all mk = 1)

static vector< int > primes;

void buildPrimes( int limit )
{
    cout << "Building primes up to " << limit << "..." << endl;
    primes.push_back( 2 );
    for( int n = 3; n <= limit; n += 2 )
    {
        bool is_prime = true;
        for( int i = 0; is_prime && ( i < (int) primes.size() ); ++i )
        {
            is_prime = ( n % primes[i] != 0 );
        }
        if ( is_prime ) primes.push_back( n );
    }
}

// Returns ceiling log3 n
int log3( int n )
{
    int l = 0;
    while( n > 0 ) { n /= 3; ++l; }
    return l;
}

void dumpProd( int prod, map<int,int>& m )
{
    cout << "prod = ";
    for( map<int,int>::iterator i=m.begin(); i!=m.end(); ++i )
        if ( i->second > 0 ) cout << i->first << "^" << i->second << " ";
    cout << "=" << prod << endl;
}

int main( int argc, char** argv )
{
    int limit = 4000000;
    if ( argc > 1 ) limit = atoll( argv[ 1 ] );
    buildPrimes( 1000 );
    int limit2 = 2*limit - 1;
    map<int,int> m;
    m[3] = log3( limit2 ); // Initial number of primes
    int prod = 1;
    for( int i = 0; i < m[3]; ++i ) prod *= 3;
    dumpProd( prod, m );
    while( ( m[3] >= 3 ) && ( prod / 27 * 25 > limit2 ) )
    {
        m[3] -= 3; m[5] += 2;
        prod /= 27; prod *= 25;
    }
    dumpProd( prod, m );
    while( ( m[5] >= 5 ) && ( prod / 3125 * 2401 > limit2 ) )
    {
        m[5]-=5; m[7]+=4;
        prod /= 3125; prod *= 2401;
    }
    dumpProd( prod, m );
    while( ( m[5] >= 5 ) && ( prod / 3125 * 3087 > limit2 ) )
    {
        m[5]-=5; m[7]+=3; ++m[9];
        prod /= 3125; prod *= 3087;
    }
    dumpProd( prod, m );
}
