#include <iostream>
#include <cstdlib>
using namespace std;

/*
 * Project Euler: Problem 113 (http://projecteuler.net/problem=113)
 */

/***
Working from left-to-right if no digit is exceeded by the digit to its left it is called an increasing number; for example, 134468.

Similarly if no digit is exceeded by the digit to its right it is called a decreasing number; for example, 66420.

We shall call a positive integer that is neither increasing nor decreasing a "bouncy" number; for example, 155349.

As n increases, the proportion of bouncy numbers below n increases such that there are only 12951 numbers below one-million that are not bouncy and only 277032 non-bouncy numbers below 10^(10).

How many numbers below a googol (10^(100)) are not bouncy?
***/

// 100 digits
// 9 "flat" numbers: all 1s, 2s, 3s, ..., 9s. (0s ?)
// Consider "deltas" instead (increasing case), ie increment over preceding
// digit.
// e.g. non bouncy 5566799 -> 5010120
// The sum of the first digit and the sum of the deltas is <=9
// That first digit is also a delta (from 0)
// So: 9 deltas (indistinguishable balls) and 100 digits (distinct holes); 
// Number of ways (Feller!): 
// nws = C(n+r-1,n-1) (n holes, r balls)
//     = (n+r-1)!/(n-1)!/r!
//
// Decreasing numbers: deltas (decrement) from 9 (first digit) or preceding
// digit:
// so 66420 -> 30222 => deltas sum to <=9 again.
// Decreasing might start with 0!
// 000066420
//
// "Flats" => were all deltas are in first digit, counted twice (10 of them)

long long n_inc( int n, int r )
{
    if ( 0 == r ) return 1;
    long long p = 1;
    long long d = 1;
    for( int i = 1; i <= r; ++i )
    {
        p *= n-1 + i;
        d *= i;
    }
    //cout << r << " deltas in " << n << " digits: " << p /d << endl;
    return p / d;
}

int main( int argc, char** argv )
{
    int ndigits = 100;
    if ( argc > 1 ) ndigits = atoi( argv[ 1 ] );
    long long non_bouncy = 0;
    // Add increasing numbers
    for( int d = 0; d <= 9; ++d ) non_bouncy += n_inc( ndigits, d );
    non_bouncy -= 10*ndigits; // remove flats (all 0s, 1s, ... 9s )
    // Flats are going to be counted as decreasing. 
    // Remember that flats may have leading 0s!!!

    // Add decreasing numbers
    for( int n = 1; n <= ndigits; ++n )
    {
        for( int d = 0; d <=9; ++d ) non_bouncy += n_inc( n, d );
    }

    non_bouncy -= 1; // Don't count 0
    
    cout << "Number of non-bouncy numbers below 10^" << ndigits << " = ";
    cout << endl << "Answer: " << non_bouncy << endl;
    return 0;
}
