#include <iostream>
#include <cstdlib>

using namespace std;

/*
 * Project Euler: Problem 094 (http://projecteuler.net/problem=94)
 */

/***
It is easily proved that no equilateral triangle exists with integral length
sides and integral area. However, the almost equilateral triangle 5-5-6 has an
area of 12 square units.

We shall define an almost equilateral triangle to be a triangle for which two
sides are equal and the third differs by no more than one unit.

Find the sum of the perimeters of all almost equilateral triangles with
integral side lengths and area and whose perimeters do not exceed one billion
(1,000,000,000).
***/

// Calculating area of triangle given sides? 2 sides equal a-a-b
// base is b, height -> h such as h^2+(b/2)^2 = a^2
// h = sqrt( a^2 - (b/2)^2 )
// Area = b * h / 2 = b/2*sqrt( a^2 - (b/2)^2 )
// So area integral <=> sqrt( a^2 - (b/2)^2 ) rational.
// 1/2 sqrt( 4*a^2 - b^2 )
// b/4.sqrt( 4*a^2 - b^2 ) integral so 4*a^2 - b^2 must be square.
// S1 = 4*a^2 - (a-1)^2 = 3a^2 + 2a - 1 = (a+1)(3a-1)
// S2 = 4*a^2 - (a+1)^2 = 3a^2 - 2a - 1 = (a-1)(3a+1)
// S1 > S2
// 

int main( int argc, char** argv )
{
    long long limit = 1000000000LL;
    if ( argc > 1 ) limit = atoll( argv[1 ] );

    long long max_side = limit / 3;
    cout << "Max side = " << max_side << endl;

    long long sum = 0;

    long long p1 = -1;
    long long p2 =  1;
    long long s1 = -1;
    long long s2 = -1;
    long long r1 = 1;
    long long r2 = 1; 
    for( long long a = 1; a <= max_side; ++a )
    {
        //cout << "Side a = " << a << endl;
        p1 += 3;
        p2 += 3;
        s1 += 6*a - 1;
        s2 += 6*a - 5; // S2-S1 = 4*a
        while( r1*r1 < s1 ) ++r1;
        while( r2*r2 < s2 ) ++r2;
        //cout << "p1 = " << p1 << " p2 = " << p2 << " s1 = " << s1
        //     << " s2 = " << s2 << " r1 = " << r1 << " r2 = " << r2 << endl;

        if ( ( r1*r1 == s1 ) && ( ( a - 1 )*r1 % 4 == 0 ) && ( a > 1 ) )
        {
            cout << a << "-" << a << "-" << a - 1 << ", " << p1 << endl;
            sum += p1;
        }
        if ( ( r2*r2 == s2 )&& ( ( a + 1 )*r2 % 4 == 0 ) && ( p2 <= limit ) )
        {
            cout << a << "-" << a << "-" << a + 1 << ", " << p2 << endl;
            sum += p2;
        }
    }

    cout << "Sum of perimeters of almost equilateral triangles (perimeter <="
         << limit << ") = " << endl;
    cout << "Answer: " << sum << endl;
    return 0;
}
