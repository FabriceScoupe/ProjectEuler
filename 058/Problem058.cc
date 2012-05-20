#include <iostream>
#include <string.h>
using namespace std;

/*
 * Project Euler: Problem 058 (http://projecteuler.net/problem=58)
 */

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

unsigned char* sieve = NULL;

void buildSieve(unsigned long long max)
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

// Only works for p >= 3
unsigned long long next_prime(unsigned long long p)
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

bool isPrime(unsigned long long p, unsigned long max)
{
    if (2 == p) return true;
    if (p % 2 == 0) return false;
    if (p < max) {
        return ((sieve[(p-1)/16] & (1 << (((p-1)/2)%8))) == 0);
    }
    for(unsigned long long q = 3; q*q <= p; q = next_prime(q)) {
        if (p % q == 0) return false;
    }
    return true;
}

int main(int argc, char** argv)
{
    unsigned long long max = 1000000;
    buildSieve(max);

    bool got_there = false;
    int  nd = 1;
    int  np = 0;
    int  n  = 1;
    int  ratio = 0;
    unsigned long long tr = 0;
    unsigned long long tl = 0;
    unsigned long long bl = 0;
    while(!got_there)
    {
        n += 2;
        nd = 1 + 2*(n-1);
        tr = n*n - 3*n + 3;
        tl = tr + n - 1;
        bl = tl + n - 1;

        if (isPrime(tr, max)) ++np;
        if (isPrime(tl, max)) ++np;
        if (isPrime(bl, max)) ++np;

        ratio = 100*np / nd;
        got_there = ( ratio < 10 );
    }
    cout << "Ratio("<<n<<")="<<np<<" / "<<nd<<" = "<< ratio << "%" << endl;
    cout << "Answer: " << n << endl;
    delete[] sieve;
    return 0;
}
