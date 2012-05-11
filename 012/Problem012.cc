#include <iostream>
#include <cstdlib>
using namespace std;

// Finding triangle number T(n) = n * (n+1) / 2 with > 500 divisors
// d | a and d | b => d | ( a+b )
// d | a and d | b => d | ( a.b )
// T(n) product of 2 integers, one of which is always odd.
// The only number dividing two successive integers is 1:
// d | n and d | n+1 <=> d = 1
// for 2 numbers A and B with only 1 as common divisor:
// number of divisors( A x B ) = num.divs(A) x num.divs(B)
// Suppose n even: if only 1 common divisor of n and n+1,
// then a fortiori only 1 common divisor of n/2 and n+1
// so nd(n*(n+1)/2) = nd(n+1)*nd(n/2) = nd(T(n))

// Return ceiling of square root of n
int root( long long n )
{
    long long i = 1;
    while( i * i < n ) ++i;
    return i;
}

// For any n > 1
int numDivs( long long n, bool show=false )
{
    int nd = 2; // At least 1 and n as divisors
    long long d = n-1;
    int r = root(n);
    while( d >= r )
    {
        if ( n % d == 0 )
        {
            nd += 2; // Count d and n/d
            if ( show ) cout << d << " " << n/d << endl;
        }
        --d;
    }
    if ( r*r == n ) --nd; // For perfect squares, not a pair, just the one.
    return nd;
}

int main( int argc, char** argv )
{
    int n = 500;
    if ( argc > 1 ) n = atoi( argv[1] );

    int nd = 1;
    int prev_nd = 1;
    int i = 2;
    long long t = 0;
    while ( nd <= n )
    {
        t = (i-1)*i/2;
        int curr_nd = ( i % 2 == 0 ? numDivs( i / 2 ) : numDivs( i ) );
        nd = prev_nd * curr_nd;
        prev_nd = curr_nd;
        cout << t << ": " << nd << " divisors" << endl;
        ++i;
    }

    cout << endl <<  t << " has more than " << n << " divisor(s)." << endl;
    cout << "Check: " << endl << numDivs( t, false ) << endl;
}
