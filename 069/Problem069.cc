#include <iostream>
#include <cstdlib>
using namespace std;

// Euler's Totient function phi(n) is used to determine the number of
// numbers less than n which are relatively prime to n.
// For instance 1,2,4,5,7 and 8 are all less than 9 and relatively prime to it,
// so phi(9)=6.
// phi(2)=1 ; 2/phi(2) = 2
// phi(3)=2 ; 3/phi(3) = 1.5
// phi(4)=2 ; 4/phi(4) = 2
// phi(5)=4 ; 5/phi(5) = 1.25
// phi(6)=2 ; 6/phi(6) = 3
// phi(7)=6 ; 7/phi(7) = 1.16666...
// phi(8)=4 ; 8/phi(8) = 2
// phi(9)=6 ; 9/phi(9) = 1.5
// phi(10)=4; 10/phi(10) = 2.5
//
// It can be seen than n=6 produces a maximum n/phi(n) for n <=10
//
// Find the value of n <= 1000000 for which n/phi(n) is a maximum.
// For a prime p, phi(p) = p-1, 1 < p/p-1 <= 2 so skip primes
//
// n decomposition in primes = Prod(k=1..m) Pk^Mk (prime, multiplicity)
// So, the most (different) primes in the decomp, the smaller phi is.
// => n = 2*3*5*7* ... keeping n under the limit (1000000 here)
// 

int main( int argc, char** argv )
{
    int limit = 1000000;
    if ( argc > 1 ) limit = atoi( argv[ 1 ] );

    int n = 1;
    int primes[] = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 0 }; // more than enough
    int i = 0;
    while( ( n <= limit ) && ( primes[i] > 0 ) ) n *= primes[i++];
    if ( primes[i] == 0 )
    {
        cerr << "I need more primes!!!" << endl;
        exit(1);
    }
    else
    {
        n /= primes[i-1];
    }
    cout << "Largest n / phi(n) for n <= " << limit << " is " << n << endl;
}
