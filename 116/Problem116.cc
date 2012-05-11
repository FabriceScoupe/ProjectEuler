#include <iostream>
#include <cstdlib>
#include <map>

using namespace std;

/***
A row of five black square tiles is to have a number of its tiles replaced
with coloured oblong tiles chosen from red (length two), green (length three),
or blue (length four).

If red tiles are chosen there are exactly seven ways this can be done.

RR...    .RR..    ..RR.    ...RR
RRRR.    RR.RR    .RRRR

If green tiles are chosen, there are three ways:
GGG..    .GGG.    ..GGG

And if blue tiles are chosen, there are two ways:
.BBBB    BBBB.

Assuming that colours cannot be mixed there are 7 + 3 + 2 = 12 ways of
replacing the black tiles in a row measuring five units in length.

How many different ways can the black tiles in a row measuring fifty units in
length be replaced if colours cannot be mixed and at least one coloured tile
must be used?

NOTE: This is related to problem 117.
***/

// See how many tiles fit,
// Then how many black ones are left,
// Multiply by number of permutations of those (indistinguishable)
// black tiles.
// nreds + nblacks = ntot
// ntot! number of permutations
// => ntot! / ( nreds! * nblacks! )
// ntot! / ( (ntot-nreds)! nreds! ) => binomial coefficients!
// 

// Number of ways of tiling row (length) with tile

static map< pair<int,int>, long long > binomial;

void calc_binomial( int up_to_row )
{
    binomial[ pair<int,int>(0,0) ] = 1; // initialise
    for( int r = 1; r <= up_to_row; ++r )
    {
        for( int c = 0; c <= r; ++c )
            binomial[ pair<int,int>(r,c) ] =
                binomial[ pair<int,int>(r-1,c-1) ] +
                binomial[ pair<int,int>(r-1, c) ];
    }
}

long long nways( int length, int tile, int ntiles )
{
    if ( ntiles * tile >  length ) return 0;
    if ( ntiles * tile == length ) return 1;
    int nblacks = length - ntiles*tile;
    int ntot = ntiles + nblacks;
    return binomial[ pair<int,int>( ntot, nblacks ) ];
}

long long nways( int length, int tile )
{
    int i = 1;
    long long nw = 0;
    long long sum = 0;
    do
    {
        nw = nways( length, tile, i );
        sum += nw;
        ++i;
    }
    while( nw > 0 );
    return sum;
}

int main( int argc, char** argv )
{
    int len = 50;
    if ( argc > 1 ) len = atoi( argv[ 1 ] );

    cout << "Length of row = " << len << endl;

    calc_binomial( len );

    long long red   = nways( len, 2 );
    cout << red << " ways of replacing with red tiles" << endl;
    long long green = nways( len, 3 );
    cout << green << " ways of replacing with green tiles" << endl;
    long long blue  = nways( len, 4 );
    cout << blue << " ways of replacing with blue tiles" << endl;
    cout << "Total = " << red + green + blue << endl;
}
