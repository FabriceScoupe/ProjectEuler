#include <iostream>
#include <cstdlib>
#include <map>
#include <vector>
#include <set>
using namespace std;

// The number 145 is well known for the property that the sum of the
// factorial of its digits is equal to 145:
// 1! + 4! + 5! = 1 + 24 + 120 = 145.
// Perhaps less well known is 169, in that it produces the longest chain
// of numbers that link back to 169; it turns out that there are only three
// such loops that exist:
// 169 -> 363601 -> 1454 -> 169
// 871 -> 45361 -> 871
// 872 -> 45362 -> 872
// It is not difficult to prove that EVERY starting number will eventually
// get stuck in a loop. For example:
// 69 -> 363600 -> 1454 -> 169 -> 363601 (->1454)
// 78 -> 45360 -> 871 -> 45361 (->871)
// 540 -> 145 (->145)
// Starting with 69 produces a chain of five non-repeating terms, but
// the longest non-repeating chain with a starting number one million is
// sixty terms.
// How many chains, with a starting number below one million, contain exactly
// sixty non-repeating terms?

// Factorial table:
static inline int fact( char digit )
{
    int f = 1;
    switch( digit )
    {
        case 2: f = 2; break;
        case 3: f = 6; break;
        case 4: f = 24; break;
        case 5: f = 120; break;
        case 6: f = 720; break;
        case 7: f = 5040; break;
        case 8: f = 40320; break;
        case 9: f = 362880; break;
        default: break;
    }
    return f;
}

static inline int next( int n )
{
    int m = n;
    int sumfact = 0;
    while(m > 0) {
        sumfact += fact( m % 10 );
        m /= 10;
    }
    return sumfact;
}

int non_repeating_terms( int n )
{
    static map< int, int > cache;
    set< int > seq;
    int m = n;
    int len = 0;
    while( ( cache[ m ] == 0 ) && ( seq.find( m ) == seq.end() ) ) {
        seq.insert( m );
        m = next( m );
    }
    len = seq.size() + cache[ m ];
    cache[ n ] = len;
    return len;
}

int main( int argc, char** argv )
{
    int limit = 1000000;
    if ( argc > 1 ) limit = atoi( argv[ 1 ] );
    int count = 0;
    for( int n = 1; n < limit; ++n ) {
        int len = non_repeating_terms( n );
        //cout << n << "-> " << len << endl;
        if ( 60 == len ) ++count;
    }
    cout << "Number of 60-long non-repeating chains = " << count << endl;
}
