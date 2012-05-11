#include <iostream>
#include <map>
#include <set>
using namespace std;

// What is the smallest odd composite (non-prime) that cannot be written
// as the sum of a prime and twice a square?

// Test increasing odd numbers: test if prime, add to cache.
// Remove a square, then test if remainder prime (>=3)

static map<long long, long long> r_cache;
long long root( long long n )
{
    long long r = r_cache[ n ];
    if ( 0 == r )
    {
        r = 1;
        while( r*r < n ) ++r;
        r_cache[ n ] = r;
    }
    return r;
}


static set< long long > p_cache;
static long long max_prime;

bool isPrime( long long n ) // n always odd, so don't test 2
{
    bool ok = ( p_cache.find( n ) != p_cache.end() );
    if ( !ok && ( n > max_prime ) )
    {
        ok = true;
        long long r = root(n);
        for( set<long long>::iterator i = p_cache.begin();
             ( i != p_cache.end() ) && ok && ( *i <= r ); ++i )
        {
            ok = ( n % *i != 0 );
        }
        if ( ok )
        {
            p_cache.insert( n );
            max_prime = n;
        }
    }
    return ok;
}


int main( int argc, char** argv )
{
    long long n = 3;
    bool found = false;
    max_prime = 0;
    while( ! found )
    {
        if ( isPrime( n ) )
        {
            cout << n << " is prime." << endl;
            n += 2;
        }
        else
        {
            long long s = 0;
            long long r = 0;
            do
            {
                ++s;
                r = n - 2*s*s;
            }
            while( ( r > 3 ) && ( !isPrime( r ) ) );
            found = ( r < 3 );
            if ( ! found )
            {
                cout << n << " = " << r << " + 2 * " << s << "^2" << endl;
                n+=2;
            }
        }
    }
    cout << n << " is the one!" << endl;
}
