#include <iostream>
#include <cstdlib>
#include <string.h>
using namespace std;

// Sum of all primes < n

char* sieve = NULL;

int main( int argc, char** argv )
{
    int n = 2000000;
    if ( argc > 1 ) n = atoi( argv[1] );

    // Allocate sieve, ( n / 8 + 1 ) bytes
    sieve = new char[ ( n / 8 ) + 1 ];
    memset( sieve, 0, ( n / 8 ) + 1 );

    // Create sieve
    for( int i = 2; i <= n/2; ++i )
    {
        for( int j = 2; i*j <= n; ++j )
        {
            int mul = i*j;
            int pos = mul / 8 + ( mul % 8 ? 1 : 0 );
            sieve[ pos ] |= 1 << ( mul % 8 );
        }
    }

    // Check & Sum
    long long sum = 0;
    for( int i = 2; i <= n; ++i )
        if ( ! ( sieve[ i / 8 + ( i % 8 ? 1 : 0 ) ] & ( 1 << ( i % 8 ) ) ) )
        {
            sum += i;
            //cout << i << endl;
        }

    cout << endl << "Sum of all primes < " << n << " = " << sum << endl;
}
