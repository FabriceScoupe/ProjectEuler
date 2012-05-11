#include <iostream>
#include <strings.h>
using namespace std;

// Starting with 1 and spiralling anticlockwise in the following way,
// a square spiral with side length 7 is formed.
//
// 37 36 35 34 33 32 31
// 38 17 16 15 14 13 30
// 39 18  5  4  3 12 29
// 40 19  6  1  2 11 28
// 41 20  7  8  9 10 27
// 42 21 22 23 24 25 26
// 43 44 45 46 47 48 49
//
// It is interesting to note that the odd squares lie along the bottom right
// diagonal, but what is more interesting is that 8 out of the 13 numbers 
// lying along both diagonals are prime; that is, a ratio of 8/13 ~ 62%.
//
// If one complete new layer is wrapped around the spiral above, 
// a square spiral with side length 9 will be formed. If this process is
// continued, what is the side length of the square spiral for which the ratio
// of primes along both diagonals first falls below 10%?


// Corners: TR=(n-2)^2+(n-1) TL=TR+(n-1) BL=TL+(n-1) BR=BL+(n-1)=n^2
// So BR never prime.
// TR = n^2 - 3n + 3
// TL = n^2 - 2n + 2
// BL = n^2 -  n + 1 
//
// For n odd, number of integers on diagonals = 1 + 2(n-1)
// Ratio to surface = ( 1 + 2(n-1) ) / n^2
//
// Using http://en.wikipedia.org/wiki/Prime_number_theorem:
// Average gap between prime numbers near N is roughly ln(N)
// Near N, change of number being prime ~ 1/ln(N). (Erdos-Kac?)

char sieve[ 62501 ]; // to detect all primes up < 1000000

void buildSieve()
{
    cout << "Building sieve..." << endl;
    memset( sieve, 0, 62501 );
    long long iter = 0;
    for( int i = 3; i <= 333333; i+=2 )
    {
        for( int j = 3; i*j <= 1000000; j += 2 )
        {
            if ( ++iter % 100000 == 0 ) { cout << "."; flush( cout ); }
            long long m = i*j/2;
            sieve[ m/8+(m%8?0:1) ] |= 1<<(m%8);
        }
    }
    cout << endl;
}

bool isPrime( long long p );

int nextPrime( int p )
{
    int q = p+2;
    while( ( q < 1000000 ) && ( !isPrime( q ) ) ) q+=2; // not subtle.
    if ( q >= 1000000 ) q = -1;
    return q;
}

bool isPrime( long long p )
{
    bool ok = false;
    if ( p < 1000000 )
    {
        long long q = p / 2;
        ok = ( ( 2 == p ) ||
               ( ( p % 2 ) && ! ( sieve[q/8+(q%8?0:1)] & 1<<(q%8) ) ) );
    }
    else
    {
        ok = true;
        for( long long d = 3; (d>0)&&( d*d < p ); d = nextPrime( d ) )
        {
            if ( p % d == 0 )
            {
                ok = false;
                break;
            }
        }
    }
    return ok;
}

int main( int argc, char** argv )
{
    buildSieve();

    bool got_there = false;
    int  nd = 1;
    int  np = 0;
    int  n  = 1;
    long long tr,tl,bl;
    while( ! got_there )
    {
        n += 2;
        nd = 1 + 2*(n-1);
        tr = n*n - 3*n + 3;
        tl = tr + n - 1;
        bl = tl + n - 1;

        if ( isPrime( tr ) ) ++np;
        if ( isPrime( tl ) ) ++np;
        if ( isPrime( bl ) ) ++np;

        int ratio = 100*np / nd;
        cout << "Ratio(" << n << ")=" 
             << np << " / " << nd << " = "
             << ratio << "%" << endl;
        got_there = ( ratio < 10 );
    }
}
