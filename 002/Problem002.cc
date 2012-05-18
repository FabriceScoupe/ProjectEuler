#include <iostream>
#include <cstdlib>

/*
 * Project Euler: Problem 002 (http://projecteuler.net/problem=2)
 */
using namespace std;

int BruteForce( int n )
{
    int a = 0;
    int b = 1;

    int sum = 0;

    cout << "0";

    while( a + b < n ) {
        int c = a + b;
        if ( c % 2 == 0 ) {
            cout << " + " << c;
            sum += c;
        }
        a = b;
        b = c;
    }
    cout << endl;
    return sum;
}

int main( int argc, char** argv )
{
    int n = 4000000;
    if ( argc > 1 ) n = atoi( argv[1] );
    cout << "Sum of even Fibonacci elements < " << n  << ":" << endl;
    cout << "Answer: " << BruteForce(n) << endl;
    return 0;
}
