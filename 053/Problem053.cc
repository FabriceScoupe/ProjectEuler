#include <iostream>
#include <cstdlib>
#include <vector>
using namespace std;

/*
 * Project Euler: Problem 053 (http://projecteuler.net/problem=53)
 */

// How many Cn,r (= n!/(r!.(n-r)! ) are > 1000000 for 1 <= n <= 100 ?

// Use Pascal's triangle.
int nextPascalTriangleLine( vector<int>& line, int threshold )
{
    int n = line.size();
    line.push_back( 1 );
    int count = 0;
    for( int i = n-1; i >= 1; --i )
    {
        line[ i ] += line[ i-1 ];
        if ( line[ i ] > threshold )
        {
            // Truncate that line at threshold, to avoid overflows
            line[ i ] = threshold;
            //cout << "C" << line.size()-1 <<","<<i<<" > "<< threshold << endl;
            ++count;
        }
    }
    return count;
}

void dump( vector<int>& line )
{
    for( int i = 0; i < (int) line.size(); ++i ) cout << line[ i ] << "\t";
    cout << endl;
}

int main( int argc, char** argv )
{
    int n = 100;
    int threshold = 1000000;
    if ( argc > 1 ) n = atoi( argv[ 1 ] );
    if ( argc > 2 ) threshold = atoi( argv[ 2 ] );
    vector<int> line;
    int count = 0;
    do
    {
        count += nextPascalTriangleLine( line, threshold );
    }
    while( (int) line.size() <= n );

    cout << "Cn,r > " << threshold << " for n <= " << n << ":" << endl;
    cout << "Answer: " << count << endl;
    return 0;
}
