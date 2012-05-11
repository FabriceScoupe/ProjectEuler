#include <iostream>
#include <cstdlib>
#include <vector>
#include <set>

// The smallest number expressible as the sum of a prime square, prime cube,
// and prime fourth power is 28. In fact, there are exactly four numbers below
// fifty that can be expressed in such a way:
// 28 = 2^2 + 2^3 + 2^4
// 33 = 3^2 + 2^3 + 2^4
// 49 = 5^2 + 2^3 + 2^4
// 47 = 2^2 + 3^3 + 2^4
// How many numbers below fifty million can be expressed as the sum of a prime
// square, prime cube and prime fourth power?

// A brute force solution...:
using namespace std;

void buildPrimes( vector<int>& primes, int limit )
{
    cout << "Building primes..." << endl;
    primes.push_back( 2 );
    for( int n = 3; n*n < limit; n += 2 )
    {
        bool is_prime = true;
        for( int p = 0; is_prime && ( p < primes.size() ); ++p )
        {
            is_prime = ( n % primes[ p ] != 0 );
        }
        if ( is_prime )
        {
            primes.push_back( n );
            cout << n << endl;
        }
    }
    cout << primes.size() << " primes found." << endl;
}

int main( int argc, char** argv )
{
    int limit = 50000000;
    if ( argc > 1 ) limit = atoi( argv[ 1 ] );

    set< int > solutions;
    vector< int > primes;
    buildPrimes( primes, limit );

    int n4 = 0;
    int n3 = 0;
    int n = 0;
    int p = 0;
    for( int p4 = 0; p4 < primes.size(); ++p4 )
    {
        p = primes[ p4 ];
        n4 = p * p * p * p;
        if ( n4 >= limit ) break;
        for( int p3 = 0; p3 < primes.size(); ++p3 )
        {
            p  = primes[ p3 ];
            n3 = p * p * p;
            if ( n4 + n3 >= limit ) break;
            for( int p2 = 0; p2 < primes.size(); ++p2 )
            {
                p = primes[ p2 ];
                n = n4 + n3 + p * p;
                if ( n >= limit ) break;
                solutions.insert( n );
                cout << '.';
            }
        }
    }
    cout << endl << solutions.size() << " numbers < " << limit << endl;
}
