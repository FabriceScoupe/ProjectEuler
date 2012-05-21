#include <iostream>
#include <cstdlib>

using namespace std;

/*
 * Project Euler: Problem 85 (http://projecteuler.net/problem=85)
 */

// By counting carefully it can be seen that a rectangular grid measuring
// 3 by 2 contains eighteen rectangles:
// Although there exists no rectangular grid that contains exactly two million
// rectangles, find the area of the grid with the nearest solution.

// Think in degrees of freedom:
// In an m * n grid, a rectangle of dimension i * j can "move" (m - i) times
// horizontally and (n - j) times vertically. All in all (m - i)*(n - j)+1
// ways to position the rectangle in the grid.
// So count = sum[ i=1..m, j = 1..n] ((m-i)*(n-j)+1)
//          = (sum[ i=0..m-1, j = 0..n-1 ] i*j) + m*n
// So:
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
    int best_x = 0;
    int best_y = 0;
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
            best = c; best_x = x; best_y = y;
        }
    }
    cout << "Answer: " << best_x*best_y << endl;
    return 0;
}
