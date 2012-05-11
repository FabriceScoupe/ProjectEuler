#include <iostream>
#include <cstdlib>
#include <set>
using namespace std;

// All square roots are periodic when written as continued fractions
// and can be written in the form:
// sqrt(N) = a0 + 1 / ( a1 + 1 / ( a2 + 1 / ( a3 + ... ) ) )
// e.g. sqrt(23) = 4, 1, 3, 1, 8, 1, 3, 1, 8, ... (ak)
// Notation: sqrt(23)=[4;(1,3,1,8)]
// Periods per sqrt of:
// 2 -> 1, 3 -> 2, 5 -> 1, 6 -> 2, 7 -> 4, 8 -> 2, 10 -> 1,
// 11 -> 2, 12 -> 2, 13 -> 5
//
// 4 continued fractions, for n < 13 have an odd period.
// How many continued fractions for N <= 10000 have an odd period?

// a0 integer part = largest integer such that a0*a0 < n (strictly)
// so a0 = n / a0 what about r0 = n % a0 ? ( 0 < r0 < a0 )
// r0 = n - a0^2 = (r - a0)(r + a0)
// let r be sqrt(n): a0 < r < a0+1 <=> 0 < r - a0 < 1
// 
// Using: method from en.wikipedia.org (Continued Fractions)
// m(0) = 0; d(0) = 1; a(0) = floor(sqrt(N))
// m(n+1) = d(n).a(n) - m(n)
// d(n+1) = (N - m(n+1)^2)/d(n)
// a(n+1) = floor( ( a0 + m(n+1) ) / d(n+1) )
// 

int floor_root( int n )
{
    int r = 1;
    while( r * r <= n ) ++r;
    return r-1;
}

struct Triplet
{
    Triplet() : m( 0 ),d( 0 ), a( 0 ) { };
    Triplet(int mm, int dd, int aa ) : m( mm ), d( dd ), a( aa ) { };
    Triplet( const Triplet& r ) : m(r.m), d(r.d), a(r.a) { }

    bool operator< ( const Triplet& r ) const
    {
        return( m != r.m ? m < r.m
                         : d != r.d ? d < r.d
                                    : a != r.a ? a < r.a
                                               : false );
    }

    Triplet& operator=( const Triplet& r )
    {
        m = r.m; d = r.d; a = r.a;
        return *this;
    }

    int m,d,a;
};

int main( int argc, char** argv )
{
    int n = 10000;
    if ( argc > 1 ) n = atoi( argv[ 1 ] );
    int count = 0;
    for( int i = 2; i <= n; ++i )
    {
        set<Triplet> ts;
        int a0 = floor_root( i );
        if ( a0*a0 == i ) continue;
        Triplet t( 0, 1, a0 );
        Triplet next_t;
        int p = 0;
        cout << "sqrt(" << i << "): ";
        while( ts.find( t ) == ts.end() )
        {
            //cout << "a(" << p << ")=" << t.a << " ";
            ts.insert( t );
            ++p;
            next_t.m = t.d*t.a - t.m;
            next_t.d = (i - next_t.m*next_t.m) / t.d;
            next_t.a = ( a0 + next_t.m ) / next_t.d;
            t = next_t;
        }
        --p;
        cout << " (period " << p << ")" << endl;
        if ( p % 2 != 0 ) ++count;
    }
    cout << endl << "odd-period continued fraction for sqrt(N<=" << n 
         << ") = " << count << endl;
}
