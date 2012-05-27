#include <iostream>
#include <vector>

using namespace std;

/*
 * Project Euler: Problem 104 (http://projecteuler.net/problem=104)
 */

/***
The Fibonacci sequence is defined by the recurrence relation:

Fn = Fn1 + Fn2, where F1 = 1 and F2 = 1.
It turns out that F541, which contains 113 digits, is the first
Fibonacci
number for which the last nine digits are 1-9 pandigital
(contain all the digits 1 to 9, but not necessarily in order).
And F2749, which contains 575 digits, is the first Fibonacci number for
which
the first nine digits are 1-9 pandigital.

Given that Fk is the first Fibonacci number for which the first nine
digits
AND the last nine digits are 1-9 pandigital, find k.
***/

typedef vector<char> BigInt;

// c = a + b;
// Assume that b always bigger than a, and b.size() at most a.size()+1
void add( const BigInt& a, BigInt& b, BigInt& c )
{
   char carry = 0;
   c.clear();
   int  d  = 0;
   char dc = 0;
   for(; d < (int) a.size() ; ++d) {
       dc = a[d] + b[d] + carry;
       carry = ( dc >= 10 ? 1 : 0 );
       if (( b.size() > 25 ) && ( 8 == d )) carry = 0;
       c.push_back( dc % 10 );
   }
   dc = carry + ( d < (int)b.size() ? b[d] : 0 );
   if ( dc > 0 ) c.push_back( dc % 10 );
   if ( dc >= 10 ) c.push_back( 1 );
   // Resize if need be:
   if ( b.size() > 25 ) {
       b.erase( b.begin()+9 );
       c.erase( c.begin()+9 );
   }
}

void dump( const BigInt& b )
{
    for(unsigned int i = b.size()-1; i >= 0; i-- ) cout << (int)b[i];
    cout << endl;   
}

inline bool is_pandigital( const BigInt& b, bool first )
{
   if ( b.size() < 25 ) return false;
   unsigned int test = 0;
   for( int d = 1; d <= 9; ++d )
   {
       int i = ( first ? b.size()-d : d-1 );
       if (b[i]==0) return false;
       unsigned int f = 1<<(b[i]-1);
       if ( ( test & f ) > 0 ) return false;
       test |= f;
   }
   return true;
}

int main( int argc, char** argv )
{
   BigInt f1,f2,f3;
   BigInt* f1p = &f1;
   BigInt* f2p = &f2;
   BigInt* f3p = &f3;

   f1.push_back( 1 );
   f2.push_back( 1 );
   int k = 3;
   bool pan_first = false;
   bool pan_last  = false;
   while( !pan_first || !pan_last )
   {
       //if ( k % 100 == 0 ) cout << '.'; flush( cout );
       add( *f1p, *f2p, *f3p );
       pan_first = is_pandigital( *f3p, true );
       pan_last  = is_pandigital( *f3p, false );
       /*
       if ( pan_first || pan_last ) {
           cout << endl << "F(" << k << ") panfirst = " << pan_first
                             << "  panlast  = " << pan_last << endl;
       }
       */
       ++k;
       // Rotate pointers
       BigInt* tmp = f3p;
       f3p = f1p;
       f1p = f2p;
       f2p = tmp;
   }

   cout << "Answer: " << k-1 << endl;
   return 0;
}
