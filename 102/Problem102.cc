#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <cstring>

using namespace std;

/*
 * Project Euler: Problem 102 (http://projecteuler.net/problem=102)
 */

/***
Three distinct points are plotted at random on a Cartesian plane,
for which -1000 ≤ x, y ≤ 1000, such that a triangle is formed.

Consider the following two triangles:

A(-340,495), B(-153,-910), C(835,-947)

X(-175,41), Y(-421,-714), Z(574,-645)

It can be verified that triangle ABC contains the origin,
whereas triangle XYZ does not.

Using triangles.txt (right click and 'Save Link/Target As...'),
a 27K text file containing the co-ordinates of one thousand "random" triangles,
find the number of triangles for which the interior contains the origin.

NOTE: The first two examples in the file represent the triangles
in the example given above.
***/

inline int sign_cross_prod( int x1, int y1, int x2, int y2 )
{
    int cp = x1*y2-x2*y1;
    return ( cp == 0 ? 0 : ( cp > 0 ? 1 : -1 ) );
}

inline bool contains_origin( int xa, int ya, int xb, int yb, int xc, int yc )
{
    // AB.AC and AB.AO = OA.AB have same sign and
    // BC.BA and BC.BO = OB.BC have same sign and
    // CA.CB and CA.CO = OC.CA have same sign, so:
    return( ( sign_cross_prod( xb-xa, yb-ya, xc-xa, yc-ya ) *
              sign_cross_prod( xa, ya, xb-xa, yb-ya ) >= 0 ) &&
            ( sign_cross_prod( xc-xb, yc-yb, xa-xb, ya-yb ) *
              sign_cross_prod( xb, yb, xc-xb, yc-yb ) >= 0 ) &&
            ( sign_cross_prod( xa-xc, ya-yc, xb-xc, yb-yc ) *
              sign_cross_prod( xc, yc, xa-xc, ya-yc ) >= 0 ) );
}

int parseFile( char* filename )
{
    int count = 0;
    ifstream in( filename );
    char c = 0;
    char buf[ 10 ]; memset( buf, 0, 10 );
    char l = 0;
    vector< int > v;
    if ( in ) do
    {
        if ( ! in.get( c ) ) c = 0;
        if ( ( '\r' == c ) || ( '\n' == c ) || ( c == 0 ) )
        {
            v.push_back( atoi( buf ) );
            memset( buf, 0, 10 );
            l = 0;
            if ( 6 == v.size() )
            {
                if ( contains_origin( v[0],v[1],v[2],v[3],v[4],v[5] ) )
                {
                    ++count;
                }
            }
            v.clear();
        }
        else if ( ',' == c )
        {
            v.push_back( atoi( buf ) );
            memset( buf, 0, 10 );
            l = 0;
        }
        else
        {
            buf[(int)(l++)] = c;
        }
    }
    while( c != 0 );
    return count;
}

int main( int argc, char** argv )
{
    char* filename = (char*) "triangles.txt";
    if ( argc > 1 ) filename = argv[ 1 ];
    int count = parseFile( filename );
    cout << endl << "Number of triangles containing origin = "<< endl;
    cout << "Answer: " << count << endl;
    return 0;
}
