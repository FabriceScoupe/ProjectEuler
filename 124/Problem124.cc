#include <iostream>
#include <cstdlib>
#include <vector>
#include <map>
#include <set>

using namespace std;

/***
The radical of n, rad(n), is the product of distinct prime factors of n. For example, 504 = 2^(3) × 3^(2) × 7, so rad(504) = 2 × 3 × 7 = 42.

If we calculate rad(n) for 1 ≤ n ≤ 10, then sort them on rad(n), and sorting on n if the radical values are equal, we get:

Let E(k) be the kth element in the sorted n column; for example, E(4) = 8 and E(6) = 9.

If rad(n) is sorted for 1 ≤ n ≤ 100000, find E(10000).
***/

vector< int > primes;
map< int, set< int > > sorted_rads;

int main( int argc, char** argv )
{
    int n = 100000;
    int k = 10000;
    if ( argc > 1 ) n = atoi( argv[ 1 ] );
    if ( argc > 2 ) k = atoi( argv[ 2 ] );

    primes.push_back( 2 );
    sorted_rads[ 1 ].insert( 1 );
    sorted_rads[ 2 ].insert( 2 );

    for( int i = 3; i <= n; ++i )
    {
        int rad = 1;
        int p = i;
        for(unsigned int j = 0; j < primes.size(); ++j )
        {
            int pj = primes[j];
            if ( p % pj == 0 )
            {
                rad *= pj;
                while( p % pj == 0 ) p /= pj;
            }
        }
        if ( p == i )
        {
            primes.push_back( p );
            rad = p;
        }
        sorted_rads[ rad ].insert( i );
    }

    int l = 1;
    map< int, set< int > >::iterator it = sorted_rads.begin();
    set< int >::iterator jt = it->second.begin();
    while( l < k )
    {
        ++l;
        ++jt;
        if ( jt == it->second.end() )
        {
            ++it;
            jt = it->second.begin();
        }
    }
    cout << "(Radicals): E(" << l << ")=" << *jt << endl;
}
