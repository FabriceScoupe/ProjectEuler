#include <iostream>
#include <cstdlib>
#include <map>
#include <set>
using namespace std;

// It turns out that 12 cmn is the smallest length of wire that can be
// be bent to form an integer-sided right-angle triangle in exactly one
// way, but there are more examples:
// 12 cm: (3,4,5)
// 24 cm: (6,8,10)
// 30 cm: (5,12,13)
// 36 cm: (9,12,15)
// 40 cm: (8,15,17)
// 48 cm: (12,16,20)
// In contrast, some lengths of wire, like 20 cm, cannot be bent to form
// an integer sided right angle triangle, and other lengths allow more than
// one solution to be found; for example, using 120 cm it is possible to form
// exactly three different integer sided right angle triangles.
// 120 cm: (30,40,50),(20,48,52),(24,45,51)
// Given that L is the length of the wire, for how many values of 
// L <= 1,500,000 can exactly one integer sided right angle triangle be formed?


// L = a + b + c , a < b < c and a^2+b^2=c^2
// a = m^2 - n^2 ; b = 2.m.n ; c = m^2 + n^2 ( m > n > 0 )
// L = 2m^2 + 2m.n = 2m( m + n );
// Then multiply by factor k >= 2, as long as L <= limit

int gcd( int m, int n )
{
    int a = m;
    int b = n;
    int r = a % b;
    while( r > 0 )
    {
        a = b;
        b = r;
        r = a % b;
    }
    return b;
}

int main( int argc, char** argv )
{
    int limit = 1500000;
    if ( argc > 1 ) limit = atoi( argv[ 1 ] );
    int r = 1;
    while( r * r < limit/2 ) ++r;
    map<int,int> freqs;
    set<pair<int,int> > pairs;
    for( int m = 1; m < r; ++m )
    {
        for( int n = 1; n < m; ++n )
        {
            int   a = m*m - n*n;
            int   b = 2*m*n;
            int len = 2*m*(m+n);
            for( int k = 1; k*len <= limit; ++k )
            {
                pair<int,int> p(k*(a<b?a:b),k*(a<b?b:a));
                if ( pairs.find( p ) == pairs.end() )
                {
                    cout << k*len<<": " << k*a << "," << k*b << endl;
                    ++freqs[ k*len ];
                    pairs.insert( p );
                }
            }
        }
    }

    int count = 0;
    for( map<int,int>::iterator i = freqs.begin(); i != freqs.end(); ++i )
    {
        cout << i->first << ": " << i->second << " time(s)." << endl;
        if (i->second == 1) ++count;
    }
    cout << "Count = " << count << endl;
}
