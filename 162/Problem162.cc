#include <iostream>
#include <iomanip>
#include <cstdlib>
using namespace std;

/*
 * Project Euler: Problem 162 (http://projecteuler.net/problem=162)
 */

// Note: trinomial coeff C(a,b,c) = (a+b+c)! / (a!b!c!)
// Putting k "balls" in n "holes": (n+k-1)!/(k!(n-1)!)
//
// Number of ways of picking a 0s, b 1s and c As, a+b+c = m -> C(a,b,c)
// 1 or A as first digit: consider the (n-1) next digits, b or c can be 0.
// (interchangeable, so consider, say, 1, and multiply result by 2).
// (n-1-m) digits left, neither 0,1 or A => 13^(n-1-m) possible choices.
// Number of ways of putting m digits in n-1-m+1=n-m "holes":
// 1.X.X.X.X.
// ==> (n-m+m-1)!(m!(n-m-1)) = (n-1)!/m!(n-m-1)! (3 <= m <= n-1)
//
// All together:
// 2 * sum(n=3..16) sum(m=3..n-1) sum(a+b+c=m, a >= 0, b,c >= 1)
//     C(a,b,c)*13^(n-1-m)*(n-1)!/(m!(n-m-1)!)
//  == 13^(n-1-m)*(n-1)!/(a!b!c!(n-m-1)!)

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
        // Starts with 1 or A, number of 0s, 1s and As all >= 1:
        if (((1==d)||(10==d))&&(n_0 >= 1)&&(n_1 >= 1)&&(n_A >= 1)) {
            cout << uppercase << hex << i << endl;
            ++count;
        }
    }
    return count;
}

int main(int argc, char* argv[])
{
    int n_max = 16;
    if (argc > 1) n_max = atoi(argv[1]);
    // Calculate and store factorials up from 0! to n!
    unsigned long long * fact = new unsigned long long[n_max+1];
    fact[0] = 1;
    for(int i = 1; i <= n_max; ++i) {
        fact[i] = i*fact[i-1];
        //cout << i << "! = " << fact[i] << endl;
    }

    unsigned long long count = 0ULL;
    for(int n = 3; n <= n_max; ++n) {
        for(int m = 2; m <= n-1; ++m) {
            unsigned long long sum_m = 0;
            for(int a = 0; a <= m-2; ++a) {
                for(int b = 1; b <= m-a-1; ++b) {
                    int c = m-a-b;
                    unsigned long long c_abc = 
                        fact[n-1] / (fact[a]*fact[b]*fact[c]);
                    sum_m += c_abc;
                }
            }
            sum_m /= fact[n-m-1];
            for(int i = 0; i < n-m-1; ++i) sum_m *= 13;
            count += sum_m;
        }
    }
    count *= 2;

    if (n_max <= 6) {
        cout << "Brute force: " << dec << brute_force(1<<(4*n_max)) << endl;
    }
    cout << "Decimal answer: " << count << endl;
    cout << "Answer: " << uppercase << hex << count << endl;
    delete[] fact;
    return 0;
}
