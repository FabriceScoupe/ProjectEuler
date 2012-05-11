#include <iostream>
#include <map>
using namespace std;

// Find the sum of all products whose multiplicand/multiplier/product identity
// can be written as 1 through 9 pandigital.

// Multiplication of x-digit number by y-digit number -> at most (x+y) digits
// and at least (x+y-1) digits:
// 10^(x-1) <= x-digit number < 10^x
// 10^(y-1) <= y-digit number < 10^y
// 10^(x+y-2) <= product < 10^(x+y)
// 10^(x+y-2) has x+y-1 digits, 10^(x+y)-1 has x+y digits.
//
// if multiplicand md has one digit, multiplier mr has 4 digits:
// 10^3 <= mr < 10^4, 1 < md < 10, so 10^3 < md*mr < 10^5
// if multiplicand md has two digits, multiplier mr has 3 digits:
// 10^2 <= mr < 10^3, 10 < md < 100 so 10^3 < md*mr < 10^5
//
// so pick 1 < md < 100, 1000 < p < 98765 => 1000 / md < mr < 98765 / md

int multiplicands[] = {
  2,  3,  4,  5,  6,  7,  8,  9,
 12, 13, 14, 15, 16, 17, 18, 19,
 21, 23, 24, 25, 26, 27, 28, 29,
 31, 32, 34, 35, 36, 37, 38, 39,
 41, 42, 43, 45, 46, 47, 48, 49,
 51, 52, 53, 54, 56, 57, 58, 59,
 61, 62, 63, 64, 65, 67, 68, 69,
 71, 72, 73, 74, 75, 76, 78, 79, 
 81, 82, 83, 84, 85, 86, 87, 89,
 91, 92, 93, 94, 95, 96, 97, 98, 0 };

bool digits( int n, map<char,char>& dm )
{
    int m = n;
    do
    {
        char d = m % 10;
        if ( ( 0 == d ) || ( dm[ d ] > 0 ) ) return false;
        dm[ d ] = 1;
        m -= ( m % 10 );
        m /= 10;
    }
    while( m > 0 );
    return true;
}

bool add_digits( map<char,char>& src, map<char,char>& tgt )
{
    for( char d = 1; d <= 9; ++d )
    {
        bool found_in_src = ( src.find(d) != src.end() );
        bool found_in_tgt = ( tgt.find(d) != tgt.end() );
        if ( src.find(d) != src.end() )
        {
            if( tgt.find(d) != tgt.end() ) return false;
            tgt[d]=1;
        }
    }
    return true;
}

int main( int argc, char** argv )
{
    map<int,int> sols;

    for( int* p = multiplicands; *p > 0; ++p )
    {
        map<char,char> m;
        digits( *p, m );
        for( int i = 1000 / *p; i <= ( 98764 / *p ) + 1; ++i )
        {
            map<char,char> m1;
            map<char,char> m2;
            if ( digits( i, m1 ) &&
                 add_digits( m, m1 ) &&
                 digits( *p * i, m2 ) &&
                 add_digits( m1, m2 ) &&
                 ( 9 == m2.size() ) )
            {
                cout << *p << " * " << i << " = " << *p * i << endl;
                ++sols[*p * i];
            }
        }
    }

    int sum = 0;
    for( map<int,int>::iterator i = sols.begin(); i != sols.end(); ++i )
    {
        sum += i->first;
    }

    cout << "Sum of products = " << sum << endl;
}
