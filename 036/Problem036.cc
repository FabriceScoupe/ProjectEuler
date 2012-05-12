#include <iostream>
#include <cstdlib>
#include <vector>
using namespace std;

// Find the sum of all numbers, less than one million,
// which are palindromic in base 10 and base 2 (eg 585)

bool isPalindrome( int n, int base )
{
    int a = n;
    int b = 0;
    while( a > 0 )
    {
        b *= base;
        b += a % base;
        a /= base;
    }
    return ( n == b );
}


int main( int argc, char** argv )
{
    int n = 1000000;
    if ( argc > 1 ) n = atoi( argv[1] );
    long long sum = 0;
    for( int i = 1; i < n; ++i )
    {
        if ( isPalindrome( i, 2 ) && isPalindrome( i, 10 ) )
        {
            //cout << i << " is a base2- and base10- palindrome" << endl;
            sum += i;
        }
    }
    cout << endl << "sum = " << sum << endl;
}
