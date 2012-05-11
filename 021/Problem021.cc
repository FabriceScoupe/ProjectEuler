#include <iostream>
#include <cstdlib>
#include <vector>
using namespace std;

// Sum of all amicable numbers under 10000
// Proper divisors of n = numbers < n which divide evenly into n
// d(n) = sum of proper divisors of n
// if a != b and d(a)=b and d(b)=a, (a,b) pair of amicable numbers
// if n odd, d(n) = 0
// if n even, proper divisors of n = divisors of n/2 (n even)

int root( int n )
{
    int r = 1;
    while( r*r < n ) ++r;
    return r;
}

int d( int n )
{
    if ( n % 2 != 0 ) return 0;
    int sum = 1;
    int r = root( n );
    int div = 2;
    while( div <= r )
    {
        if ( ( n % div == 0 ) &&
             ( ( div % 2 == 0 ) || ( ( n / div ) % 2 == 0 ) ) )
        {
            sum += div + n / div;
        }
        ++div;
    }
    if ( r*r == n ) sum -= r;
    return sum;
}

int main( int argc, char** argv )
{
    int n = 10000;
    if ( argc > 1 )  n = atoi( argv[1] );
    // Find amicable pairs
    cout << "Test: d(220)=" << d(220) << endl;
    vector<int> amicable;
    for( int i = 1; i < n/2; ++i )
    {
        int b = d(2*i);
        if ( ( b < n ) && ( b % 2 == 0 ) && ( d(b) == 2*i ) && ( b != 2*i ) )
        {
            amicable.push_back( b );
            cout << "Found pair (" << 2*i << ", " << b << ")" << endl;
        }
    }

    // Sum found amicable numbers (watch doubles!)
    int sum = 0;
    for( vector<int>::iterator it = amicable.begin();
         it != amicable.end(); ++it )
    {
        int peer = d(*it);
        if ( peer < n )
        {
            sum += (*it + peer )/2;
        }
        else
        {
           sum += *it;
        }
    }
    cout << "Sum of amicable numbers < " << n << " = " << sum << endl;
}
