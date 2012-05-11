#include <iostream>
#include <cstdlib>

using namespace std;

/***
The points P(x1,y1) and Q(x2,y2) are plotted at integer co-ordinates and
are joined to the origin , O(0,0) to form the triangle OPQ.
There are exactly 14 triangles containing a right angle than can be formed
when each coordinate lies between 0 and 2 inclusive; that is:
0 <= x1,y2,x2,y2 <= 2
Given that 0 <= x1,y1,x2,y2 <= 50 how many right triangles can be formed?
***/

// Right angle: area of triangle = 1/2 that of rectangle of sides:
// OP and PQ, or OQ and PQ, or OP and OQ (3 tests)

inline bool is_right_angle_triangle( int x1, int y1, int x2, int y2 )
{
    int area = x1*y2 - x2*y1;
    if ( 0 == area ) return false;
    if ( area < 0 ) area = -area;
    area *= area;
    int op2 = x1*x1 + y1*y1;
    int oq2 = x2*x2 + y2*y2;
    int pq2 = (x2-x1)*(x2-x1)+(y2-y1)*(y2-y1);
    
    return ( ( area == op2*oq2 ) || 
             ( area == op2*pq2 ) ||
             ( area == oq2*pq2 ) );
}

int main( int argc, char** argv )
{
    int limit = 50;
    if ( argc > 1 ) limit = atoi( argv[ 1 ] );

    int count = 0;

    for( int x1 = 0; x1 <= limit; ++x1 )
        for( int y1 = 0; y1 <= limit; ++y1 )
            for( int x2 = x1; x2 <= limit; ++x2 )
                for( int y2 = (x2>x1?0:y1+1); y2 <= limit; ++y2 )
                    if ( is_right_angle_triangle( x1, y1, x2, y2 ) )
                    {
                        cout << "P(" << x1 << "," << y1 << ") and ";
                        cout << "Q(" << x2 << "," << y2 << ")." << endl;
                        ++count;
                    }
    cout << endl << "Number of right angle triangles with 0 <= x1,y1,x2,y2 <=";
    cout << limit << " = " << count << endl;
}
