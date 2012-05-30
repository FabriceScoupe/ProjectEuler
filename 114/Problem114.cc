#include <iostream>
#include <cstdlib>
#include <map>
using namespace std;

/*
 * Project Euler: Problem 114 (http://projecteuler.net/problem=114)
 */

/***
A row measuring seven units in length has red blocks with a minimum length of
three units placed on it, such that any two red blocks (which are allowed to be
different lengths) are separated by at least one black square. There are
exactly seventeen ways of doing this.

How many ways can a row measuring fifty units in length be filled?

NOTE: Although the example above does not lend itself to the possibility, in
general it is permitted to mix block sizes. For example, on a row measuring
eight units in length you could use red (3), black (1), and red (4).
***/

// Related to 115, 116 and 117.

// nr number of red tiles
// nb number of red tiles
// There must be at least nr-1 black tiles nb >= nr - 1 (gaps)
// Number of ways of arranging black around red?
// nr - 1 in gaps, nb - nr + 1 remaining.
// holes? nr - 1 + head and tail => nr + 1
// Ways of arranging (nb-nr+1) balls in (nr+1) holes?
// => Feller's intro to prob, p.36:
// == binomial( (nb-nr+1)+(nr+1)-1,(nr+1)-1 )
// == binomial( nb+1, nr )
//
// distribution of length into nr?
// At least 3 per tile and nr-1 gaps => available length l-3*nr - nr + 1
// => av. len = l - 4*nr + 1 = avl;
// Ways of arranging avl (balls) into nr (holes)
// Same again:
// ways = binomial( avl+nr-1, nr-1);
// 

static map< pair<int,int>, long long > binomial;

void calc_binomial( int up_to_row )
{
    binomial[ pair<int,int>(0,0) ] = 1; // initialise
    for( int r = 1; r <= up_to_row; ++r ) {
        for( int c = 0; c <= r; ++c ) {
            binomial[ pair<int,int>(r,c) ] =
                binomial[ pair<int,int>(r-1,c-1) ] +
                binomial[ pair<int,int>(r-1, c) ];
        }
    }
}

long long nways( int len )
{
    long long sum = 0;
    for( int nr = 1; len - 4*nr + 1 >= 0 ; ++nr ) {
        int max_l = len - 3*nr; // Available length for black
        // At least enough black tiles for gaps, so min = nr - 1
        for( int nb = nr-1; nb <= max_l; ++nb ) {
            int avl = max_l - nb; // Available for red
            int nw1 = binomial[ pair<int,int>( avl+nr-1, nr-1 ) ];
            int nw2 = binomial[ pair<int,int>( nb+1, nr ) ];
            // cout << "nr = " << nr << " nb = " << nb
            //     << " nw1 = " << nw1 << " nw2 = " << nw2 << endl;
            sum += nw1*nw2;
        }
    }
    return sum;
}

int main( int argc, char** argv )
{
    int len = 50;
    if ( argc > 1 ) len = atoi( argv[ 1 ] );
    cout << "Length of row = " << len << endl;
    calc_binomial( len );
    long long nw = 1 + nways( len );
    cout << "Total number of ways = " << endl;
    cout << "Answer: " << nw << endl;
    return 0;
}
