#include <iostream>
#include <cstdlib>
#include <cstring>
using namespace std;

/*
 * Considering 4-digit primes containing repeated digits it is clear that
 * they cannot all be the same: 1111 is divisible by 11, 2222 is divisible
 * by 22, and so on. But there are nine 4-digit primes containing three ones:
 * 1117, 1151, 1171, 1181, 1511, 1811, 2111, 4111, 8111
 * We shall say that M(n, d) represents the maximum number of repeated digits
 * for an n-digit prime where d is the repeated digit, N(n, d) represents the
 * number of such primes, and S(n, d) represents the sum of these primes.
 *
 * So M(4, 1) = 3 is the maximum number of repeated digits for a 4-digit prime
 * where one is the repeated digit, there are N(4, 1) = 9 such primes, and the
 * sum of these primes is S(4, 1) = 22275. It turns out that for d = 0, it is
 * only possible to have M(4, 0) = 2 repeated digits, but there are
 * N(4, 0) = 13 such cases.
 *
 * For d = 0 to 9, the sum of all S(4, d) is 273700.
 *
 * Find the sum of all S(10, d).
 */

// 1111111111 = 11 * 101010101 so S(10,d) < 10 for any digit d.
// Try and find M(10,d) for all digits d.
// Test numbers: dddddddddx, ddddddddxd, ... xddddddddd for x != d
// Assume M(10, d) = 9, try and find d.
// For 0, x00000000y, with x and y != 0.
// Prime factorisation of 10-digit number => need 5-digit primes.
// (calculate all primes up to 100,000)

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

bool is_prime(unsigned long long n)
{
    if (n % 2 == 0) return false;
    for(unsigned long long p = 3; p*p <= n; p = next_prime(p)) {
        if ((n % p) == 0) return false;
    }
    return true;
}

unsigned long long make_integer(unsigned char* digit_array, unsigned int len)
{
    unsigned long long pow10 = 1ULL;
    unsigned long long n = 0ULL;
    for(unsigned int i = 0; i < len; ++i) {
        n += pow10*digit_array[i];
        pow10 *= 10;
    }
    return n;
}

int main(int argc, char* argv[])
{
    int ndigits = 10;
    if (argc > 1) ndigits = atoi(argv[1]);
    if (ndigits > 10) ndigits = 10;
    // Build prime numbers, enough to factorise 10-digit numbers
    build_sieve(150000);

    unsigned char digits[10];
    unsigned char m10[10];
    unsigned int  n10[10];
    unsigned long long s10[10];
    unsigned long long tmp_n = 0;

    for(unsigned int i = 0; i < 10; ++i) {
        m10[i] = 0;
        n10[i] = 0;
        s10[i] = 0;
    }

    for(unsigned char d = 0; d <= 9; ++d) {
        for(int i = 0; i < ndigits; ++i) digits[i] = d;
        // Try replacing only one digit
        for(int i = 0; i < ndigits; ++i) {
            for(unsigned char e = 0; e <= 9; ++e) {
                if (e == d) continue;
                digits[i] = e;
                tmp_n = make_integer(digits, ndigits);
                if ((digits[ndigits-1] > 0) && is_prime(tmp_n)) {
                    m10[d] = ndigits-1;
                    ++n10[d];
                    s10[d] += tmp_n;
                }
                digits[i] = d;
            }
        }

        if (m10[d] == 0) {
            // Try replacing two digits
            for(int i = 0; i < ndigits; ++i) {
                for(int j = i+1; j < ndigits; ++j) {
                    for(unsigned char e = 0; e <= 9; ++e) {
                        if (e == d) continue;
                        digits[i] = e;
                        for(unsigned char f = 0; f <= 9; ++f) {
                            if (f == d) continue;
                            digits[j] = f;
                            tmp_n = make_integer(digits, ndigits);
                            if ((digits[ndigits-1] > 0) && is_prime(tmp_n)) {
                                //cout << tmp_n << " is prime!" << endl;
                                m10[d] = ndigits-2;
                                ++n10[d];
                                s10[d] += tmp_n;
                            }
                            digits[j] = d;
                        }
                        digits[i] = d;
                    }
                }
            }
        }
        // Assume that we don't need to change more digits...!

        cout << "m(" << ndigits << "," << (int)d <<")=" << (int) m10[d] << endl;
        cout << "n(" << ndigits << "," << (int)d <<")=" << n10[d] << endl;
        cout << "s(" << ndigits << "," << (int)d <<")=" << s10[d] << endl;
    }
    unsigned long long sum = 0ULL;
    for(int i = 0; i <= 9; ++i) sum += s10[i];
    cout << "Sum = " << sum << endl;

    delete[] sieve;
    return 0;
}
