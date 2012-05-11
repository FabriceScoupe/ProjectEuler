#include <iostream>
#include <cstdlib>
#include <set>
using namespace std;

// Proper fraction:  n / d, n < d and n and d relatively prime.
// Listing all proper fraction with d <= 8 in ascending order:
// 1/8, 1/7, 1/6, 1/5, 1/4, 2/7, 1/3, 3/8, 2/5, 3/7, 1/2, 4/7, 3/5, 5/8,
// ...
// 2/5 is the fraction immediately to the left of 3/7.
//
// For d <= 1000000, what is the fraction immediately to the left of 3/7 ?
// (basically, ignore anything >= 3/7)

void to_proper_fraction( int& n, int& d )
{
    while( ( n % 2 == 0 ) && ( d % 2 == 0 ) )
    {
        n /= 2;
        d /= 2;
    }
    int p = 3;
    while( p < n )
    {
        while( ( n % p == 0 ) && ( d % p == 0 ) )
        {
             n /= p;
             d /= p;
        }
        p += 2;
    }
}

// n / d < 3 / 7 <=> 7n < 3d ( d <= 1000000 )
int main( int argc, char** argv )
{
    int limit = 1000000;
    if ( argc > 1 ) limit = atoi( argv[1] );
    int max_n = 1;
    int max_d = limit;

    for( int d = 2; d <= limit; ++d )
    {
        // Pick n so that n / d > max_n / max_d
        // n > d*max_n / max_d
        long long min = (long long) d * (long long) max_n /
                        (long long) max_d;
        for( int n = min; 7*n < 3*d; ++n )
        {
            // n / d > max_n / max_d <=> n*max_d > d*max_n
            long long left  = (long long) n * (long long) max_d;
            long long right = (long long) d * (long long) max_n;
            if ( left > right )
            {
                max_n = n;
                max_d = d;
                cout << max_n << " / " << max_d << endl;
            }
        }
    }

    to_proper_fraction( max_n, max_d );
    cout << "With d <= " << limit << ", fraction to the left of 3/7 is "
         << max_n << " / " << max_d << endl;
}
