#include <iostream>
#include <cmath>
using namespace std;

/*
 * Project Euler: Problem 063 (http://projecteuler.net/problem=63)
 */

// The 5-digit number 16807 = 7^5 is a 5th power.
// The 9-digit number 134217728 = 8^9 is a 9th power.
// How many n-digit positive integers exist which are also an n-th power?

// Number of digits in n = floor( log10( n ) ) + 1
// 10^n has (n+1) digits
// log10( 9 ) = 0.9542425...; when floor( n.log10( 9 ) ) < n - 1, stop.
int main( int argc, char** argv )
{
    int n = 0;
    double floor_log10 = 0.0;
    int count = 0;
    do {
        ++n;
        for( int a = 1; a < 10; ++a ) {
            floor_log10 = floor( n*log10( a ) ) + 1;
            if ( floor_log10 == n ) {
                //cout << a << "^" << n << endl;
                ++count;
            }
        }
    }
    while( floor_log10 >= n );
    cout << "Answer: " << count << endl;
    cout << " n-digit positive integers also n-th power" << endl;
    return 0;
}
