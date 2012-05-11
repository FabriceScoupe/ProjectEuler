#include <iostream>
#include <cstdlib>
#include <map>

using namespace std;

// A number chain is created by continuously adding the square of the digits
// in a number to form a new number until it has been seen before.
// For example,
// 44 -> 32 -> 13 -> 10 -> 1 -> 1
// 85 -> 89 -> 145 -> 42 -> 20 -> 4 -> 16 -> 37 -> 58 -> 89

// Memoisation of series' limit.

int main( int argc, char** argv )
{
    int limit = 10000000;
    if ( argc > 1 ) limit = atoi( argv[ 1 ] );

    int count = 0;
    map<int,int> limits;

    for( int i = 1; i < limit; ++i )
    {
        if ( i % 10000 == 0 ) { cout << '.'; flush( cout ); }
        int n = i;
        int l = 0;
        do
        {
            l = limits[ n ];
            if ( l ) break;
            int s = 0;
            while( n )
            {
                char d = n % 10;
                s += d*d;
                n /= 10;
            }
            n = s;
        }
        while( ( n != 1 ) && ( n != 89 ) );
        if ( 0 == l ) l = n;
        limits[ i ] = l;
        if ( 89 == l ) ++count;
    }
    cout << endl;
    cout << count << " numbers below " << limit << " arrive at 89.";
    cout << endl;
}
