#include <iostream>
#include <cstdlib>
#include <cstring>
#include <set>
#include <vector>
using namespace std;

/*
 * Project Euler: Problem 072 (http://projecteuler.net/problem=72)
 */

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

unsigned char *sieve = NULL; // to detect all primes up < 1000000

void buildSieve(unsigned long max)
{
    cout << "Building sieve..." << endl;
    sieve = new unsigned char[(max/16)+1];
    memset(sieve, 0, (max/16)+1);
    for(unsigned long long n = 3; n*n <= max; n += 2) {
        for(unsigned long long m = 3*n; m <= max; m += 2*n) {
            sieve[(m-1)/16] |= 1 << (((m-1)/2)%8);
        }
    }
}

unsigned long long nextPrime(unsigned long long p)
{
    if (2 == p) return 3;
    unsigned long long n = 0;
    unsigned int index = (p-1)/16;
    unsigned int bit   = ((p-1)/2)%8;
    while(0 == n) {
        ++bit;
        if (bit >= 8) {
            ++index;
            bit = 0;
        }
        if ((sieve[index] & (1 << bit)) == 0) {
            n = 16*index+1+2*bit;
        }
    }
    return n;
}

bool isPrime(unsigned long long p)
{
    if (2 == p) return true;
    if (p % 2 == 0) return false;
    return((sieve[(p-1)/16] & (1<<(((p-1)/2)%8))) == 0);
}

// Property of totient: if a and b rel. prime, phi(ab)=phi(a).phi(b)
unsigned long long totient(unsigned long long n)
{
    unsigned long long phi = 1;

    if (isPrime(n)) {
        phi = n-1;
    } else {
        unsigned long long nn = n;
        unsigned long long m  = 1;
        for(unsigned long long p = 2; p <= nn; p = nextPrime(p)) {
            if (nn % p == 0) {
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
    buildSieve(limit);

    long long num_frac = limit;
    num_frac *= limit-1;
    num_frac /= 2;
    cout << "Total number of fractions: " << num_frac << endl;

    // Brute force
    if (limit <= 10000) {
        set< Fraction > s;
        long long iter = 0;
        for( int d = 2; d <= limit; ++d ) {
            for( int n = 1; n < d; ++ n ) {
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
    for( long long d = 2; d <= limit; ++d ) {
        totient_sum += totient(d);
        if (d % 1000 == 0) { cout << '.'; flush(cout); }
    }
    cout << endl << "Sum[k=2.." << limit << "] totient(k) = " << endl;
    cout << "Answer: " << totient_sum << endl;

    delete[] sieve;
    return 0;
}
