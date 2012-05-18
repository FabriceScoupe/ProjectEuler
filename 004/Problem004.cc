#include <iostream>
#include <cstdlib>
using namespace std;

/*
 * Project Euler: Problem 004 (http://projecteuler.net/problem=4)
 */

// 6-digit palindrome ABCCBA = 100001*A + 10010*B + 1100*C
// A in [1..9], B in [0..9], C in [0..9]
// 100001 = 11 * 9091 ; 10010 = 11 * 910 so:
// ABCCBA = 11 * ( 9091 * A + 910 * B + 100 * C )
//
bool decompose( int n, int&a, int&b, int&c )
{
    a = n / 9091;
    n %= 9091;
    b = n / 910;
    n %= 910;
    c = n / 100;
    n %= 100;
    return ( ( a >= 1 ) && ( a <= 9 ) &&
             ( b <= 9 ) && ( c <= 9 ) &&
             ( n == 0 ) );
}

int main( int argc, char** argv )
{
    int max = 0;
    int max_a = 0;
    int max_b = 0;

    for( int i = 10; i <= 90; ++i )
    for( int j = 100; j <= 999; ++j ) {
       int x, y, z;
       int p = i*j;
       if ( decompose( p, x, y, z ) ) {
           p *= 11;
           //cout << 11 * i << " x " << j << " = " << p;
           //cout << " = " << x << y << z << z << y << x << endl;
           if ( p > max ) {
               max = p;
               max_a = 11*i;
               max_b = j;
           }
       }
    }

    //cout << endl;
    cout << "Greatest = " << max << " = " << max_a << " * " << max_b << endl;
    cout << "Answer: " << max << endl;
    return 0;
}
