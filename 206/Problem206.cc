#include <iostream>
#include <string.h>

using namespace std;

/***
Find the unique positive integer whose square has the form
1_2_3_4_5_6_7_8_9_0,
where each “_” is a single digit.
***/

// 19 digits => 9 digit number, ends with 0 => 8 unknown digits.
// => Square ends with 2 zeroes: ...900
// => 10-digit number ending with ...30 or ...70
// => look for 9-digit number starting with 1, ending with 3 or 7

// Brute force!

// Returns number of matching digits
inline int match( long long n )
{
    long long sq = n*n;
    char buf[17];
    memset( buf, 0, 17 );
    char i = 0;
    while(sq > 0) {
        buf[(int) i++] = sq % 10;
        sq /= 10;
    }
    int sum = 0;
    for( i = 0; ( i <= 16 )&&( buf[(int)i]==9-(i/2) ); i += 2 ) ++sum;
    if ( sum >= 8 ) {
        cout << "n = " << n << " n^2 = " << n*n << endl;
    }
    return sum;
}

int main( int argc, char** argv )
{
    long long n = 100000003;
    long long inc = 4;
    int m = match( n );
    while( m < 9 ) {
        n += inc;
        inc = ( inc == 4 ? 6 : 4 );
        m = match( n );
    }
    n *= 10; 
    cout << endl << "n = " << n << " (" << n*n << ")" << endl;
}
