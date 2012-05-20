#include <iostream>
#include <cstdlib>
#include <set>
using namespace std;

/*
 * Project Euler: Problem 073 (http://projecteuler.net/problem=73)
 */

// Consider the fraction n/d, n and d positive integers.
// If n < d and Highest Common Factor HCF(n,d)=1, it is called a
// proper reduced fraction.
// For d <= 8, there are 3 fractions > 1/3 < 1/2: 3/8, 2/5, 3/7.
// How many fractions lie between 1/3 and 1/2 in the sorted set of
// reduced proper fractions for d <= 12000.

// 1/3 < n/d < 1/2 <=> 3n > d and 2n < d <=> 2n < d < 3n

struct Fraction
{
    Fraction( int n, int d ) : num( n ), den( d ) {};

    int num;
    int den;

    bool operator< ( const Fraction& rhs ) const
    {
        // n1/d1 < n2/d2 <=> n1.d2 < n2.d1
        long long left  = num * rhs.den;
        long long right = den * rhs.num;
        return( left < right );
    }
};

int main( int argc, char** argv )
{
    int limit = 12000;
    if ( argc > 1 ) limit = atoi( argv[ 1 ] );
    set< Fraction > sf;
    for( int n = 1; n <= limit / 2; ++n )
        for( int d = 2*n+1; ( d <= limit ) && ( d < 3*n ); ++d )
            sf.insert( Fraction( n, d ) );

    cout << "For d <= " << limit
         << " number of proper reduced fraction > 1/3 < 1/2 :" << endl;
    cout << "Answer: " << sf.size() << endl;
    return 0;
}
