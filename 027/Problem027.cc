#include <iostream>
#include <cstdlib>
#include <string.h>
using namespace std;

/*
 * Project Euler: Problem 027 (http://projecteuler.net/problem=27)
 */

// Q(n) = n^2 + a.n + b such as |a| and |b| < 1000
// L(Q) = l such as Q(0),Q(1),...,Q(l) all primes.
// Find max L(Q)
//
// Q(0)=b => b prime b >= 2
// Q(1)=1+a+b prime => 1+a+b >= 3 a >= 2 - b
// Q(b-a)=(b-a)^2+a(b-a)+b = b^2-ab+b = b(b-a+1)
// So L(Q) <= b-a
// L(n^2+n+41) = 40 so only look for L(Q) > 40
// or b-a > 40 or a < b - 40
// a >= 2 - b so -a <= b - 2 => b-a <= 2(b-1)
//
// Max( b - a ) < 2000 => max Q(b-a)=b(b-a+1) < 2000000
// Calculate all primes under 2000000 (see problem 10) via sieve.
//
// So: pick b prime < 1000 
// max_L (initialised to 40)
// 2-b < b-max_L <=> 2b > max_L+2 <=> b > (max_L/2)+1 (floor for b)
// Make a vary from 2-b <= a < b - max_L
// Q(0) = b and Q(n+1) = Q(n) + 2n + 1 + a and check if prime

// 2000000 elements sieve
static char sieve[250001];

static inline bool checkPrime( long long p )
{
    return ( ( p >= 2 ) && ! ( sieve[p/8+(p%8==0?1:0)] & ( 1 << ( p%8 ) ) ) );
}

int findNextPrime( int p )
{
    int np = 0;
    if ( p > 2 ) {
        np = p-1;
        while( ! checkPrime( np ) ) --np;
    }
    return np;
}

void makePrimeSieve( int n )
{
    cout << "Creating prime sieve..." << endl;
    memset( sieve, 0, 250001 );
    for( int i = 2; i < 1000000; ++i ) {
        for( int j = 2; i*j < n; ++j ) {
            int mul = i*j;
            sieve[ ( mul / 8 ) + ( ( mul % 8 ) == 0 ? 1 : 0 ) ] |= 
                1 << ( mul % 8 );
        }
    }
}

// Q(n+1)=n^2+2n+1+an+a+b = Q(n)+2n+1+a
int nprimes( int a, int b )
{
    long long q = b;
    int n = 0;
    for( n = 0; ( n <= ( b - a ) ) && checkPrime( q ); ++n ) {
        q += n + n + 1 + a;
    }
    return n;
}

int main( int argc, char** argv )
{
    makePrimeSieve( 2000000 );
    cout << "Test: L(Q(1,41)) = " << nprimes(1,41) << endl;

    int max_l = 40;
    int max_b = 41;
    int max_a = 1;

    int b = findNextPrime( 1000 );
    while( b > ( ( max_l / 2 ) + 1 ) ) {
        for( int a = 2-b; a < (b-max_l); ++a ) {
            int l = nprimes( a, b );
            //cout << "nprimes(" << a << "," << b << ") = " << l << endl;
            if ( l > max_l ) {
                cout << "New max: "<< l <<" ("<< a <<","<< b <<")"<< endl;
                max_l = l;
                max_a = a;
                max_b = b;
            }
        }
        b = findNextPrime( b );
    }

    cout << "Max L(Q) = " << max_l << " a = " << max_a << " b = " << max_b
         << " a.b = " << max_a*max_b << endl;
    cout << "Answer: " << max_a*max_b << endl;
    return 0;
}
