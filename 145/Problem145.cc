#include <iostream>
#include <cstdlib>

using namespace std;

unsigned int reverse( unsigned int n )
{
    unsigned int m = 0;
    while( n > 0 )
    {
        m *= 10;
        m += n % 10;
        n /= 10;
    }
    return m;
}

bool all_odd_digits( unsigned int n )
{
    bool r = true;
    while( ( n > 0 ) && r )
    {
        char d = n % 10;
        r = ( d % 2 != 0 );
        n /= 10;
    }
    return r;
}

int main( int argc, char** argv )
{
    unsigned int limit = 1000000000;
    if ( argc > 1 ) limit = atoi( argv[ 1 ] );

    unsigned int count = 0;
    unsigned int n = 12;
    while( n < limit )
    {
        if ( n % 10 != 0 )
        {
            unsigned int s = n + reverse( n );
            if ( all_odd_digits( s ) )
            {
                count += 2;
            }
        }
        n += 2;
    }
    cout << "Number of reversible numbers below " << limit << "=" << count
         << endl;
    return 0;
}
