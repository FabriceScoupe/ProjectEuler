#include <iostream>
#include <cstdlib>

using namespace std;

/* 
 * Some positive integers n have the property that the sum
 * [n + reverse(n)] consists entirely of odd (decimal) digits.
 * For instance, 36+93=99 and 409+904=1313.
 * We call such numbers reversible; so 39, 63, 409 and 904 are reversible.
 * Leading zeroes are not allowed in either n or reverse(n).
 * There are 120 reversible numbers below one thousand.
 * How many reversible numbers are there below one-billion (10^9) ?
 */

// n = sum[k=0..m] d(k).10^k
// reverse(n) = sum[k=0..m]d(m-k).10^k
// n + reverse(n) = sum[k=0..m](d(k)+d(m-k)).10^k

int main( int argc, char** argv )
{
    unsigned int limit = 1000000000;
    if ( argc > 1 ) limit = atoi( argv[ 1 ] );
    unsigned int count = 0;
    unsigned char digits[9]; // 9-digit number max
    for(unsigned int n = 12; n < (limit/2)+1; n += 2) {
        if (n % 10 == 0) continue;
        unsigned int m = n;
        unsigned char nd = 0; // Number of digits processed
        while(m > 0) {
            digits[nd] = m % 10;
            m /= 10;
            ++nd;
        }
        bool carry = false;
        bool is_odd = true;
        for(int i = 0; (is_odd) && (i < nd); ++i) {
            char s = digits[i] + digits[nd-i-1] + (carry ? 1 : 0);
            carry = (s >= 10);
            is_odd = (s % 2);
        }
        if (is_odd) count += 2;
    }
    cout << "Number of reversible numbers below " << limit << "=" << count
         << endl;
    return 0;
}
