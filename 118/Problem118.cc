#include <iostream>
#include <cstring>
#include <cstdlib>
#include <sstream>
using namespace std;

/*
 * Project Euler: Problem 118 (http://projecteuler.net/problem=118)
 */

static unsigned char* sieve = NULL;

// Optimised Sieve of Erastothenes.
void build_sieve(unsigned long long max)
{
    cout << "Building sieve up to " << max << "..." << endl;
    sieve = new unsigned char[(max / 16)+1];
    memset(sieve, 0, (max / 16)+1);
    for(unsigned long long n = 3; n*n <= max; n += 2) {
        for(unsigned long long m = 3*n; m <= max; m += 2*n) {
            sieve[(m-1)/16] |= 1 << (((m-1)/2)%8);
        }
    }
    cout << endl;
}

static inline bool is_prime(unsigned long long n)
{
    return((2 == n) ||
           ((n > 2) && (n % 2 != 0) && 
            ((sieve[(n-1)/16] & (1 << (((n-1)/2)%8))) == 0))); 
}

static inline void swap(unsigned char& a, unsigned char& b)
{
    unsigned char tmp = a;
    a = b;
    b = tmp;
}

// Reversing set
static inline void reverse( unsigned char* set, int length )
{
    for( int i = 0; 2*i < length; ++i ) swap( set[i], set[ length -1 - i ] );
}

// (Permutator from problem 068) Here, dimension is 9.
static inline bool next_perm( unsigned char* set, int dim )
{
    bool ok = false;
    if ( dim > 2 ) {
        ok = next_perm( set + 1, dim - 1 );
        if (!ok) {
             // No next perm for set + 1 => set + 1 "reverse" ordered
             // Try and find smallest elem in set+1 greater than set[0]
             int pos = dim-1;
             while( ( pos > 0 ) && ( set[0] > set[pos] ) ) --pos;
             if ( pos > 0 ) {
                 swap( set[0], set[pos] );
                 // reverse order of set+1
                 reverse( set+1, dim-1 );
                 ok = true;
             }
        }
    } else if ( 2 == dim ) {
        ok = ( set[ 1 ] > set[ 0 ] );
        if ( ok ) swap( set[ 1 ], set[ 0 ] );
    }
    return ok;
}

static inline unsigned long long charset2int(unsigned char* s, int dim)
{
    unsigned long long n = 0;
    for (int i = 0; i < dim; ++i) {
        n *= 10;
        n += s[i];
    }
    return n;
}

int main(int argc, char* argv[])
{
    // Build prime numbers up to 100000000 (8 digit primes)
    // All 9-digit numbers with 1..9 cannot be a prime (digits sum to 45)
    build_sieve(100000000);

    unsigned char perm[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    unsigned int count = 0;

    // 9-digit permutation: abcdefghi
    // 0 to 8 commas in between => 8 bit, 0..255 range
    // 0000 0001 => 1 comma
    // 1111 1111 => 8 commas
    // 256 sets to test.
    do { // Loop over permutations of the 9 digits
        for(int st = 1; st < 256; ++st) { // Loop over sets
            stringstream out;
            unsigned int start  = 0;
            unsigned int length = 1;
            unsigned long long n = 0;
            bool ok = true;
            for(int i = 0; ok && (i < 8); ++i) {
                if ((st & (1 << i)) == 0) {
                    ++length;
                } else {
                    n = charset2int(&perm[start], length);
                    out << n << " ";
                    ok = is_prime(n);
                    start += length;
                    length = 1;
                }
            }
            if (!ok) continue;
            n = charset2int(&perm[start], length);
            out << n << endl;
            if (is_prime(n)) {
                ++count;
                cout << out.str();
            }
        }
    } while(next_perm(perm, 9));

    cout << "Answer: " << count << endl;
    return 0;
}
