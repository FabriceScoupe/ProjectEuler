#include <iostream>
#include <iomanip>
#include <cstdlib>
using namespace std;

/*
 * Project Euler: Problem 162 (http://projecteuler.net/problem=162)
 */

// Inclusion-exclusion principle:
// See: https://en.wikipedia.org/wiki/Inclusion-exclusion_principle
// (Sieve principle)

// |A u B| = |A| + |B| - |A ^ B|
// |A u B u C| = |A| + |B| + |C| - |A ^ B| - |B ^ C| - |C ^ A| + |A ^ B ^ C|
// 16^n n-digit hex numbers.
// 15*16^(n-1) of those NOT starting with 0
// A: Numbers without any 1 in them 14*15^(n-1) (neither 0 nor 1 at the start)
// B: Numbers without any A in them 14*15^(n-1) (neither 0 nor A at the start)
// C: Numbers without any 0 in them 15^n        (not 0 at the start)
// A^C: Without any 0 nor 1: 14^n
// B^C: Without any 0 nor A: 14^n
// A^B: Without any 1 nor A: 13*14^(n-1)
// A^B^C: Without 0, 1 nor A: 13^n
// AuBuC: Without any 0 or without any 1 or without any A
// Complementary of AuBuC is what we're after:
// with at least one 0 AND at least one 1 AND at least one A.
//
// |AuBuC|=2*14*15^(n-1)+15^n-2*14^n-13*14^(n-1)+13^n
//        = 43*15^(n-1)-41*14^(n-1)+13^n

// so count=15*16^(n-1)-43*15^(n-1)+41*14^(n-1)-13^n

unsigned long brute_force(unsigned long long n) {
    unsigned long long count = 0;
    for(unsigned long long i = 1; i <= n; ++i) {
        int n_0 = 0;
        int n_1 = 0;
        int n_A = 0;
        unsigned long long ii = i;
        int d = 0;
        while(ii > 0) {
            d = ii % 16;
            switch(d) {
                case 0 : ++n_0; break;
                case 1 : ++n_1; break;
                case 10 : ++n_A; break;
                default: break;
            }
            ii /= 16;
        }
        // Number of 0s, 1s and As all >= 1:
        if ((n_0 >= 1)&&(n_1 >= 1)&&(n_A >= 1)) {
            //cout << uppercase << hex << i << endl;
            ++count;
        }
    }
    return count;
}

int main(int argc, char* argv[])
{
    int n_max = 16;
    if (argc > 1) n_max = atoi(argv[1]);

    unsigned long long count = 0ULL;

    if (n_max <= 6) {
        cout << "Brute force: " << dec << brute_force(1<<(4*n_max)) << endl;
    }
    // so count=15*16^(n-1)-43*15^(n-1)+41*14^(n-1)-13^n
    unsigned long p16 = 1;
    unsigned long p15 = 1;
    unsigned long p14 = 1;
    unsigned long p13 = 13;
    for(int n = 0; n < n_max-1; ++n) {
        p16 *= 16; p15 *= 15; p14 *= 14; p13 *= 13;
        count += 15*p16-43*p15+41*p14-p13;
    }

    cout << "Decimal answer: " << count << endl;
    cout << "Answer: " << uppercase << hex << count << endl;
    return 0;
}
