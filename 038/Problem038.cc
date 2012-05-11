#include <iostream>
#include <map>
using namespace std;

// Largest 1 to 9 pandigital 9-digit number that can be formed as the 
// concatenated product of an integer with (1,2,...,n) / n>1 ?

// 9! permutations (362880)
// product p => number starts with p
// 1-digit p => p = 1 123456789 (n=9)
//              p = 2 24681012? 
//              p = 3 369121518 (n=6)
//              p = 4 48121615?
//              p = 5 510152025 (n=5)
//              p = 6 612182430 (n=5)
//              p = 7 714212835 (n=5)
//              p = 8 816243240 (n=5)
//            * p = 9 918273545 (n=5)
//
// So only look up to 5
// See also problem 32.
// Max p ? 9999 = 999918888 (9-digits, then 10000 => 10-digits)

bool digits( int n, map<char,char>& dm )
{
    dm.clear();
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
    int max = 0;
    for(int p = 1; p < 10000; ++p )
    {
        bool ok = true;
        int number = 0;
        map< char, char > m1;
        map< char, char > m2;
        for( int n = 1; ok && ( m2.size() < 9 ); ++n )
        {
            ok = ( digits( n*p, m1 ) && add_digits( m1, m2 ) );
            if ( ok )
            {
                for( int i = 0; i < m1.size(); ++i ) number *= 10;
                number += n*p;
            }
        }
        if ( ok )
        {
            cout << "Found: " << number << " (product " << p << ")" << endl;
            if ( number > max ) max = number;
        } 
    }
    cout << endl <<  "Max: " << max << endl;
}
