#include <iostream>
#include <cstdlib>
#include <set>
#include <vector>

using namespace std;

// Proper fraction n / d, n < d, n and d relatively prime.
// Number of elements in proper fraction set PF(d) = { proper fractions with
// denominator <= d }.
// card PF(8) = 21.
// card PF(1000000) ?

// Remember: number of numbers n such that n < d and n and d relatively
// is Euler's Totient function(n).
// For given denominator d, there are phi(d) proper fractions.
// So card PF(d) = sum[k=2..d] phi(k).
// phi(k) = k.Prod[p|k](p-1)/p (p prime).
//
// Total fractions to consider: d(d-1)/2 (triangle number).
// => brute force useless.
//
// 

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

char sieve[ 62501 ]; // to detect all primes up < 1000000

void buildSieve()
{
    cout << "Building sieve..." << endl;
    memset( sieve, 0, 62501 );
    long long iter = 0;
    for( long long i = 3; i <= 333333; i+=2 )
    {
        for( long long j = 3; i*j <= 1000000; j += 2 )
        {
            if ( ++iter % 100000 == 0 ) { cout << "."; flush( cout ); }
            long long m = (i*j)/2;
            sieve[ m/8+(m%8?0:1) ] |= 1<<(m%8);
        }
    }
    cout << endl;
}

bool isPrime( long long p );

long long nextPrime( long long p )
{
    if ( 2 == p ) return 3;
    long long q = p+2;
    while( ( q < 1000000 ) && ( !isPrime( q ) ) ) q+=2; // not subtle.
    if ( q >= 1000000 ) q = -1;
    return q;
}

bool isPrime( long long p )
{
    long long q = p / 2;
    return ( ( 2 == p ) ||
             ( ( p % 2 ) && ! ( sieve[q/8+(q%8?0:1)] & 1<<(q%8) ) ) );
}

vector< long long > primes;
// Property of totient: if a and b rel. prime, phi(ab)=phi(a).phi(b)
long long totient( long long n )
{
    long long phi = 1;

    if ( isPrime( n ) )
    {
        phi = n-1;
    }
    else
    {
        long long nn = n;
        long long m  = 1;
        for( int i = 0; primes[i] <= nn; ++i )
        {
            long long p = primes[i];
            if ( nn % p == 0 )
            {
                while( nn % p == 0 ) nn /= p;
                phi *= p - 1;
                m   *= p;
            }
        }
        phi *= n / m;
    }
    return phi;
}

int main( int argc, char** argv )
{
    int limit = 1000000;
    if ( argc > 1 ) limit = atoi( argv[ 1 ] );
    buildSieve();
    primes.push_back(2);
    long long p = 3;
    do
    {
        primes.push_back( p );
        p = nextPrime( p );
    }
    while( ( p > 0 ) && ( p <= limit ) );
    cout << primes.size() << " primes <= " << limit << endl;

    long long num_frac = limit;
    num_frac *= limit-1;
    num_frac /= 2;
    cout << "Total number of fractions: " << num_frac << endl;

    // Brute force
    if ( limit <= 10000 )
    {
        set< Fraction > s;
        long long iter = 0;
        for( int d = 2; d <= limit; ++d )
        {
            for( int n = 1; n < d; ++ n )
            {
                s.insert( Fraction( n, d ) );
                ++iter;
            }
        }

        cout << s.size() << " proper fractions for d <= " << limit << endl;
        cout << iter << " fractions considered." << endl;
        
        double ratio = (double) s.size() / (double) iter;
        cout << "Ratio: " << ratio << endl;
        // Ratio of proper fractions / all possible fractions "seems" to
        // converge to ~3/5 as d -> +infinity (?)
    }

    // The actual problem, using Totient.
    long long totient_sum = 0;
    for( long long d = 2; d <= limit; ++d )
    {
        totient_sum += totient( d );
        if ( d % 1000 == 0 ) { cout << '.'; flush( cout ); }
    }
    cout << endl << "Sum[k=2.." << limit << "] totient(k) = " 
         << totient_sum << endl;
}
