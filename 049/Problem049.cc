#include <iostream>
#include <set>
#include <map>
using namespace std;

// Find arithmetic sequences, made of prime terms, whose four digits are
// permutations of each other.

// Ex: 1487, 4817, 8147 is one such sequence (increment 3330)
// Return 12-digit number obtained by concatenating the three terms in the
// other sequence.

// Increment is a multiple of 9 (property of perms in base 10):
// abcd = 1000a + 100b + 10c + d
// abdc = 1000a + 100b + 10d + c so abdc - abcd = 9(d-c)
// adcb-abcd = 100d - d - 100b + b = 99( d - b )
// Must be an even multiple of 9 (primes are odd).
// First 4-digit prime is 1009. Last 4-digit prime is 9973 (diff=8964)
// diff/2=4482=9*498.

void calculatePrimes( set<int>& ps )
{
    //cout << "Calculating all 4-digit primes" << n << "..." << endl;
    for( int i = 1001; i < 10000; i += 2 )
    {
        bool isPrime = true;
        for( int d = 3; (isPrime)&&(d*d <= i); d += 2 )
        {
            isPrime = ( i % d != 0 );
        }
        if (isPrime)
        {
            cout << i << " is prime." << endl;
            ps.insert(i);
        }
    }
    //cout << ps.size() << " primes found." << endl;
}

bool sameDigits( int p1, int p2 )
{
    map<int,int> m1,m2;
    for( int i = 1; i <= 4; ++i )
    {
        ++m1[ p1 % 10 ]; ++m2[ p2 % 10 ];
        p1 /= 10; p2 /= 10;
    }
    return( m1 == m2 );
}

int main( int argc, char** argv )
{
    set<int> primes;
    calculatePrimes( primes );
    for( int i = 18; i <= 4482; i += 18 )
    {
        for( set<int>::iterator it = primes.begin(); it != primes.end(); ++it )
        {
            int p1 = *it;
            int p2 = p1 + i;
            int p3 = p2 + i;
            if ( p3 > 9999 ) break;
            if ( ( primes.find( p2 ) != primes.end() ) &&
                 ( primes.find( p3 ) != primes.end() ) &&
                 ( sameDigits( p1, p2 ) ) &&
                 ( sameDigits( p2, p3 ) ) )
            {
                cout << p1 << ", " << p2 << ", " << p3
                     << " (" << i << ") : " << p1 << p2 << p3 << endl;
            }
        }
    }
}
