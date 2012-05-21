#include <iostream>
#include <fstream>

/*
 * Project Euler: Problem 089 (http://projecteuler.net/problem=89)
 */

// The rules for writing Roman numerals allow for many ways of writing each
// number (see FAQ: Roman Numerals). However, there is always a "best" way of
// writing a particular number.
// For example, the following represent all of the legitimate ways of writing
// the number sixteen:
// IIIIIIIIIIIIIIII
// VIIIIIIIIIII
// VVIIIIII
// XIIIIII
// VVVI
// XVI
// The last example being considered the most efficient, as it uses the least
// number of numerals.
// The 11K text file, roman.txt (right click and 'Save Link/Target As...'),
// contains one thousand numbers written in valid, but not necessarily minimal,
// Roman numerals; that is, they are arranged in descending units and obey the
// subtractive pair rule (see FAQ for the definitive rules for this problem).
// Find the number of characters saved by writing each of these in their
// minimal form.
// Note: You can assume that all the Roman numerals in the file contain no
// more than four consecutive identical units.

using namespace std;

inline int romchar2int( char rc )
{
    int v = 0;
    switch( rc )
    {
        case 'I': v = 1;  break;
        case 'V': v = 5;  break;
        case 'X': v = 10; break;
        case 'L': v = 50; break;
        case 'C': v = 100; break;
        case 'D': v = 500; break;
        case 'M': v = 1000; break;
        default: break;
    }
    return v;
}

// Number of characters in "normal" roman form for integer n
int num_romchars( int n )
{
    int count = n / 1000;
    int m = n % 1000;
    while( m > 0 )
    {
        switch( m % 10 )
        {
            case 3: ++count;
            case 2: ++count;
            case 1: ++count; break;
            case 4:
            case 9: count += 2; break;
            case 8: ++count;
            case 7: ++count;
            case 6: ++count;
            case 5: ++count; break;
            default: break;
        }
        m /= 10;
    }
    return count;   
}


// Returns the number of letters removed via "normalisation"
int parseRomans( char* filename )
{
    ifstream in( filename );
    int delta = 0;
    if ( in )
    {
        char c = 0;
        int res = 0;
        int p = 0;
        int d = 0;
        do
        {
            if ( ! in.get( c ) ) c = 0;
            int v = romchar2int( c );
            if ( v > 0 )
            {
                ++d;
                if ( 0 == res )
                {
                    res = v;
                }
                else
                {
                    res += ( v <= p ? v : v-2*p );
                }
                p = v;
            }
            else
            {
                delta += d - num_romchars( res );
                res = 0;
                d = 0;
            }
        }
        while( c != 0 );
    }
    return delta;
}

int main( int argc, char** argv )
{
    char* filename = (char*) "roman.txt";
    if ( argc > 1 ) filename = argv[ 1 ];

    cout << "Answer: " << parseRomans( filename ) << endl;
    return 0;
}
