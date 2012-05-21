#include <iostream>
#include <cstdlib>
#include <set>
#include <map>

using namespace std;

/*
 * Project Euler: Problem 088 (http://projecteuler.net/problem=88)
 */

/***
A natural number, N, that can be written as the sum and product of a given set
of at least two natural numbers, {a_(1), a_(2), ... , a_(k)} is called
a product-sum number:
N = a_(1) + a_(2) + ... + a_(k) = a_(1) × a_(2) × ... × a_(k).

For example, 6 = 1 + 2 + 3 = 1 × 2 × 3.

For a given set of size, k, we shall call the smallest N with this property
a minimal product-sum number. The minimal product-sum numbers for sets of size,
k = 2, 3, 4, 5, and 6 are as follows.

k=2: 4 = 2 × 2 = 2 + 2
k=3: 6 = 1 × 2 × 3 = 1 + 2 + 3
k=4: 8 = 1 × 1 × 2 × 4 = 1 + 1 + 2 + 4
k=5: 8 = 1 × 1 × 2 × 2 × 2 = 1 + 1 + 2 + 2 + 2
k=6: 12 = 1 × 1 × 1 × 1 × 2 × 6 = 1 + 1 + 1 + 1 + 2 + 6

Hence for 2≤k≤6, the sum of all the minimal product-sum numbers is
4+6+8+12 = 30; note that 8 is only counted once in the sum.

In fact, as the complete set of minimal product-sum numbers for 2≤k≤12 is
{4, 6, 8, 12, 15, 16}, the sum is 61.

What is the sum of all the minimal product-sum numbers for 2≤k≤12000?
***/

// mininal product-sum = mps
// mps( k ) > k
// mps( k ) <= 2k since 1^(k-2)*2*k = k-2 + 2 + k = 2k !
// k+1 <= mps( k ) <= 2k, k values to check.
// Ignore prime numbers (need at least 2 prime factors).
// For n, k+1 <= n < 2k, decompose n in prime factors:
// n = p1^e1 * ... * pm^em with p1 < p2 <... < pm
// a+b <= a*b


static set<int> primes;

void build_primes( int limit )
{
    cout << "Building primes up to " << limit << "..." << endl;
    primes.clear();
    primes.insert( 2 );
    for(int n = 3; n <= 2*limit; n+=2) {
        bool is_prime = true;
        for( set<int>::iterator it = primes.begin();
             ( it != primes.end() )&&( is_prime ); ++it ) {
            is_prime = ( n % *it != 0 );
        }
        if (is_prime) {
            primes.insert( n );
            //cout << "Prime: " << n << endl;
        }
    }
    cout << "... done!" << endl;
}


// Decompose n into a vector of its prime factors
void decomp( int n, multiset<int>& ms )
{
    ms.clear();

    //cout << "Decomposition of " << n << " = ";
    int nn = n;

    for( set<int>::iterator it = primes.begin(); 
         ( it != primes.end() ) && ( *it <= nn ); ++it ) {
        while ( (nn % (*it)) == 0 ) {
            nn /= (*it);
            ms.insert( *it );
            //cout << *it << " ";
        }
    }
    //cout << endl;
}

int main( int argc, char** argv )
{
    int limit = 12000;
    if ( argc > 1 ) limit = atoi( argv[ 1 ] );

    build_primes( limit );

    map< int, int > mps;
    for( int k = 2; k <= limit; ++k ) mps[ k ] = 2*k; // Set upper bounds

    for( int n = 3; n < 2*limit; ++n ) {
        //cout << endl << "### Checking " << n << "..." << endl;
        multiset< int > ms;
        decomp( n, ms );
        if ( ms.size() > 1 ) { // ignore prime numbers
            // Go through every possible decomposition of n into at least
            // 2 factors (f factors). There are at most v.size() factors.
            // n = sum(factors) + (n-sum(factors))*1
            // Number of terms in sum: kk = f + n -sum(factors)
            // if mps[kk] > n then better solution found: set mps[kk] to n.
            // Use multisets?
            set< multiset< int > > factorisations;
            factorisations.insert( ms );
            set< multiset< int > >::iterator it = factorisations.begin();
            while( it != factorisations.end() ) {
                multiset< int >::iterator jt;
                int sum = 0; 
                for( jt = it->begin(); jt != it->end(); ++jt ) {
                    //cout << *jt << "+";
                    sum += *jt;
                }
                //cout << "(" << n - sum << ") = " << n;
                int kk = it->size() + n - sum;
                if ( mps[ kk ] > n ) {
                    //cout << " => mps[" << kk << "] = " << n;
                    mps[ kk ] = n;
                }
                //cout << endl;
                // Generating factorisations with it->size()-1 terms and
                // inserting them in the factorisations set.
                multiset< int > m2;
                for(unsigned int i = 0; i < it->size()-1; ++i) {
                    jt = it->begin();
                    for(unsigned int ii = 0; ii < i; ++ii) ++jt;
                    for(unsigned int j = i+1; j < it->size(); ++j) {
                        multiset< int >::iterator kt = it->begin();
                        for(unsigned int jj = 0; jj < j; ++jj ) ++kt;
                        m2.clear();
                        multiset< int >::iterator lt = it->begin();
                        for( ; lt != it->end(); ++lt ) {
                            if ( lt == jt ) {
                                m2.insert( (*jt) * (*kt) );
                            } else if ( lt != kt ) {
                                m2.insert( *lt );
                            }
                        }
                        if ( m2.size() > 1 ) { factorisations.insert( m2 ); }
                    }
                }
                ++it;
            }
        }
    }

    // We are only considering DISTINCT minimal product-sum numbers, so:
    cout << endl;
    set< int > distinct_mps;
    for( int k = 2; k <= limit; ++k )
    {
        //cout << "mps[" << k << "] = " << mps[k] << endl;
        distinct_mps.insert( mps[ k ] );
    }
    //cout << endl;

    int sum = 0;
    for( set<int>::iterator it = distinct_mps.begin();
         it != distinct_mps.end(); ++it )
    {
        sum += (*it);
    }

    cout << endl 
         << "Sum of all distinct minimal product-sum number for 2 <= k <= "
         << limit << " = " << endl;
    cout << "Answer: " << sum << endl;
    return 0;
}

