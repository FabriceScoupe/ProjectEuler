#include <iostream>
#include <cstdlib>

using namespace std;

/***
Using a combination of black square tiles and oblong tiles chosen from:
red tiles measuring two units, green tiles measuring three units,
and blue tiles measuring four units, it is possible to tile a row measuring
five units in length in exactly fifteen different ways.

Using a combination of black square tiles and oblong tiles chosen from:
red tiles measuring two units, green tiles measuring three units,
and blue tiles measuring four units, it is possible to tile a row measuring
five units in length in exactly fifteen different ways.
***/

// See how many tiles fit,
// Then how many black ones are left,
// Multiply by number of permutations of those (indistinguishable)
// black tiles.
// ntiles + nblacks = ntot
// ntot! number of permutations
// => ntot! / ( ntiles! * nblacks! )
// ntot! / ( (ntot-ntiles)! ntiles! ) => binomial coefficients!
// 

// Number of ways of tiling row (length) with tile

inline long long nways( int l, int t1, int t2, int t3, int n1, int n2, int n3 )
{
    int busy = n1*t1 + n2*t2 + n3*t3;
    if ( busy >  l ) return 0;
    int nb = l - busy;
    int ntot = n1 + n2 + n3 + nb;
    // coef is ntot! / ( n1! * n2! * n3! * nblacks! )
    long long coef = 1;
    int nts = 1;
    int n1s = 1;
    int n2s = 1;
    int n3s = 1;
    int nbs = 1;
    while( nts < ntot )
    {
        coef *= ++nts;
        if ( ( n1s < n1 ) && ( coef % (n1s+1) == 0 ) ) coef /= ++n1s;
        if ( ( n2s < n2 ) && ( coef % (n2s+1) == 0 ) ) coef /= ++n2s;
        if ( ( n3s < n3 ) && ( coef % (n3s+1) == 0 ) ) coef /= ++n3s;
        if ( ( nbs < nb ) && ( coef % (nbs+1) == 0 ) ) coef /= ++nbs;
    }
    return coef;
}

long long nways( int length, int t1, int t2, int t3 )
{
    long long sum = 0;
    for( int i1 = 0; i1*t1 <= length; ++i1 )
    {
        int l1 = length - i1*t1;
        for( int i2 = 0; i2*t2 <= l1; ++i2 )
        {
            int l2 = l1 - i2*t2;
            for( int i3 = 0; i3*t3 <= l2; ++i3 )
            {
                sum += nways( length, t1, t2, t3, i1, i2, i3 );
            }
        }
    }
    return sum;
}

int main( int argc, char** argv )
{
    int len = 50;
    if ( argc > 1 ) len = atoi( argv[ 1 ] );
    cout << "Length of row = " << len << endl;
    cout << "Total number of ways = " << nways( len, 2, 3, 4 ) << endl;
}
