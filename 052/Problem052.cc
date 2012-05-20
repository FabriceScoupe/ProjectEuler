#include <iostream>
#include <map>
using namespace std;

/*
 * Project Euler: Problem 052 (http://projecteuler.net/problem=52)
 */

// Find the smallest positive integer x such that 2x, 3x, 4x, 5x and 6x 
// all contain the same digits as x, in a different order.

// x = sum[k=0..n] Ak.10^k
// An must be 1 (6 times 2 > 9) x = sum[k=0..n-1] Ak.10^k + 10^n
// An-1 <= 6 ( 6 times 16 = 96 )
//
// x must be a multiple of 9 (because of digit permutations)
// => sum[k=0..n]Ak is also a multiple of 9.
//
// 167... x 6 adds a digits, so left-most digits at most 166...
// Right-most digit:
// 1->2,3,4,5,6 2->4,6,8,0,2 3->6,9,2,5,8 4->8,2,6,0,4 5->0,5,0,5,0
// 6->2,8,4,0,6 7->4,1,8,5,2 8->6,4,2,0,8 9->8,7,6,5,4 0->0,0,0,0,0
//
bool sameDigits( int a, int b )
{
    map<char,char> ma,mb;
    int ta = a;
    int tb = b;
    do
    {
        ++ma[ ta % 10 ];
        ++mb[ tb % 10 ];
        ta /= 10;
        tb /= 10;
    }
    while( ( ta > 0 ) && ( tb > 0 ) );
    return( ma == mb );
}

int main( int argc, char** argv )
{
   int  n     = 1008;
   int  upper = 1666; 
   int  roof  = 10000;
   int  found = 0;
   while( found <= 0 )
   {
       int    m = n;
       char mul = 2;
       for(;mul<=6;++mul)
       {
           m += n;
           if ( ( m >= roof ) || ( ! sameDigits( m, n ) ) ) break;
       }
       if ( mul > 6 ) found = n;
       n += 9;
       if ( n > upper )
       {
           cout << "Adding a digit..." << endl;
           upper *= 10;
           upper += 6;
           n = roof + 8;
           roof *= 10;
       }
   }
   cout << "Answer: " << found << endl;
   cout << " x2 =  " << found*2 << endl;
   cout << " x3 =  " << found*3 << endl;
   cout << " x4 =  " << found*4 << endl;
   cout << " x5 =  " << found*5 << endl;
   cout << " x6 =  " << found*6 << endl;
}
