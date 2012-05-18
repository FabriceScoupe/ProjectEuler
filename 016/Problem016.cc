#include <iostream>
#include <cstdlib>
#include <string.h>
using namespace std;

/*
 * Project Euler: Problem 016 (http://projecteuler.net/problem=16)
 */

// Sum of digits of 2^1000 (in base 10)
// Logs: log10(2^1000)=1000.log10(2) (log10(2)= 0.30102999566...)
// Numbers of digits of X = ceiling( log10( X ) )
// => Numbers of digits of 2^1000 = 302
// First digit of  X=2^1000 : get log10( X / 10^301 )
// = log10( X ) - 301 = 1000.log10(2) - 301

void multiplyBy2( char* number, int length )
{
    int pos = 0;
    char carry = 0;
    while( pos < length ) {
        char tmp = 2 * number[pos] + carry;
        if ( tmp >= 10 ) {
            carry = 1;
            tmp -= 10;
        } else {
            carry = 0;
        }
        number[pos] = tmp;
        ++pos;
    }
    number[pos] = carry;
}

int main( int argc, char** argv )
{
    int n = 1000;
    if ( argc > 1 ) n = atoi( argv[ 1 ] );
    // Number of digits of 2^n : use n / 3 + 10 for safety
    int length = n / 3 + 10;
    char* pow2 = new char[ length ];
    memset( pow2, 0, length );
    pow2[0]=1;
    for( int i = 1; i <= n; ++i ) {
        //cout << "2^" << i << "=\t";
        multiplyBy2( pow2, length );
        int pos = length - 1;
        while( pow2[ pos ] == 0 ) --pos;
        while( pos >= 0 ) {
            //cout << (int) pow2[ pos ];
            --pos;
        }
        //cout << endl;
    }
    cout << "Sum of digits of 2^" << n << ":" << endl;
    int sum = 0;
    for( int i = 0; i < length; ++i ) sum += pow2[i];
    cout << "Answer: " << sum << endl;
    return 0;
}
