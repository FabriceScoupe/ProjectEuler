#include <iostream>
#include <cstdlib>
#include <map>

using namespace std;

/***
NOTE: This is a more difficult version of problem 114.

A row measuring n units in length has red blocks with a minimum length of m
units placed on it, such that any two red blocks (which are allowed to be
different lengths) are separated by at least one black square.

Let the fill-count function, F(m, n), represent the number of ways that a row
can be filled.

For example, F(3, 29) = 673135 and F(3, 30) = 1089155.

That is, for m = 3, it can be seen that n = 30 is the smallest value for
which the fill-count function first exceeds one million.

In the same way, for m = 10, it can be verified that F(10, 56) = 880711
and F(10, 57) = 1148904, so n = 57 is the least value for which the fill-count
function first exceeds one million.

For m = 50, find the least value of n for which the fill-count function
first exceeds one million.
***/

// Re-using 114, making binomial a memoised function

long long binomial( int n, int k )
{
    static map< pair< int,int >, long long > memo;
    long long& m = memo[ pair<int,int>( n, k ) ];
    if ( m > 0 ) return m;

    long long bp = 1;
    int ns  = 1;
    int nk  = n - k;
    int nks = 1;
    int ks  = 1;
    while( ns < n )
    {
        bp *= ++ns;
        if ( ( nks < nk ) && ( bp % (nks+1) == 0 ) ) bp /= ++nks;
        if ( ( ks < k ) && ( bp % (ks+1) == 0 ) ) bp /= ++ks;
    }
    m = bp;
    return bp;
}

long long F( int m, int n )
{
    long long sum = 0;
    for( int nr = 1; n - (m+1)*nr + 1 >= 0 ; ++nr )
    {
        int max_l = n - m*nr; // Available length for black
        // At least enough black tiles for gaps, so min = nr - 1
        for( int nb = nr-1; nb <= max_l; ++nb ) 
        {
            int avl = max_l - nb; // Available for red
            int nw1 = binomial( avl+nr-1, nr-1 );
            int nw2 = binomial( nb+1, nr );
            sum += nw1*nw2;
        }
    }
    return sum;
}

int main( int argc, char** argv )
{
    int m = 50;
    if ( argc > 1 ) m = atoi( argv[ 1 ] );
    long long limit = 1000000LL;
    if ( argc > 2 ) limit = atoll( argv[ 2 ] );
    cout << "min(n) such as F(" << m << ", n) > " << limit << " = " << endl;
    int n = m;
    while( F( m, n ) <= limit ) ++n;
    cout << "Answer: " << n << endl;
    return 0;
}
