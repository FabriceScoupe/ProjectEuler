#include <iostream>
#include <cstdlib>
#include <vector>
#include <map>
#include <string.h>
using namespace std;

// How many circular primes below one million?
// Circular prime: all rotations of digits --> also prime numbers

char sieve[125001];

void BuildSieve()
{
    cout << "Building sieve..." << endl;
    memset( sieve, 0, 125001);

    for( int i=2; i <= 500000; ++i )
    {
        for( int j = 2; i*j <= 1000000; ++j )
        {
            int m = i*j;
            sieve[ m/8 + ( m%8 ? 0 : 1 ) ] |= 1<<(m%8);
        }
    }
}

bool checkPrime( int p )
{
    return ( ( sieve[ p/8 + ( p%8 ? 0 : 1 ) ] & (1<<(p%8))) == 0 );
}

int power10( char n )
{
    int p = 1;
    switch( n )
    {
        case 1: p=10; break;
        case 2: p=100; break;
        case 3: p=1000; break;
        case 4: p=10000; break;
        case 5: p=100000; break;
        case 6: p=1000000; break;
        case 7: p=10000000; break;
        default: break;
    }
    return p;
}

void getDigits( int p, vector<char>& dv )
{
    int n = p;
    dv.clear();
    while( n > 0 )
    {
        dv.push_back( n % 10 );
        n /= 10; 
    }
}

bool checkCircularPrime( int p )
{
    bool ok = checkPrime( p );
    if ( ok )
    {
        vector<char> dv;
        getDigits( p, dv );
        char nd = dv.size();
        for( char s = 1; ( s < nd ) && ok ; ++s )
        {
            int q = 0;
            for( char t = 0; t < nd; ++t )
            {
                q += power10( t )*dv[(t+s)%nd];
            }
            ok = checkPrime( q );
        }
    }
    //if ( ok ) cout << "Found: " << p << endl;
    return ok;
}

int main( int argc, char** argv )
{
    int n = 1000000;
    if ( argc > 1 ) n = atoi( argv[1] );
    BuildSieve();

    int count = 0;
    if ( checkCircularPrime( 2 ) ) ++count;
    for( int i = 3; i < n; i += 2 ) if ( checkCircularPrime( i ) ) ++count;
    cout << "Found "  << count << " circular primes under " << n << endl;
}
