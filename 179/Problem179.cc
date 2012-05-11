#include <iostream>
#include <cstdlib>

using namespace std;

/***
Find the number of integers 1 < n < 10^(7),
for which n and n + 1 have the same number of positive divisors.
For example, 14 has the positive divisors 1, 2, 7, 14
while 15 has 1, 3, 5, 15.
***/

// Sieve!
// log2(10000000)~24, so at most 1+24 = 25 divisors
// Use 10000000 chars as sieve!

int main( int argc, char** argv )
{
    int limit = 10000000;
    if ( argc > 1 ) limit = atoi( argv[ 1 ] );
    int* sieve = new int[ limit ];
    for( int n = 2; n <= limit; ++n )
    {
        for( int m = n; m <= limit; m += n )
        {
            ++sieve[ m ];
        }
        if ( n % 100000 == 0 ) { cout << '.'; flush( cout ); }
    }
    cout << endl;
    int last_nd = -1;
    int count = 0;
    for( int n = 2; n <= limit; ++n )
    {
        if ( last_nd == sieve[ n ] )
        {
            //cout << n-1 << " & " << n << " = " << last_nd << endl;
            ++count;
        }
        last_nd = sieve[ n ];
    }
    delete[] sieve;
    cout << count << " n such as n and n+1 have same # divisors." << endl;
    return 0;
}
