#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <string.h>
#include <map>
using namespace std;

// Which prime below one million can be written as the sum of the
// most consecutive primes?

char sieve[ 62501 ];

void buildSieve()
{
    memset( sieve, 0, 62501 );
    for( int i = 3; i <= 333333; i+=2 )
    {
        for( int j = 3; i*j <= 1000000; j += 2 )
        {
            int m = i*j/2;
            sieve[ m/8+(m%8?0:1) ] |= 1<<(m%8);
        }
    }
}

bool isPrime( int p )
{
    int q = p / 2;
    return( ( 2 == p ) ||
            ( ( p % 2 ) && ! ( sieve[q/8+(q%8?0:1)] & 1<<(q%8) ) ) );
}

int nextPrime( int p )
{
    int q = p+1;
    while( ( q < 1000000 ) && ( !isPrime( q ) ) ) ++q; // not subtle.
    if ( q >= 1000000 ) q = -1;
    return q;
}

int main( int argc, char** argv )
{
    int n = 1000000;
    if ( argc > 1 ) n = atoi( argv[ 1 ] );
    buildSieve();
    int max_count = 1;
    int max_prime = 2;
    for( int p = 2; ( p > 0 ) && ( p < n ); p = nextPrime( p ) )
    {
        int count = 1;
        int sum = p;
        int q = p;
        while( ( q > 0 ) && ( sum < n ) )
        {
            if ( isPrime( sum ) && ( count > max_count ) )
            {
                max_count = count;
                max_prime = sum;
                //cout << sum << " (" << count << " from " << p << ")" << endl;
            }
            q = nextPrime( q );
            ++count;
            sum += q;
        }
    }
    cout << max_prime << " (" << max_count << " primes)" << endl;
    return 0;
}
