#include <iostream>
#include <cstdlib>
#include <vector>
using namespace std;

// Let p(n) represent the number of different ways in which n coins can be
// separated into piles. For example, five coins can separated into piles
// in exactly seven different ways, so p(5)=7.
//
// OOOOO 
// OOOO   O 
// OOO   OO 
// OOO   O   O 
// OO   OO   O 
// OO   O   O   O 
// O   O   O   O   O 
//
// Find the least value of n for which p(n) is divisible by one million.

// Another variation on Problem 76. Reuse, use long longs
int main( int argc, char** argv )
{
    long long div = 1000000LL;
    if ( argc > 1 ) div = atol( argv[ 1 ] );

    // div assumed to be a multiple of 10. So only care about
    // <number> % div

    // Recurrence
    vector< long long > p;
    p.push_back( 1 ); // p[0] = 1;
    bool found = false;
    long long i = 0;
    for( i = 1; !found ; ++i )
    {
        bool keep_going = true;
        long long tmp_p = 0;
        long long sp[2];
        for( long long m = 1; keep_going; ++m )
        {
            sp[0] = (m*(3*m-1))/2;
            sp[1] = (m*(3*m+1))/2;

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
        p.push_back( tmp_p % div );
        found = ( tmp_p % div == 0 );
    }

    cout << "p(" << i-1 << ") is divisible by " << div << "." << endl;
}
