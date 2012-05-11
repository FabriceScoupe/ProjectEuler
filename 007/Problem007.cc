#include <iostream>
#include <cstdlib>
#include <vector>
using namespace std;

typedef vector<int> Vint;
typedef Vint::iterator Iter;

static Vint primes;

int buildPrimes( int n )
{
    int np = 0;
    int p = 2;
    while( np < n )
    {
        bool prime = true;
        for( Iter i = primes.begin(); i != primes.end(); ++i )
        {
            prime = ( p % *i != 0 );
            if ( ! prime ) break;
        }
        if ( prime )
        {
            ++np;
            primes.push_back( p );
            //cout << "Prime #" << np << " = " << p << endl;
        }
        ++p;
    }
    return primes[primes.size()-1];
}

int main( int argc, char** argv )
{
    int n = 10001;
    if ( argc > 1 ) n = atoi( argv[1] );
    int nth_prime = buildPrimes( n );
    cout << "Prime # " << n << " = " << nth_prime << endl;
}
