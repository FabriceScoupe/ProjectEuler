#include <iostream>
#include <cstdlib>
#include <vector>
using namespace std;

/*
 * Project Euler: Problem 048 (http://projecteuler.net/problem=48)
 */

// Find the last 10 digits of the series 1^1+2^2+3^3+...+1000^1000
// Note: 1^1+2^2+...+10^10 = 10405071317.

// 10^10 doesn't contribute any digit in the last ten (same for its multiples)
// (sum[k=1..n] k^k)%(10^10) = ( sum[k=1..n] (k^k)%(10^10) ) % (10^10)
// Also (a.b)%m = ((a%m).(b%m)) % m

int main( int argc, char** argv )
{
    int n = 1000;
    if ( argc > 1 ) n = atoi( argv[ 1 ] );
    long long sum = 0;
    long long pow10 = 10000000000LL;
    for( int k = 1; k <= n; ++k )
    {
        long long val = 1;
        for( int j = 1; j <= k; ++j )
        {
            val *= ( k % pow10 );
            val %= pow10;
        }
        sum += val;
        sum %= pow10;
    }
    sum %= pow10;
    cout << "sum[k=1.." << n << "] k^k % 10^10:" << endl;
    cout << "Answer: " << sum << endl;
    return 0;
}
