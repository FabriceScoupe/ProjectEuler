#include <iostream>
#include <cstdlib>
#include <string.h>

using namespace std;

/***
A composite is a number containing at least two prime factors.
For example, 15 = 3 × 5; 9 = 3 × 3; 12 = 2 × 2 × 3.

There are ten composites below thirty containing precisely two,
not necessarily distinct, prime factors:
4, 6, 9, 10, 14, 15, 21, 22, 25, 26.

How many composite integers, n < 10^(8), have precisely two,
not necessarily distinct, prime factors?
***/

char sieve[ 3125001 ]; // to detect all primes up to <50000000

void buildSieve()
{
    cout << "Building sieve..." << endl;
    memset( sieve, 0, 3125001 );
    long long iter = 0;
    for( long long i = 3; i <= 16666666; i+=2 )
    {
        for( long long j = 3; i*j <= 50000000; j += 2 )
        {
            if ( ++iter % 1000000 == 0 ) { cout << "."; flush( cout ); }
            long long m = (i*j)/2;
            sieve[ m/8+(m%8?0:1) ] |= 1<<(m%8);
        }
    }
    cout << endl;
}

bool isPrime( long long p );

long long nextPrime( long long p )
{
    if ( 2 == p ) return 3;
    long long q = p+2;
    while( ( q < 50000000 ) && ( !isPrime( q ) ) ) q+=2; // not subtle.
    if ( q >= 50000000 ) q = -1;
    return q;
}

bool isPrime( long long p )
{
    long long q = p / 2;
    return ( ( 2 == p ) ||
             ( ( p % 2 ) && ! ( sieve[q/8+(q%8?0:1)] & 1<<(q%8) ) ) );
}



int main( int argc, char** argv )
{
    int limit = 100000000;
    if ( argc > 1 ) limit = atoi( argv[ 1 ] );
    buildSieve();
    int count = 0;
    int a = 2;
    int b = 2;
    do
    {
        do
        {
            ++count;
            b = nextPrime( b );
        }
        while( ( b > 0 ) && ( a*b < limit ) );
        a = nextPrime( a );
        b = a;
    }
    while( ( a > 0 ) && ( a*b < limit ) );
    cout << "Number of semi-primes < " << limit << " = " << count << endl;
}
