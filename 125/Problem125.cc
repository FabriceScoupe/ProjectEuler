#include <iostream>
#include <cstdlib>
#include <vector>
#include <set>


using namespace std;

/***
The palindromic number 595 is interesting because it can be written as the
sum of consecutive squares:
6^(2) + 7^(2) + 8^(2) + 9^(2) + 10^(2) + 11^(2) + 12^(2).

There are exactly eleven palindromes below one-thousand that can be written
as consecutive square sums, and the sum of these palindromes is 4164. Note
that 1 = 0^(2) + 1^(2) has not been included as this problem is concerned
with the squares of positive integers.

Find the sum of all the numbers less than 10^(8) that are both palindromic
and can be written as the sum of consecutive squares.
***/

// Sum[k=1..n] k^2 = 1/6 n*(n+1)(2n+1) = ssq( n );

inline bool is_palindrome( long long n )
{
    long long m = n;
    long long r = 0;
    while( m > 0 )
    {
        r *= 10;
        r += m % 10;
        m /= 10;
    }
    return( r == n );
}

int main( int argc, char** argv )
{
    long long limit = 100000000;
    if ( argc > 1 ) limit = atoll( argv[ 1 ] );
    long long ssq = 0;
    vector< long long > sum_squares;
    sum_squares.push_back( 0 );
    for( long long n = 1; n*n < limit; ++n )
    {
        ssq += n*n;
        sum_squares.push_back( ssq );
    }
    set< long long > pals;
    for( int i = sum_squares.size()-1; i > 1; --i )
    {
        for( int j = i-2; j >= 0; --j )
        {
            long long diff = sum_squares[ i ] - sum_squares[ j ];
            if ( diff >= limit ) break;
            if ( is_palindrome( diff ) )
            {
                pals.insert( diff );
                //cout << diff << " = ssq(" << i << ")-ssq(" << j << ")" << endl;
            }
        }
    }
    long long sum = 0;
    for( set< long long >::iterator it = pals.begin(); it != pals.end(); ++it )
    {
        sum += *it;
    }
    cout << "Sum of palindromes sums of consecutives squares and < "
         << limit << " = " << sum << endl;
}
