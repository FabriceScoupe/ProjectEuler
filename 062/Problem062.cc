#include <iostream>
#include <cstdlib>
#include <vector>
#include <map>
using namespace std;

// Cube 41063625 (345^3) can be permuted to produce two other cubes:
// 56623104 (384^3) and 66430125 (405^3). In fact, it is the smallest cube
// which has exactly three permutations of its digits which are also cube.
//
// Find the smallest cube for which exactly five permutations of its digits
// are cube.

long long digits_in_order( long long n, int& num_digits )
{
    long long m = n;
    map<char,char> tmp;
    num_digits = 0;
    do
    {
        ++num_digits;
        ++tmp[ m % 10 ];
        m /= 10;
    }
    while( m > 0 );
    for( map<char,char>::iterator i = tmp.begin(); i != tmp.end(); ++i )
    {
        while( i->second > 0 )
        {
            m *= 10;
            m += i->first;
            --(i->second);
        }
    }
    return m;
}

int main( int argc, char** argv )
{
    int limit = 5;
    if ( argc > 1 ) limit = atoi( argv[ 1 ] );
    long long found = 0;
    map< long long, vector< long long > > m;
    map< long long, vector< int > > ndm;
    for( long long n = 1; 0 == found; ++n )
    {
        long long c = n*n*n;
        int nd = 0;
        long long dio = digits_in_order( c, nd );
        vector< long long >& v = m[ dio ];
        v.push_back( n );
        vector< int >& ndv = ndm[ dio ];
        ndv.push_back( nd );
        if ( v.size() == limit )
        {
            found = c;
            for( int i = 1; i < limit; ++i )
                if ( ndv[ i ] != ndv[ 0 ] ) found = 0;
        }
    }
    int tmp_nd = 0;
    vector< long long >& fv = m[ digits_in_order( found, tmp_nd ) ];
    cout << "Found: " << fv[0]*fv[0]*fv[0] << " = ";
    for( int i = 0; i < limit; ++i ) cout << fv[i] << "^3 ";
    cout << endl;
}
