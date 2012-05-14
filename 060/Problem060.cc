#include <iostream>
#include <cstring>
#include <set>
#include <map>
#include <vector>
using namespace std;

// The primes 3, 7, 109, and 673, are quite remarkable.
// By taking any two primes and concatenating them in any order
// the result will always be prime.
// For example, taking 7 and 109, both 7109 and 1097 are prime.
// The sum of these four primes, 792, represents the lowest sum for a set
// of four primes with this property.
// Find the lowest sum for a set of five primes for which any two primes
// concatenate to produce another prime.
//
unsigned char* sieve = NULL; // to detect all primes up < 10000000

void buildSieve(unsigned long long max)
{
    cout << "Building sieve..." << endl;
    sieve = new unsigned char[(max/16)+1];
    memset( sieve, 0, (max/16)+1);
    for(unsigned long long n = 3; n*n <= max; n += 2) {
        for(unsigned long long m = 3*n; m <= max; m += 2*n) {
            sieve[(m-1)/16] |= 1 << (((m-1)/2)%8);
        }
    }
}

// Only works for p >= 3
unsigned long long nextPrime(unsigned long long p)
{
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

bool isPrime(unsigned long long p, unsigned long long max)
{
    static set<unsigned long long > big_prime_cache; // memoization

    if (2 == p) return true;
    if (p % 2 == 0) return false;

    bool ok = false;
    if (p < max) {
        ok = ((sieve[(p-1)/16] & (1 << (((p-1)/2)%8))) == 0);
    } else if ( big_prime_cache.find( p ) != big_prime_cache.end() ) {
        ok = true;
    } else {
        ok = true;
        for(unsigned long long d = 3; ok && (d*d <= p); d = nextPrime(d)) {
            ok = (p % d != 0);
        }
        if (ok) big_prime_cache.insert(p);
    }
    return ok;
}

long long power10shift( long n, int& sumdigits )
{
    long long pw = 1;
    long long m  = n;
    sumdigits = 0;
    while(m > 0) {
        sumdigits += m % 10;
        pw *= 10;
        m /= 10;
    }
    return pw;
}

bool test(long long a, long long b, long long max)
{
    static pair< long long, long long > tmp_p;
    static map< pair< long long, long long >, bool > cache;
    tmp_p.first = a; tmp_p.second = b;
    map< pair< long long, long long >, bool >::iterator cit =
        cache.find( tmp_p );
    if ( cit != cache.end() ) return cit->second;

    int sa = 0;
    long long pw_a = power10shift( a, sa );
    int sb = 0;
    long long pw_b = power10shift( b, sb );
    if ((sa + sb) % 3 == 0) { // Quick rule-out
        cache[tmp_p] = false;
        return false;
    }
    long long ab = a*pw_b + b;
    long long ba = b*pw_a + a;
    bool ok = (isPrime(ab, max) && isPrime(ba, max));
    cache[ tmp_p ] = ok;
    return ok;
}

int main( int argc, char** argv )
{
    unsigned long long max = 10000000;
    buildSieve(max);
    vector< int > primes;
    for(int p = 3; p < 10000; p = nextPrime(p)) primes.push_back(p);
    int psize = primes.size();
    cout << psize << " candidate primes under 10000." << endl;

    int idx[5]; // array of index to primes
    idx[0] = -1; idx[1] = -1; idx[2] = -1; idx[3] = -1; idx[4] = -1;
    int d = 0;
    int min = 30000;
    int sum = 0;
    while((idx[0] < psize-4) && (primes[idx[0]] < min)) {
        // Go to next "valid" prime
        bool found = false;
        while((idx[d] < psize-1) && ! found) {
            ++idx[d];
            if ( (5-d)*primes[ idx[ d ] ]+sum >= min ) break;
            found = true;
            for( int i = 0; found && (i < d); ++i ) {
                found = test( primes[idx[i]], primes[idx[d]], max);
            }
        }

        if ( found ) {
            sum += primes[ idx[ d ] ];
            if ( 4 == d ) {
                cout << endl;
                for( int i = 0; i <= d; ++i ) {
                    //cout << primes[ idx[ i ] ] << " ";
                }
                //cout << " (" << sum << ")" << endl;
                if ( sum < min ) min = sum;
                d = 0; // Rollback to depth 0
                sum = 0;
            } else { // Go deeper
                //cout << '+'; flush( cout );
                ++d;
                idx[ d ] = idx[ d-1 ];
            }
        } else if ( d > 0 ) { // Rollback one level
            //cout << 'R'; flush( cout );
            --d;
            sum -= primes[ idx[ d ] ];
        }
        //if ( 0 == d ) { cout << primes[ idx[ 0 ] ] << "\t"; flush( cout ); }
    }
    cout << "Min is " << min << endl;

    return 0;
}
