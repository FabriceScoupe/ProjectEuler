#include <iostream>
#include <cstdlib>
#include <vector>
using namespace std;

// It is possible to write five as a sum in exactly six different ways:
//
// 4 + 1
// 3 + 2
// 3 + 1 + 1
// 2 + 2 + 1
// 2 + 1 + 1 + 1
// 1 + 1 + 1 + 1 + 1
//
// Cardinals of sets in partition of N (card N = n)
// Call that p(n); -1 (full set N not in partition).
// Vague memory of generating function: GF(p)(x)=Prod[i](1-x^i)^(-1)
// Looked up wikipedia: http://en.wikipedia.org/wiki/Partition_(number_theory)
// (oops, that gives p(100)=190,569,292, but let's not cheat!)
// Look up "Discrete Mathematics" by Norman Biggs, chapter 26 explains
// the recurrence used in this program.
// 

// Selected powers: sp1(m) = 1/2*m*(3m-1) sp2(m) = 1/2*m*(3m+1)
// sp1(0) = 0 = sp2(0)
// p(n)  = sum[ m >= 0 ] (-1)^(m+1)*( p(n-sp1(m))+p(n-sp2(m) )
// (as long as n - sp?(m) >= 0 )
// Convention p(0)=1

inline int sp1( int m ) { return (m*(3*m-1))/2; }
inline int sp2( int m ) { return (m*(3*m+1))/2; }

int main( int argc, char** argv )
{
    int n = 100;
    if ( argc > 1 ) n = atoi( argv[ 1 ] );

    // Recurrence 
    vector< int > p;
    p.push_back( 1 ); // p[0] = 1;
    for( int i = 1; i <= n; ++i )
    {
        bool keep_going = true;
        int tmp_p = 0;
        int sp[2];
        for( int m = 1; keep_going; ++m )
        {
            sp[0] = sp1( m );
            sp[1] = sp2( m );
            //cout << sp[0] << " " << sp[1] << endl;
            keep_going = false;
            for( int j = 0; j <= 1; ++j )
            {
                if ( ( i - sp[j] ) >= 0 )
                {
                    tmp_p += ( m % 2 ? p[i-sp[j]] : -p[i-sp[j]] );
                    keep_going = true;
                }
            }
        }
        cout << "p("<<i<<")= " << tmp_p << endl;
        p.push_back( tmp_p );
    }

    cout << "Number of way to write " << n << " as a sum = "
         << p[n] - 1 << endl;
}
