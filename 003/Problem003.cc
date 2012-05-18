#include <iostream>
#include <cstdlib>
using namespace std;

/*
 * Project Euler: Problem 003 (http://projecteuler.net/problem=3)
 */

int main( int argc, char** argv )
{
    long long n = 600851475143LL;
    if ( argc > 1 ) n = atol( argv[ 1 ] );

    long long p = 1;
    long long m = n;

    while( n > 1 ) {
        ++p;
        while( n % p == 0 ) {
            //cout << p << " ";
            n  /= p;
        }
    }
    //cout << endl;

    cout << "Largest prime in decomposition of " << m << ":" << endl;
    cout << "Answer: " << p << endl;
    return 0;
}
