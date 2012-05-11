#include <iostream>
#include <cstdlib>
#include <vector>
#include <map>
using namespace std;

// Like 69, about Euler's Totient function, ie number of positive numbers less
// than or equal to n which are relatively prime to n.
// Phi(87109)=79180 (digit permutation).
//
// Find the value of n 1 < n < 10^7, for which phi(n) is a permutation of
// n and the ratio n/phi(n) produces a minimum.

// phi(n) < n for n > 1 so n/phi(n) > 1
// Not a prime number: phi(p)=p-1, and p-1 cannot be a permutation of p (unless
// it ends with 0, and then not prime). For primes, p/phi(p) -> 1 (converges
// towards minimum minimorum, 1).
// phi(n) linked to prime decomposition of n = Prod[k=1..m]Pk^Mk:
// phi(n)=n.Prod[p|n](p-1)/p
// n/phi(n) = Prod[p|n] p/(p-1) => look for "large" primes in decomp, but as
// few as possible.
// phi(n) has as many digits as n => the Prod must be > 1/10
// n cannot be a power of a single prime:
// phi(n = p^r) = p^r.(p-1)/p = p^r - p^(r-1) but p^(r-1) not multiple of 9,
// so phi(p^r) cannot be a permutation of p^r (well, except if p is 3, but
// then n/phi(n) = 3/2 = 1.5, not optimal in considered range).
// So: try a product of two primes p1 and p2 (p1 and p2 as big as possible).
// Then of three distinct primes, etc...

void makePrimeSet( int limit, vector<int>& primes )
{
    cout << "Building prime set..." << endl;
    primes.clear();
    primes.push_back( 1 ); // not a prime, but helps
    primes.push_back( 2 );
    for( int p = 3; p*p < limit; p += 2 )
    {
        bool yes = true;
        for( int i = 1; yes && (i < primes.size()); ++i )
        {
            yes = ( p % primes[i] != 0 );
        }
        if ( yes )
        {
            primes.push_back( p );
            //cout << p << " prime." << endl;
        }
    }
}

int digits_in_order( int n )
{
    map< char, char > m;
    int p = n;
    while( p > 0 )
    {
        ++m[ p % 10 ];
        p /= 10;
    }
    for( map<char,char>::iterator it = m.begin(); it != m.end(); ++it )
    {
        while( it->second > 0 )
        {
            p *= 10;
            p += it->first;
            --(it->second);
        }
    }
    return p;
}

int main( int argc, char** argv )
{
    // This is a crappy solution, but it just happens to find the
    // right answer. Ah well...

    int limit = 10000000;
    if ( argc > 1 ) limit = atoi( argv[ 1 ] );
    vector<int> p;
    makePrimeSet( 100*limit, p );
    cout << p.size() << " primes in vector." << endl;
    // n = p1 * p2 
    // phi(n) = p1 * p2 * (p1-1)/p1 * (p2-1)/p2 = (p1-1)*(p2-1);
    int min_n   = 2;
    int min_phi = 1;

    for( int i1 = p.size()-1; i1 >= 1; --i1 )
    {
        for( int i2 = 1;
             (i2 <= i1 )&&(p[i1]*p[i2]<limit);
             ++i2)
        {
            for( int i3 = 0;
                 (i3 <= i2)&&(p[i1]*p[i2]*p[i3]<limit);
                 ++i3 )
            {
                int n123   = p[i1]*p[i2]*p[i3];
                int phi123 = (p[i1]-1)*(p[i2]-1)*(p[i3]==1?1:p[i3]-1);
                if ( digits_in_order( n123 ) == digits_in_order( phi123 ) )
                {
                    cout << "phi(" << n123 << "=" 
                         << p[i1] << " * " << p[i2] << " * " << p[i3]
                         << ")=" << phi123;
                    // n1 / phi1 < n2 / phi2 <=> n1*phi2 < n2*phi1
                    long long left  = (long long)(n123)*(long long)(min_phi);
                    long long right = (long long)(min_n)*(long long)(phi123);
                    if ( left < right )
                    {
                        min_n   = n123;
                        min_phi = phi123;
                    }
                    cout << " (min n so far = " << min_n << ")" << endl;
                }
            }
        }
    }
}
