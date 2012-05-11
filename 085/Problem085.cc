#include <iostream>
#include <cstdlib>

using namespace std;

// By counting carefully it can be seen that a rectangular grid measuring
// 3 by 2 contains eighteen rectangles:
// Although there exists no rectangular grid that contains exactly two million
// rectangles, find the area of the grid with the nearest solution.

// count = sum[ i=1..m, j = 1..n] i*j
//       = sum[ i=1..m ] i * sum[ j = 1..n ] j
//       = m*(m+1)*n*(n+1)/4

int count_rectangles( int m, int n )
{
   return (m*(m+1)*n*(n+1)/4);
}

int main( int argc, char** argv )
{
    int target = 2000000;
    if ( argc > 1 ) target = atoi( argv[ 1 ] );

    //cout << "For 2 by 3 => " << count_rectangles( 2, 3 ) << endl;

    int r = 1;
    int c = 1;
    while( c < target )
    {
        ++r;
        c = count_rectangles( r, r );
    }

    cout << r << " x " << r << " (" << r*r << ") => " << c << endl;

    int best = c;
    int x = r;
    int y = r;

    while( ( c != target )&& ( x > 1 ) )
    {
        if ( c > target )
        {
            --x;
        }
        else
        {
            ++y;
        }
        c = count_rectangles( x, y );
        if ( abs( c - target ) < abs( best - target ) )
        {
            cout << x << " x " << y << " (" << x*y<< ") => " << c << endl;
            best = c;
        }
    }
}
