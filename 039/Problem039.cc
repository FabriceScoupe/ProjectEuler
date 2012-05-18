#include <iostream>
#include <cstdlib>
#include <map>
#include <vector>
using namespace std;

/*
 * Project Euler: Problem 039 (http://projecteuler.net/problem=39)
 */

// if p perimeter (a+b+c) or right-angle triangle (a,b,c integers),
// which p <= 1000 corresponds to most triplets (a,b,c) ?
// See also problem 9.
// Since c = sqrt(a*a+b*b), only consider pairs (a,b).
// Posit a <= b < c; p/3 <= b <= p / 2 and 1 <= a <= p/3
// Make a vary from 1 to max p/3, b vary from a to max p / 2

int root( int n )
{
   static map<int,int> cache;
   int r = cache[ n ];
   if ( 0 == r )
   {
       r = 1;
       while( r * r < n ) ++r;
       cache[ n ] = r;
   }
   return r;
}

static map< int, vector< pair< int, int > > > tripletMap;

// A not-subtle way to build all triplets
int BuildTriplets( int n )
{
    int max_p  = 0;
    int max_nt = 0;

    for( int a = 1; a <= n / 3 + 1; ++a )
    {
        int r = root( 2*a*a );
        for( int b = a; r <= n - a - b; ++b )
        {
            r = root( a*a+b*b );
            if ( r*r != a*a+b*b ) continue;
            int p = a + b + r;
            if ( p <= n )
            {
                vector< pair< int, int > >& v = tripletMap[ p ];
                v.push_back( pair<int,int>( a, b ) );
                if ( (int) v.size() > max_nt )
                {
                    max_nt = v.size();
                    max_p  = p;
                }
            }
        }
    }
    return max_p;
}

int main( int argc, char** argv )
{
    int n = 1000; 
    if ( argc > 1 ) n = atoi( argv[1] );
    int max_p = BuildTriplets( n );
    vector< pair< int, int > >& v = tripletMap[ max_p ];
    for( int i = 0; i < (int) v.size(); ++i )
    {
        int a = v[i].first;
        int b = v[i].second;
        cout << "(" << a << "," << b << "," << root(a*a+b*b) << ")" << endl;
    }
    cout << endl << "max(a+b+c) = " << max_p << " (" <<v.size()<< ")" << endl;
    cout << "Answer: " << max_p << endl;
    return 0;
}
