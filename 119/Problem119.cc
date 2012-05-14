#include <iostream>
#include <cstdlib>
#include <set>

using namespace std;

/***
The number 512 is interesting because it is equal to the sum of its digits
raised to some power: 5 + 1 + 2 = 8, and 8^(3) = 512.
Another example of a number with this property is 614656 = 28^(4).

We shall define a_(n) to be the nth term of this sequence and insist that a
number must contain at least two digits to have a sum.

You are given that a_(2) = 512 and a_(10) = 614656.

Find a_(30).
***/


// Take number, elevate to power, check sum of digits, etc.

inline int sum_digits( long long n, int& nb_digits )
{
    long long m = n;
    int s = 0;
    nb_digits = 0;
    while( m > 0 ) {
        ++nb_digits;
        s += m % 10;
        m /= 10;
    }
    return s;
}

int main( int argc, char** argv )
{
    int n = 32; // Dirty hack to get a proper value
    if ( argc > 1 ) n = atoi( argv[ 1 ] );

    int i = 2;
    set< long long > a;
    int k = 0;

    while( k < n ) {
        int nd = 0;
        int sd = 0;
        long long p = 1;
        //cout << "Trying " << i << endl;
        int pwr = 0;
        do {
            p *= i;
            ++pwr;
            sd = sum_digits( p, nd );
            if ( ( nd >= 2 ) && ( sd == i ) ) {
                 ++k;
                 a.insert( p );
                 //cout << "Found " << p << " k= " << k << endl;
            }
        }
        // TODO!!! Improve this condition, it doesn't work correctly
        while( ( nd <= i ) && ( pwr < 20 ) );
        ++i;
    }

    k = 0;
    for( set< long long >::iterator it = a.begin(); it != a.end(); ++it )
    {
        ++k;
        if (30 == k) cout << "a(" << k << ")=" << *it << endl;
    }
    return 0;
}
