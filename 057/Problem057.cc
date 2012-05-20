#include <iostream>
#include <cstdlib>
#include <vector>
using namespace std;

/*
 * Project Euler: Problem 057 (http://projecteuler.net/problem=57)
 */

// Sqrt(2) = 1 + 1 / ( 2 + 1 / ( 2 + 1 / ( 2 .... = 1.414213...
// (Infinite continuous fraction)
// 1 + 1/2 = 1.5 = 3/2
// 1 + 1/(2 + 1/2) = 7/5
// 1 + 1/(2 + 1/( 2 + 1/2 )) = 17/12
// 1 + 1/(2 + 1/( 2 + 1/( 2 + 1/2 ))) = 41/29
// ...
// next: 99/70, 239/169, 577/408, then 1393/985 first example where
// number of digits in numerator > number of digits in denominator.
//
// In the first one-thousand expansions, how many fractions contain a
// numerator with more digits than denominator?

// Recursion:
// F(1) = 1 + 1/2 = N(1)/D(1)
// F(n+1) = 1 + 1/( 1 + F(n) ) = 1 + D(n) / (N(n)+D(n))
//        = (N(n) + 2.D(n)) / (N(n)+D(n)
//
// So  D(n+1) = D(n) + N(n)
// So  N(n+1) = N(n) + 2.D(n) = D(n+1) + D(n)
// So  D(n+1) = 2.D(n) + D(n-1) (Fibonacci-like!) D(0)=1, D(1)=2
// 
// F(n+1) = (D(n+1) + D(n)) / (D(n+1))
//
// (limit F = 1 + 1/(1+F) <=> (F-1)(F+1)=1 <=> F^2=2 <=> F=+-sqrt(2)

typedef vector<char> BigInt;

void add( BigInt& a, BigInt& b, BigInt& s )
{
    s.clear();
    
    for(int i = 0; (i < (int) a.size()) || (i < (int) b.size()); ++i) {
         s.push_back(0);
    }
    s.push_back( 0 );
   
    for( int i = 0; ( i < (int) a.size()) || ( i < (int) b.size() ); ++i )
    {
        char da = ( i < (int) a.size() ? a[i] : 0 );
        char db = ( i < (int) b.size() ? b[i] : 0 );
        s[i] += da + db;
        if ( s[ i ] >= 10 )
        {
            s[ i ] -= 10;
            ++s[ i+1 ];
        }
    }
    if ( 0 == s[ (int)s.size()-1 ] ) s.erase( (++s.rbegin()).base() );
}

void dump( BigInt& n )
{
    for( int i = (int) n.size()-1; i >= 0; --i ) cout << (int) n[i];
}

int main( int argc, char** argv )
{
    int limit = 1000;
    if ( argc > 1 ) limit = atoi( argv[ 1 ] );
    int count = 0;
    BigInt d0; d0.push_back( 1 );
    BigInt d1; d1.push_back( 2 );
    BigInt d;
    BigInt n;
    BigInt* p0 = &d0;
    BigInt* p1 = &d1;
    BigInt* tp = 0;

    for( int i = 1; i <= limit; ++i )
    {
        add( (*p0), (*p1), n );
        //cout << "Expansion(" << i << ") = ";
        //dump(n);
        //cout << " / ";
        //dump(*p1);
        if ( n.size() > p1->size() )
        {
            ++count;
            //cout << " (Counted!)";
        }
        //cout << endl;
        add( (*p0), (*p1), d );
        add( (*p1), d, (*p0) );
        tp = p0; p0 = p1; p1 = tp;  // swap 
    }
    cout << endl << "Answer: " << count << endl;
    return 0;
}
