#include <iostream>
#include <cstdlib>
using namespace std;

// How many Lychrel numbers are there below 10000 ?
// Lychrel number: a number that never forms a palindrome through the
// reverse and add process.
// Counter-example:
// 349 + 943 = 1292
// 1292 + 2921 = 4213
// 4213 + 3124 = 7337
//
// Palindromic number that is not a Lychrel number: 4994
// Assume that number is Lychrel until proven otherwise
// + (i) either it becomes a palindrome in < 50 iterations
// or (ii) no one has so far managed to map it to a palindrome.
// (10677, for instance, over 50 iterations to palindrome).

long long reverse( long long n )
{
    long long a = n;
    long long b = 0;
    while( a > 0 )
    {
        b *= 10;
        b += a % 10;
        a /= 10;
    }
    return b;
}

int main( int argc, char** argv )
{
    int limit = 10000;
    if ( argc > 1 ) limit = atoi( argv[ 1 ] );
    int lychrels = 0;

    for( int i = 10; i < limit; ++i )
    {
        long long n = i;
        char iter = 0;
        do
        {
            n += reverse( n );
            ++iter;
        } while( ( iter <= 50 ) && ( n != reverse( n ) ) );

        if ( iter > 50 )
        {
            cout << i << " is a Lychrel number." << endl;
            ++lychrels;
        }
    }
    cout << endl << lychrels << " Lychrel numbers < " << limit << endl;
}
