#include <iostream>
#include <cstdlib>
#include <set>
#include <map>
using namespace std;

/*
 * Project Euler: Problem 106 (http://projecteuler.net/problem=106)
 */

// Non-equality of subsets S(B) != S(C) for B and C parts of A.
// A = { a1, a2, ...., an } strictly increasing elements.
//
// Use bits to represent indices, so n bits => 0 (empty) to (1<<n)-1 (2^n sets)
// Only checks disjoint sets: (p1 & ~p2) == p1
// Only checks sets with same bit count.
//
// Worst case: A = {a0+1, a0+2, ..., a0+n} with some a0
// Obeying B < C => S(B) < S(C): min Sk > max Sk+1 (k number of elements)
// a1 + sum[a(k), 1 <= k <= (n-1)/2] > sum[a(n-k+1), 1 <= k <= (n-1)/2]
//
// B and C have same number of elems: B = {b1, ..., bm}, C = {c1, ..., cm}
// All bi,cj distincts, ordered.
// 2 elements of B are always greater than 1 element of C (and vice-versa)
// For n=7, possibility of having this:
// b1 c1 c2 c3 b2 b3 => check: c1+c2+c3 > b2+b3, the diff might be > b1
// b1 c1 c2 b2 b3 c3 => check: c1+c2+c3 > b2+b3, same.
// b1 c1 c2 b2 c3 b3 => check: c1+c2+c3 > b2+b3.
// b1 c1 b2 c2 b3 c3 => don't check, the c's "win" ci > bi for i in (1..3)
// 
typedef unsigned int uint;

void dumpbits(uint p, uint n)
{
    for(uint i = n; i > 0; --i) cout << ((p & (1<<(i-1))) ? '1' : '0');
}
int main(int argc, char* argv[])
{
    uint n = 12;
    if (argc > 1) n = (uint) atoi(argv[1]);
    uint count = 0;
    uint disjoint_pairs = 0;
    for (uint p1 = 1; p1 < ((1<<n)-1); ++p1) {
        uint b1 = 0;
        for(uint q1 = p1; q1 > 0; q1 >>= 1) b1 += (q1 & 1); // bitcount of p1
        for (uint p2 = p1+1; p2 < (1<<n); ++p2) {
            if ((p1 & ~p2) != p1) continue; // Not disjoint, ignore
            ++disjoint_pairs;
            uint b2 = 0;
            for(uint q2 = p2; q2 > 0; q2 >>= 1) b2 += (q2 & 1);
            if ((b1 != b2) || (1 == b1)) continue; // Different bitcounts, or 1 
            // p2 > p1, so from highest bits, the first one is p2's
            uint ct1 = 0; // bits of p1 seen so far
            uint ct2 = 0; // bits of p2 seen so far
            uint sup2to1 = 0; // Number of times a bit of p2 is > one of p1
            for(uint q = 1<<(n-1); q > 0; q >>= 1) {
                if (p2 & q) {
                    if (ct1) {
                        --ct1;
                    } else {
                        ++ct2;
                    }
                }
                if (p1 & q) {
                    if (ct2) { // at least one p2 bit on the left
                        --ct2; // consume it and...
                        ++sup2to1; // ...add "victory"
                    } else {
                        ++ct1; // p1 will "win" the next one.
                    }
                }
            }
            // p2 "won" for each of its bits, don't check.
            if (sup2to1 == b2) continue;
            //dumpbits(p1, n); cout << " "; dumpbits(p2, n); cout << endl;
            ++count;
        }
    }
    cout << "Disjoint pairs: " << disjoint_pairs << ", check:" << endl;
    cout << "Answer: " << count << endl;
    return 0;
}
