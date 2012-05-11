#include <iostream>

using namespace std;

/***
Working from left-to-right if no digit is exceeded by the digit to its left
it is called an increasing number; for example, 134468.

Similarly if no digit is exceeded by the digit to its right it is called a
decreasing number; for example, 66420.

We shall call a positive integer that is neither increasing nor decreasing a
"bouncy" number; for example, 155349.

Clearly there cannot be any bouncy numbers below one-hundred, but just over
half of the numbers below one-thousand (525) are bouncy. In fact, the least
number for which the proportion of bouncy numbers first reaches 50% is 538.

Surprisingly, bouncy numbers become more and more common and by the time we
reach 21780 the proportion of bouncy numbers is equal to 90%.

Find the least number for which the proportion of bouncy numbers is exactly
99%.
***/

// Not subtle
bool is_bouncy( long long n )
{
    if ( n < 100 ) return false;
    char last_d = n % 10;
    n /= 10;
    char last_dir = 0;
    bool monotonous = true;
    while( ( n > 0 ) && monotonous )
    {
        char d = n % 10;
        char dir = ( d > last_d ? 1 : d < last_d ? -1 : last_dir );
        if ( 0 == last_dir ) last_dir = dir;
        monotonous = ( last_dir == dir );
        last_dir = dir;
        last_d   = d;
        n /= 10;
    }
    return ( ! monotonous );
}


int main( int argc, char** argv )
{
    bool found   = false;
    long long n  = 1;
    long long b  = 0;
    long long p  = 0;
    long long tp = 50;

    while( ! found )
    {
        bool bouncy = is_bouncy( n );
        if ( bouncy ) ++b;
        p = b * 100 / n;
        if ( p >= tp )
        {
            cout << "n = " << n << "\t %bouncy=" << p << endl;
            tp += ( tp < 90 ? 10 : 1 );
        }
        found = ( p >= 99 );
        ++n;
    }
    return 0;
}
