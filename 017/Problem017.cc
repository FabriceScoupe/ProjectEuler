#include <iostream>
#include <cstdlib>
#include <vector>
#include <string.h>
using namespace std;

/*
 * Project Euler: Problem 017 (http://projecteuler.net/problem=17)
 */

// How many letters used to write all numbers from 1 to 1000 ?

const char* word( int d )
{
    const char* msg = NULL;
    switch( d )
    {
        case 1: msg = "one"; break;
        case 2: msg = "two"; break;
        case 3: msg = "three"; break;
        case 4: msg = "four"; break;
        case 5: msg = "five"; break;
        case 6: msg = "six"; break;
        case 7: msg = "seven"; break;
        case 8: msg = "eight"; break;
        case 9: msg = "nine"; break;
        case 10: msg = "ten"; break;
        case 11: msg = "eleven"; break;
        case 12: msg = "twelve"; break;
        case 13: msg = "thirteen"; break;
        case 14: msg = "fourteen"; break;
        case 15: msg = "fifteen"; break;
        case 16: msg = "sixteen"; break;
        case 17: msg = "seventeen"; break;
        case 18: msg = "eighteen"; break;
        case 19: msg = "nineteen"; break;
        case 20: msg = "twenty"; break;
        case 30: msg = "thirty"; break;
        case 40: msg = "forty"; break;
        case 50: msg = "fifty"; break;
        case 60: msg = "sixty"; break;
        case 70: msg = "seventy"; break;
        case 80: msg = "eighty"; break;
        case 90: msg = "ninety"; break;
        case 100: msg = "hundred"; break;
        case 1000: msg = "thousand"; break;
        default: msg = "?"; break;
    }
    return msg;
}

void writeNumber( int n, vector<const char*>& words )
{
    if ( n > 1000 )
    {
        words.push_back( "TOO BIG!" );
    }
    else if ( n == 1000 )
    {
        words.push_back( word(1) );
        words.push_back( word(1000) );
    }
    else
    {
        int h = n / 100;
        if ( h > 0 )
        {
            words.push_back( word( h ) );
            words.push_back( word( 100 ) );
            n -= 100*h;
            if ( n > 0 )
            {
                words.push_back( "and" );
            }
        }
        h = n / 10;
        if ( h > 1 )
        {
            words.push_back( word( h*10 ) );
            n -= 10*h;
            if ( n > 0 ) words.push_back( word( n ) );
        }
        else if ( n > 0 )
        {
            words.push_back( word( n ) );
        }
    }
}

int main( int argc, char** argv )
{
    int n = 1000;
    if ( argc > 1 ) n = atoi( argv[1] );
    int sum = 0;
    for( int i = 1; i <= n; ++i )
    {
        vector< const char* > words;
        writeNumber( i, words );
        int len = 0;
        for( vector< const char* >::iterator it = words.begin();
             it != words.end(); ++it )
        {
            //cout << *it << " ";
            len += strlen( *it );
        }
        //cout << "(" << len << " letters)" << endl;
        sum += len;
    }
    cout << "Total letters: " << endl;
    cout << "Answer: " << sum << endl;
    return 0;
}
