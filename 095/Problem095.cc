#include <iostream>
#include <cstdlib>
#include <map>
#include <set>

using namespace std;

/***
The proper divisors of a number are all the divisors excluding the number
itself. For example, the proper divisors of 28 are 1, 2, 4, 7, and 14.
As the sum of these divisors is equal to 28, we call it a perfect number.

Interestingly the sum of the proper divisors of 220 is 284 and the sum of the
proper divisors of 284 is 220, forming a chain of two numbers. For this reason,
220 and 284 are called an amicable pair.

Perhaps less well known are longer chains. For example, starting with 12496, we
form a chain of five numbers:

12496  14288  15472  14536  14264 ( 12496  ...)

Since this chain returns to its starting point, it is called an amicable chain.

Find the smallest member of the longest amicable chain with no element
exceeding one million.
***/

// Re-using problem 21

// Returns ceiling(square root(n))
inline int root( int n )
{
    int r = 1;
    while( r*r < n ) ++r;
    return r;
}

int d( int n )
{
    static map< int, int > cache_d; // Memoisation
    int& c = cache_d[ n ];
    if ( c > 0 ) return c;
    int sum = 1;
    int r = root( n );
    int div = 2;
    while(( div <= r )&&( div < n ))
    {
        if ( n % div == 0 )
        {
            sum += div + n / div;
        }
        ++div;
    }
    if ( r*r == n ) sum -= r;
    c = sum;
    return sum;
}

int main( int argc, char** argv )
{
    int limit = 1000000;
    if ( argc > 1 ) limit = atoi( argv[ 1 ] );
    map< int, int > lengths;
    set< int > items;
    int max_length = 0;
    int min_elem   = 0;
    for( int n = 2; n < limit; ++n )
    {
        if ( n % 10000 == 0 ) { cout << '.'; flush( cout ); }
        if ( lengths[n] != 0 ) continue; // Already spotted in a chain.
        items.clear();
        int s = n;
        while( ( s > 0 ) && ( s < limit ) && // Divergence test
               ( lengths[s] == 0 ) &&        // Ending up in known chain?
               ( items.find( s ) == items.end() ) )
        {
            items.insert( s );
            s = d(s);
        }
        int l = items.size();
        if ( ( 0 == s ) || ( s >= limit ) ) l = -1;
        if ( s == n ) 
        {
            for( set<int>::iterator it = items.begin();
                 it != items.end(); ++it )
            {
                lengths[ *it ] = l;
                if ( *it < s ) s = *it;
            }
            if ( l > max_length )
            {
                max_length = l;
                min_elem   = s;
                cout << endl <<  "New max length " << l 
                     << ", min element " << s << endl;
            }
        }
        else
        {
            lengths[ n ] = -1;
        }
    }
    cout << endl;
}
