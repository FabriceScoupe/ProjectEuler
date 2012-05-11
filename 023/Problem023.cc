#include <iostream>
#include <cstdlib>
#include <vector>
#include <string.h>
using namespace std;

// Sum of all positive integers which cannot be written as the sum of
// two abundant numbers.
// Abundant <=> greater than the sum of its divisors

int root( int n )
{
    int r = 1;
    while( r*r < n ) ++r;
    return r;
}

int sum_divs( int n )
{
    int sum = 1;
    int r = root(n);
    for( int d = 2; d < r; ++d ) if ( n % d == 0 ) sum += d + n/d;
    if ( n == r*r ) sum += r;
    return sum;
}

// Find abundant numbers up to (and including) n
// We know that 12 smallest one, so...
void find_abundant( int n, vector<int>& abundants )
{
    for( int i = 12; i <= n; ++i )
    {
        int sd = sum_divs(i);
        if ( i < sd )
        {
            abundants.push_back(i);
            //cout << "Found abundant number: " <<  i << " < " << sd << endl;
        }
    }
    //cout << endl;
}

int main( int argc, char** argv )
{
    int n = 28123;
    if ( argc > 1 ) n = atoi( argv[1] );
    if ( n < 24 ) n = 24;

    //cout << "Test: sum proper divisors( 12 ) = " << sum_divs( 12 ) << endl;
    //cout << "Test: sum proper divisors( 28 ) = " << sum_divs( 28 ) << endl;

    vector<int> a;
    find_abundant( n, a );
    //cout << a.size() << " abundant numbers found." << endl;

    // allocate sieve
    char* sieve = new char [ ( n / 4 ) + 1 ];
    memset( sieve, 0, ( n / 4 ) + 1 );

    // "Tick" all possible sums in sieve
    //cout << endl << "Building up sieve:" << endl;

    for( vector<int>::iterator i1 = a.begin(); i1 != a.end(); ++i1 )
    {
        for( vector<int>::iterator i2 = a.begin(); i2 != a.end(); ++i2 )
        {
            int s = *i1 + *i2;
            //if ( s % 10000 == 0 ) { cout << '.'; flush( cout ); }
            sieve[ s / 8 + ( s % 8 ? 1 : 0 ) ] |= 1 << ( s % 8 );
        }
    }
    //cout << endl;

    // Sum all "ticked" integers in sieve
    //cout << endl << "Walking sieve..." << endl;
    long long sum = 0;
    for( int i = 1; i <= n; ++i )
    {
        int pos = i / 8 + ( i % 8 ? 1 : 0 );
        if ( 0 == ( sieve[ pos ] & ( 1 << ( i % 8 ) ) ) )
        {
            sum += i;
            //cout << " + " << i << endl;
        }
    }

    cout << "Sum: " << sum << endl;

    delete[] sieve;
}
