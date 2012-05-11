#include <iostream>
#include <cstdlib>
#include <set>

using namespace std;

/***
A Hamming number is a positive number which has no prime factor larger than 5.
So the first few Hamming numbers are 1, 2, 3, 4, 5, 6, 8, 9, 10, 12, 15.
There are 1105 Hamming numbers not exceeding 10^(8).

We will call a positive number a generalised Hamming number of type n,
 if it has no prime factor larger than n.
Hence the Hamming numbers are the generalised Hamming numbers of type 5.

How many generalised Hamming numbers of type 100 are there which don't exceed
10^(9)?
***/

static int primes[] = {
    2, 3, 5, 7, 11, 13, 17, 19, 23, 29,
    31, 37, 41, 43, 47, 53, 59, 61, 67, 71,
    73, 79, 83, 89, 97, 0
};

int main( int argc, char** argv )
{
    int n = 100;
    if ( argc > 1 ) n = atoi( argv[ 1 ] );
    long long limit = 1000000000LL;
    if ( argc > 2 ) limit = atoll( argv[ 2 ] );

    set< long long > hamming;
    set< long long > h2;
    hamming.insert( 1 );
    for( int* p = primes; (*p > 0 )&&( *p <= n ); ++p )
    {
        h2.clear();
        for( set<long long>::iterator it = hamming.begin();
             it!=hamming.end(); ++it )
        {
            long long l = *it;
            while( l * (*p) <= limit )
            {
                l *= (*p);
                h2.insert( l );
            }
        }
        for( set<long long >::iterator it = h2.begin(); it != h2.end(); ++it )
        {
            hamming.insert( *it );
        }
    }
    cout << hamming.size() << " generalised Hamming number of type " << n
         << " which don't exceed " << limit << endl;
}
