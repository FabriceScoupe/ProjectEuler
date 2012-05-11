#include <iostream>
#include <strings.h>

using namespace std;

// Find the smallest prime which, by replacing the same part of the
// number with the same digit, can form eight different primes.
// Ex: *3 -> 13,23,43,53,73, and 83 all primes.
// Or: 56**3 -> 56003, 56113, 56333, 56443, 56663, 56773 and 56993

// Masks for the patterns: 1 meaning *, 0 same => 56003 and 56113, mask is 
// 00110, or binary 6. All masks other than 11111 (31) and 00000 are ok, so
// 30 possibilities (mask 00001 to 11110).
// Store pattern "hit" as say 56003, with 0 meaning *. Map of patterns.

// Assuming that this prime is under 1000000 (5 or 6 digit- prime).
char sieve[ 62501 ]; // to detect all primes up < 1000000

void buildSieve()
{
    memset( sieve, 0, 62501 );
    for( int i = 3; i <= 333333; i+=2 )
    {
        for( int j = 3; i*j <= 1000000; j += 2 )
        {
            int m = i*j/2;
            sieve[ m/8+(m%8?0:1) ] |= 1<<(m%8);
        }
    }
}

bool isPrime( int p )
{
    int q = p / 2;
    return( ( 2 == p ) ||
            ( ( p % 2 ) && ! ( sieve[q/8+(q%8?0:1)] & 1<<(q%8) ) ) );
}

int nextPrime( int p )
{
    int q = p+1;
    while( ( q < 1000000 ) && ( !isPrime( q ) ) ) ++q; // not subtle.
    if ( q >= 1000000 ) q = -1;
    return q;
}

int base2to10( char b2 )
{
    char c = b2;
    int pw10 = 1;
    int b10 = 0;
    while( c > 0 )
    {
        b10 += ( c % 2 )*pw10;
        pw10 *= 10;
        c = c>>1;
    }
    return b10;
}

int applyPattern( int a, int p )
{
    int ta = a;
    int tp = p;
    int pw10 = 1;
    int res = 0;
    while( ta > 0 )
    {
        char da = ta % 10;
        char dp = tp % 10;
        if ( 0 == dp ) res += da*pw10;
        pw10 *= 10;
        ta /= 10;
        tp /= 10;
    }
    return res;
}

void buildPatternMap( char nd, int& max_count,int& max_prime,int& max_pattern )
{
    int pw10 = 1;
    for( int i = 1; i < nd; ++i ) pw10 *= 10;
    for( int p = nextPrime( pw10 ); (p>0)&&(p<pw10*10); p = nextPrime( p ) )
    {
        for( char m = 1; m < (1<<nd)-1; ++m )
        {
            int pattern = base2to10( m );
            int base = applyPattern( p, pattern );
            int count = 0;
            int prime = 0;
            for( int tmp_p = base+9*pattern; tmp_p >= base; tmp_p-=pattern )
            {
                if ( ( tmp_p > pw10 ) && ( isPrime( tmp_p ) ) )
                {
                    prime = tmp_p;
                    ++count;
                }
            }
            if ( count > max_count )
            {
                max_count   = count;
                max_prime   = prime;
                max_pattern = pattern;
                cout << "base: " << prime 
                     << " pattern: " << pattern << " ("<<count<<")" << endl;
                if ( count == 8 ) exit(0); // We're done.
            }
        }
    } 
}

int main( int argc, char** argv )
{
    buildSieve();
    int max_count   = 0;
    int max_prime   = 0;
    int max_pattern = 0;
    buildPatternMap( 2, max_count, max_prime, max_pattern );
    buildPatternMap( 3, max_count, max_prime, max_pattern );
    buildPatternMap( 4, max_count, max_prime, max_pattern );
    buildPatternMap( 5, max_count, max_prime, max_pattern );
    buildPatternMap( 6, max_count, max_prime, max_pattern );
}
