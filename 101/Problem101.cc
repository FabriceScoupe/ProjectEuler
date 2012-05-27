#include <iostream>
#include <vector>

using namespace std;

/*
 * Project Euler: Problem 101 (http://projecteuler.net/problem=101)
 */

/**
If we are presented with the first k terms of a sequence it is impossible
to say with certainty the value of the next term, as there are infinitely
many polynomial functions that can model the sequence.

As an example, let us consider the sequence of cube numbers.
This is defined by the generating function,
u_(n) = n^(3): 1, 8, 27, 64, 125, 216, ...

Suppose we were only given the first two terms of this sequence.
Working on the principle that "simple is best" we should assume a linear
relationship and predict the next term to be 15 (common difference 7).
Even if we were presented with the first three terms, by the same principle
of simplicity, a quadratic relationship should be assumed.

We shall define OP(k, n) to be the n^(th) term of the optimum polynomial
generating function for the first k terms of a sequence. It should be clear
that OP(k, n) will accurately generate the terms of the sequence for n ≤ k,
and potentially the first incorrect term (FIT) will be OP(k, k+1);
in which case we shall call it a bad OP (BOP).

As a basis, if we were only given the first term of sequence,
it would be most sensible to assume constancy;
that is, for n ≥ 2, OP(1, n) = u_(1).

Hence we obtain the following OPs for the cubic sequence:
OP(1, n) = 1               1, 1, 1, 1, ...
OP(2, n) = 7n−6            1, 8, 15, ...
OP(3, n) = 6n^(2)−11n+6    1, 8, 27, 58, ...
OP(4, n) = n^(3)           1, 8, 27, 64, 125, ...

Clearly no BOPs exist for k ≥ 4.

By considering the sum of FITs generated by the BOPs (indicated in red above),
we obtain 1 + 15 + 58 = 74.

Consider the following tenth degree polynomial generating function:

u_(n) = 1 − n + n^(2) − n^(3) + n^(4) − n^(5) + n^(6) − n^(7) + n^(8) − n^(9)
        + n^(10)

Find the sum of FITs for the BOPs.
***/

// Interpolation poly: for i in [1..k], P(i) = U(i)
// P(x) = Sum[i in 1..k] U(i) * Prod[j in 1..k, j != i] (x - j)/(i - j)
// P(k+s) = Sum[i in 1..k] U(i) * Prod[j in 1..k, j != i] (k+s-j)/(i-j)
// Prod[j in 1..k, j != i] (k+s-j) =
// Prod[j in 1..k, j != i] (i-j) = (k-i)! * (i-1)! * (-1)^(k-i)

// Returns:

long coef(int k, int s, int i)
{
     int sign = ((k-i) % 2 == 0 ? 1 : -1);
     long fact_kmi = 1;
     for(int j = 1; j <= k-i; ++j) fact_kmi *= j;
     long fact_im1 = 1;
     for(int j = 1; j <= i-1; ++j) fact_im1 *= j;
     long top = 1;
     for(int j = 1; j <= k; ++j) if (j != i) top *= k+s-j;
     top /= fact_im1;
     top /= fact_kmi;
     return sign*top;
}

long pkps(int k, int s, long (*func)(int))
{
    long sum = 0;
    for(int i = 1; i <= k; ++i) sum += func(i)*coef(k,s,i);
    return sum;
}

long fit(int k, long (*func)(int))
{
    int s = 0;
    long fit;
    do {
        ++s;
        fit = pkps(k,s,func);
    } while(fit == func(k+s));
    return fit;
}

// Evaluate polynomial at point x
long eval(vector<long>& poly, long x)
{
    long res = 0;
    for(int i = poly.size()-1; i >= 0; --i) {
        res *= x;
        res += poly[i];
    }
    return res;
}

static vector<long> u_poly;

long u(int n) { return eval(u_poly, n); }

int main(int argc, char** argv)
{
    cout << "For u(n) = n^3:" << endl;
    for(int i=0; i < 3; ++i) u_poly.push_back(0);
    u_poly.push_back(1); // n^3
    long sum_fit = 0;
    for(int k=1; k <= 3; ++k) {
        long f = fit(k,u);
        sum_fit += f;
        cout << "u("<<k<<") = "<< u(k) << " FIT = " << f << endl;
    }
    cout << "Sum of FITs = " << sum_fit << endl << endl;

    cout << "For u(n) = (n^11+1)/(n+1):" << endl;
    u_poly.clear();
    sum_fit = 0;
    for(int i=0; i < 11; ++i) u_poly.push_back(i % 2 == 0 ? 1 : -1);
    for(int k=1; k <= 10; ++k) {
        long f = fit(k,u);
        sum_fit += f;
        cout << "u("<<k<<") = "<< u(k) << " FIT = " << f << endl;
    }
    cout << "Sum of FITs = " << endl;
    cout << "Answer: " << sum_fit << endl << endl;
    return 0;
}
