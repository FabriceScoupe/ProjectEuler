#include <iostream>
#include <cstdlib>
#include <vector>
#include <set>
#include <stack>
using namespace std;

/*
 * Project Euler: Problem 103 (http://projecteuler.net/problem=103)
 */

// A = {a(1), ...., a(n)} with a(1) < a(2) < .... < a(n)
// For any B and C non-empty disjoint parts of A: S sum of elements of set
// 1/ S(B) != S(C)
// 2/ card(B) > card(C) => S(B) > S(C)
//
// 2/ => For k in [1..n-1], max S(K / card K = k) < min S(K' / card K' = k+1)
// max(S(K / card K = k) = sum[n-k+1 <= i <= n] a(i)
// min(S(K / card K = k) = sum[1 <= i <= k] a(i)
// So:
// a(1) + a(2) > a(n)
// a(1) + a(2) + a(3) > a(n-1) + a(n)
// ...
// a(1) + sum[2 <= i <= k] a(i) > sum[2 <= i <= k] a(n-i+2)
// with 2 <= k, 2*k < n
//
// 0 - Start with A = {1, ..., n}
// 1 - Check min/max inequalities 
// 2 - If any fails, add 1 to all elements, and loop back to 2
// 3 - Calculate sum of elements of all subsets of A, look for equal sums
//
// Evolution of Set A is "addition" at position [1..n], where adding one
// at position k actually means adding one at positions [k..n].
// A Set may have several transitions, ie possible next additions (when equal
// sums are detected, to "break" them).
// => use set<Set> to avoid reprocessing the same states, and
// stack<Set> to go down the tree. Keep "best" leaf as solution. 

// Convenient Type Aliases:
typedef unsigned char uchar;
typedef unsigned int  uint;
typedef vector<uint>  Set;
typedef set<Set>      SetStore;
typedef stack<Set>    SetStack;

static inline Set& add(Set& A, uchar pos)
{
    for(uchar i = pos; i < A.size(); ++i) ++A[i];
    return A;
}

void dump(const Set& A, bool separated = false)
{
    cout << (separated ? "A = { " : "");
    for(uint i = 0; i < A.size(); ++i) cout << A[i] << (separated ? " " : "");
    cout << (separated ? "}" : "") << endl;
}

static inline uint sum(const Set& A, uint p = 0)
{
    if (0 == p) p = (1 << A.size())-1;
    uint s = 0;
    uint q = p;
    for(uchar j = 0; j < A.size(); ++j, q >>= 1) if (q & 1) s += A[j];
    return s;
}

bool check_min_max(const Set& A)
{
    uint min_sum = A[0];
    uint max_sum = 0;

    for(uchar k = 1; 2*k < A.size(); ++k) {
        min_sum += A[k];
        max_sum += A[A.size()-k];
        if (min_sum <= max_sum) return false;
    }
    return true;
}

uint check_unequal_sums(const Set& A)
{
    uint p2n = 1 << A.size();
    uint max_sum = sum(A);
    Set sums2parts(max_sum+1);
    for(uint s = 0; s <= max_sum; ++s) sums2parts[s] = p2n;

    // For all subsets of A (illustrated by numbers from 1 to 2^n-1):
    for(uint p = 1; p < p2n; ++p) {
        uint  s = sum(A, p);
        uint& parts = sums2parts[s];
        
        if (parts < p2n) { // Equal sums detected!!!
            uint merged = (parts | p);
            uint lowest_bit = 0;
            while(((1<<lowest_bit) & merged) == 0) ++lowest_bit;
            merged &= ~ (1<<lowest_bit);
            return merged;
        }
        parts = p;
    }
    return 0;
}

uint find_optimum_special_sum_set(Set& A)
{
    SetStore store;
    SetStack tree;
    Set      best_A; // initially empty.

    tree.push(A); // The "trunk"

    while (!tree.empty()) {
        A = tree.top(); tree.pop();
        while(!check_min_max(A)) add(A, 0);
        uint p = check_unequal_sums(A);
        if (p > 0) { // Potential branches!
            for(uchar j = 0; j <= A.size(); ++j, p >>= 1) {
                if (p & 1) {
                    Set B = A;
                    add(B, j);
                    // Have we already looked at it? Is it good enough?
                    if ((store.find(B) == store.end()) &&
                        ((0 == best_A.size()) || (sum(B) < sum(best_A)))) {
                        store.insert(B);
                        tree.push(B);
                    }
                }
            }
        } else {
            // A is a special sum set, is it the best? If not, discard.
            if ((0 == best_A.size()) || (sum(A) < sum(best_A))) best_A = A;
        }
    }
    A = best_A;
    return sum(A);
}

int main(int argc, char* argv[])
{
    uchar n = 7;
    if (argc > 1) n = (uchar) atoi(argv[1]);
    Set A(n);
    for(uchar i = 0; i < n; ++i) A[i] = i+1;
    uint best_sum = find_optimum_special_sum_set(A);
    cout << "Best sum = " << best_sum << endl;
    cout << "Answer: ";
    dump(A);
    return 0;
}
