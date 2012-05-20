#include <iostream>
#include <fstream>
#include <vector>

/*
 * Project Euler: Problem 67 (http://projecteuler.net/problem=67)
 */

// Find the maximum sum from top to bottom in file
// See problem 18, same idea there!

using namespace std;

void parseFile( char* filename, vector< int >& triangle )
{
    ifstream in( filename );
    if (in) {
        char c     = 0;
        int  value = 0;
        do {
            if (!in.get(c)) c = 0;
            if ((0 == c) || (' ' == c) || ('\n' == c)) {
                if ( value > 0 ) {
                    triangle.push_back( value );
                    value = 0;
                }
            } else if ( ( c >= '0' ) && ( c <= '9' ) ) {
                value *= 10;
                value += c - '0';
            }
        } while( c != 0 );
        in.close();
    }
}

static inline int index( int line, int index ) {
    return(index + line*(line+1)/2);
}

// Find max sum in triangle of dim N
// Start from N-1 line: store all max sum of elements of this line and next
// Replace line N-1 by these N-1 max sums
// Repeat until the top.
//
int maxSum( vector<int>& triangle, int N )
{
    int line = N-2;
    while(line >= 0) {
        for(int i = line; i >= 0; --i) {
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
    char* filename = (char*)"triangle.txt";
    if ( argc > 1 ) filename = argv[ 1 ];
    vector< int > t;
    parseFile( filename, t );
    cout << t.size() << " elements in triangle : ";
    int n = 1;
    unsigned int tn = 1;
    while( tn < t.size() ) tn += ++n;
    cout << n << " levels." << endl;
    cout << endl << "Answer: " << maxSum( t, n ) << endl;
    return 0;
}
