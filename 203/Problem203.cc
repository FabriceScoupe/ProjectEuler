#include <iostream>
#include <cstdlib>
#include <vector>
#include <map>
#include <set>

using namespace std;

/***
The binomial coefficients ^(n)C_(k) can be arranged in triangular form,
Pascal's triangle, like this:

1	
1   1	
1   2   1	
1   3   3   1	
1   4   6   4   1	
1   5   10  10  5   1	
1   6   15  20  15  6   1	
1   7   21  35  35  21  7   1
.........

It can be seen that the first eight rows of Pascal's triangle contain twelve
distinct numbers: 1, 2, 3, 4, 5, 6, 7, 10, 15, 20, 21 and 35.

A positive integer n is called squarefree if no square of a prime divides n.
Of the twelve distinct numbers in the first eight rows of Pascal's triangle,
all except 4 and 20 are squarefree. The sum of the distinct squarefree numbers
in the first eight rows is 105.

Find the sum of the distinct squarefree numbers in the first 51 rows of
Pascal's triangle.
***/

bool is_square_free( long long n )
{
    static map< long long, char > memo;
    char& m = memo[ n ];
    if ( m != 0 ) return( m > 0 );

    int d = 2;
    int nd = 0;
    while( d <= n ) {
        nd = 0;
        while( n % d == 0 ) {
            n /= d;
            ++nd;
            if ( 2 == nd ) break;
        }
        if ( 2 == nd ) break;
        ++d;
    }
    bool res = ( nd < 2 );
    m = ( res ? 1 : -1 );
    return res;
}

int main( int argc, char** argv )
{
    int rows = 51;
    if ( argc > 1 ) rows = atoi( argv[ 1 ] );
    vector< long long > pascal;
    // Input first row
    pascal.push_back( 0 );
    pascal.push_back( 1 );
    pascal.push_back( 0 );
    int r = 1;
    set< long long > sf;

    while( r <= rows ) {
        // Dump row
        for(unsigned int i = 1; i < pascal.size()-1; ++i) {
            long long pi = pascal[i];
            //cout << pi << " ";
            if ( is_square_free( pi ) ) sf.insert( pi );
        }
        //cout << endl;

        // Build new row
        // C(n,k) = C(n-1,k-1)+C(n-1,k)
        for(unsigned int i = pascal.size()-1; i >= 1; --i) {
            pascal[i] += pascal[i-1];
        }
        pascal.push_back( 0 );
        ++r;
    }

    long long sum = 0;
    for( set< long long >::iterator it = sf.begin(); it != sf.end(); ++it )
        sum += *it;
    cout << "Sum of square-free coefficients = " << sum << endl;
    return 0;
}
