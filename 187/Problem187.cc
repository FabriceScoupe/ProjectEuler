#include <iostream>
#include <cstdlib>
#include <string.h>

using namespace std;

/***
A composite is a number containing at least two prime factors.
For example, 15 = 3 × 5; 9 = 3 × 3; 12 = 2 × 2 × 3.

There are ten composites below thirty containing precisely two,
not necessarily distinct, prime factors:
4, 6, 9, 10, 14, 15, 21, 22, 25, 26.

How many composite integers, n < 10^(8), have precisely two,
not necessarily distinct, prime factors?
***/

static unsigned char* sieve;

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

unsigned long long nextPrime(unsigned long long p)
{
    if ( 2 == p ) return 3;
    unsigned int index = (p-1)/16;
    unsigned int bit   = ((p-1)/2)%8;
    unsigned long long n = 0;
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

int main( int argc, char** argv )
{
    int limit = 100000000;
    if ( argc > 1 ) limit = atoi( argv[ 1 ] );
    buildSieve(50000000);
    int count = 0;
    int a = 2;
    int b = 2;
    do {
        do {
            ++count;
            b = nextPrime( b );
        } while( ( b > 0 ) && ( a*b < limit ) );
        a = nextPrime( a );
        b = a;
    } while( ( a > 0 ) && ( a*b < limit ) );
    cout << "Number of semi-primes < " << limit << " = " << count << endl;
}
