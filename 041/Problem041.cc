#include <iostream>
#include <cstdlib>
#include <string.h>
using namespace std;

/*
 * Project Euler: Problem 041 (http://projecteuler.net/problem=41)
 */

// What is the largest n-digit pandigital prime that exists?
// (Eg: 2143 is a 4-digit pandigital prime, uses 1..4 exactly once).
// 987654321 largest pandigital integer.
// No 5-digit pandigital prime (1+2+3+4+5 = 15 multiple of 3)
// No 6-digit, 8-digit or 9-digit pandigital prime (same reason)
// So 7654321 max 
// Look for 7-digit ones (possibilities 7! - 4.6!, since it can't end
// with 2,4,5, or 6, so 5040 - 4*720 = 2160 numbers to test.
//
// Create sieve for numbers from 1234567 to 7654321
// Re-use problem 24 for lexicographic permutations.

char sieve[1000001];

static inline bool isPrime( int p )
{
    return( ( 2 == p ) ||
            ( ( p % 2 ) && ! ( sieve[p/8+(p%8?0:1)] & 1<<(p%8) ) ) );
}

void BuildSieve( )
{
    cout << "Creating sieve..." << endl;
    memset( sieve, 0, 1000001 );
    for( int i = 3; i < 4000000; i+=2 ) {
        for( int j = 2; i*j <= 8000000; ++j ) {
            int m = i*j;
            sieve[m/8+(m%8?0:1)] |= 1<<(m%8);
        }
    }
}

static inline void swap( char& a, char& b )
{
    char tmp = a; a = b; b = tmp;
}

// Reversing set
void reverse( char* set, int length )
{
    for( int i = 0; 2*i < length; ++i ) swap( set[i], set[ length -1 - i ] );
}

// Get next permutation in set, or return false if last one reached.
bool next_perm( char* set, int dim )
{
    bool ok = false;
    if ( dim > 2 ) {
        ok = next_perm( set + 1, dim - 1 );
        if ( ! ok ) {
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

int main( int argc, char** argv )
{
    BuildSieve();
    int max = 0;
    char n[8];
    // Checking 4-digit pandigital numbers
    strcpy( n, "1234" );
    do {
        if ((n[3]!='2')&&(n[3]!='4')) {
            int p = atoi( n );
            if ( isPrime( p ) ) {
                max = p;
                //cout << "Found: " << p << endl;
            }
        }
    }
    while( next_perm( n, 4 ) );
    
    // Checking 7-digit pandigital numbers
    strcpy( n, "1234567" );
    do {
        if ((n[6]!='2')&&(n[6]!='4')&&(n[6]!='5')&&(n[6]!='6')) {
            int p = atoi( n );
            if ( isPrime( p ) ) {
                max = p;
                //cout << "Found: " << p << endl;
            }
        }
    } while( next_perm( n, 7 ) );
    cout << endl << "Answer: " << max << endl;
    return 0;
}
