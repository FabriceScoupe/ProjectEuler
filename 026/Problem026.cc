#include <iostream>
#include <cstdlib>
#include <map>
using namespace std;

// Find value of d < 1000 for which 1/d has longest recurring cycle

int cycle( int n )
{
    int p = 10;
    int r = 0;
    int c = 0;
    map<int,int> m;
    cout << "1/" << n << " = 0.";
    while( p / n == 0 ) { cout << '0'; p*= 10; }
    do
    {
        int d = p / n; // digit
        cout << d;
        ++c;
        if ( d > 0 )
        {
            r = p % n;
            if ( m[r] > 0 ) // found cycle?
            {
                --c;
                break;
            }
            else
            {
                m[r] = c;
            }
            p = r;
        }
        p *= 10;
    }
    while( r > 0 );
    if ( r > 0 )
    {
        cout << "...";
    }
    else
    {
        c = 0; // No recurring cycle
    }
    cout << " cycle = " << c << endl;
    return c;
}


int main( int argc, char** argv )
{
    int n = 1000;
    if ( argc > 1 ) n = atoi( argv[1] );
    int max   = 0;
    int max_i = 0;
    for( int i = 2; i < n; ++i )
    {
        int c = cycle( i );
        if ( c > max ) { max = c; max_i = i; }
    }

    cout << endl << "1/" << max_i << " has longest cycle: " << max << endl;
}
