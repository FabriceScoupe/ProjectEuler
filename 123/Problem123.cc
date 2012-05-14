#include <iostream>
#include <cstdlib>
#include <vector>

using namespace std;

/***
Let p_(n) be the nth prime:
2, 3, 5, 7, 11, ...,
and let r be the remainder when
(p_(n)−1)^(n) + (p_(n)+1)^(n) is divided by p_(n)^(2).

For example, when n = 3, p_(3) = 5, and 4^(3) + 6^(3) = 280 ≡ 5 mod 25.
The least value of n for which the remainder first exceeds 10^(9) is 7037.
Find the least value of n for which the remainder first exceeds 10^(10).
***/

// See Problem 120, too.
// Actually: (p-1)^n+(p+1)^n = (-1)^(n-1)*n*p+(-1)^n+n*p^n+1 (module p^2)
// since all powers of p >= 2 disappear with the mod!
// if n even, this is = 2 (mod p^2)
// if n odd , = 2*n*p (mod p^2) and this > limit (10^9)
//
// so look for first p(n) such that 2*n*p > limit.
//

static vector< long long > primes;

long long get_next_prime( )
{
    long long p = primes[ primes.size() - 1 ];
    bool is_prime = false;
    while( ! is_prime )
    {
        p += 2;
        is_prime = true;
        for(unsigned int i = 0; is_prime && ( i < primes.size() ); ++i )
        {
            long long pi = primes[ i ];
            if ( pi*pi > p ) break;
            is_prime = ( p % pi != 0 );
        }
    }
    primes.push_back( p );
    return p;
}


int main( int argc, char** argv )
{
    long long limit = 10000000000LL;
    if ( argc > 1 ) limit = atoll( argv[ 1 ] );

    primes.push_back( 2 );
    primes.push_back( 3 );
    primes.push_back( 5 );
    int n = 3;
    while( 2*n*primes[n-1] <= limit )
    {
        get_next_prime();
        get_next_prime();
        n += 2;
    }
    cout << "n = " << n << " p(n) = " << primes[n-1] << endl;
}
