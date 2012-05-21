#include <iostream>

using namespace std;

/*
 * Project Euler: Problem 097 (http://projecteuler.net/problem=097)
 */

// The first known prime found to exceed one million digits was discovered in
// 1999, and is a Mersenne prime of the form 2^(6972593)−1; it contains exactly
// 2,098,960 digits. Subsequently other Mersenne primes, of the form 2^(p)−1,
// have been found which contain more digits.
// However, in 2004 there was found a massive non-Mersenne prime which contains
// 2,357,207 digits: 28433×2^(7830457)+1.
// Find the last ten digits of this prime number.

// Use % 10000000000LL !

int main( int argc, char** argv )
{
    long long num = 28433LL;

    for( int i = 0; i < 7830457; ++i )
    {
        num *= 2;
        num %= 10000000000LL;
    }
    ++num;

    cout << "Last 10 digits = " << endl;
    cout << "Answer: " << num << endl;
    return 0;
}
