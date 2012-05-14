#include <iostream>
#include <cstdlib>
#include <set>
#include <map>

using namespace std;

/***
Let r be the remainder when (a−1)^(n) + (a+1)^(n) is divided by a^(2).

For example, if a = 7 and n = 3, then r = 42:
6^(3) + 8^(3) = 728 ≡ 42 mod 49.
And as n varies, so too will r, but for a = 7 it turns out that r_(max) = 42.

For 3 ≤ a ≤ 1000, find ∑ r_(max).
***/

// Properties of mod:
// ( a + b ) % c = ( a % c ) + ( b % c )
// 
int r_max( int a )
{
    set< int > r;
    set< pair< int, int > > amp;

    int am1 = 1;
    int ap1 = 1;
    int a2  = a*a;

    while( true )
    {
        am1 *= a-1;
        am1 %= a2;
        ap1 *= a+1;
        ap1 %= a2;
        int tmp_r = ( am1 + ap1 ) % a2;
        pair< int, int > p( am1, ap1 );
        if ( amp.find( p ) != amp.end() ) break;
        amp.insert( p );
        r.insert( tmp_r );
    }
    int res = *(r.rbegin() );
    //cout << "r_max(" << a << ")=" << res << "[" << r.size() << "]" << endl;
    return res;
}

int main( int argc, char** argv )
{
    int a_min = 3;
    int a_max = 1000;
    if ( argc > 1 ) a_min = atoi( argv[ 1 ] );
    if ( argc > 2 ) a_max = atoi( argv[ 2 ] );

    int sum_r_max = 0;
    for( int i = a_min; i <= a_max; ++i )
    {
        sum_r_max += r_max( i );
    }
    cout << "sum r_max[a=" << a_min << ".." << a_max << "]="
         << sum_r_max << endl;
}
