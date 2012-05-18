#include <iostream>
#include <iomanip>
#include <strings.h>
#include <vector>
using namespace std;

/*
 * Project Euler: Problem 018 (http://projecteuler.net/problem=18)
 */

const char* raw = "\
75 \
95 64 \
17 47 82 \
18 35 87 10 \
20 04 82 47 65 \
19 01 23 75 03 34 \
88 02 77 73 07 63 67 \
99 65 04 28 06 16 70 92 \
41 41 26 56 83 40 80 70 33 \
41 48 72 33 47 32 37 16 94 29 \
53 71 44 65 25 43 91 52 97 51 14 \
70 11 33 28 77 73 17 78 39 68 17 57 \
91 71 52 38 17 14 91 43 58 50 27 29 48 \
63 66 04 68 89 53 67 30 73 16 69 87 40 31 \
04 62 98 27 23 09 70 98 73 93 38 53 60 04 23";

void parseTriangle( char* source, vector<int>& triangle )
{
     int num = 0;
     char* c = source;
     while( *c != 0 )
     {
         switch( *c )
         {
             case ' ':
                 if ( num > 0 )
                 {
                     triangle.push_back( num );
                 }
                 num = 0;
                 break;
             default: // digit [0..9]
                 num *= 10;
                 num += *c - '0';
                 break;
         }
         ++c;
     }
     triangle.push_back( num );
}

int root( int n )
{
   int i = 1;
   while( i * i < n ) ++i;
   return i;
}

int dim( vector<int>& triangle )
{
    return( ( root( 1 + 8*triangle.size() ) - 1 ) / 2 );
}

int index( int line, int idx )
{
    return( (( line + 1 )*line) / 2 + idx );
}

// Find max sum in triangle of dim N
// Start from N-1 line: store all max sum of elements of this line and next
// Replace line N-1 by these N-1 max sums
// Repeat until the top.
//
int maxSum( vector<int>& triangle )
{
    int N = dim( triangle );
    int line = N-2;
    while( line >= 0 )
    {
        for( int i = line; i >= 0; --i )
        {
           int left    = triangle [ index( line+1, i   ) ];
           int right   = triangle [ index( line+1, i+1 ) ];
           int current = index( line, i ); 
           triangle[ current ] += ( left > right ? left : right );
        }
        --line;
    }
    return triangle[ index( 0, 0 ) ];
}

int main( int argc, char** argv )
{
    char* src = (char*) raw;
    if ( argc > 1 ) src = argv[1];
    vector<int> triangle;
    parseTriangle( src, triangle );
    cout << "Triangle has " << triangle.size() << " elements, " 
         << dim( triangle ) << " lines." << endl;
    for( int line = 0; line < dim( triangle ); ++line )
    {
        for( int idx = 0; idx < dim( triangle )-line-1; ++idx ) cout << "  ";
        for( int idx = 0; idx <= line; ++idx )
            cout << setw(2) << triangle[ index( line, idx ) ] << "  ";
        cout << endl;
    }

    cout << "Answer: " << maxSum( triangle ) << endl;
    return 0;
}
