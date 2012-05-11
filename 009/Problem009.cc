#include <iostream>
#include <cstdlib>
#include <map>
using namespace std;

// Find pythagorean triplet(s) (a,b,c) such as a+b+c = 1000
// a*a+b*b=c*c => a + b + sqrt( a*a + b*b ) = 1000
// Assume a <= b < c
// "Flat" triangle a = 0 => b = c = 1000/2 => max b is 1000/2
// Half-square: a = b => c = sqrt(2)*a => b = 1000 / (2+sqrt(2))
//                                     => min b ~ 1000 / 3
// so 1 <= a <= 1000/3, 1000/3 <= b <= 1000/2.

map<int,int> roots;

bool check( int a, int b, int n )
{
    int r = roots[ a*a + b*b ];
    return( ( a + b + r == n ) &&
            ( r*r == a*a + b*b ) );
}

int main( int argc, char** argv )
{
    int n = 1000;
    if ( argc > 1 ) n = atoi( argv[1] );

    // Initialise roots, up to 2*(n/3)^2
    int max_square_c = 2*(n/3)*(n/3);
    cout << "Max c^2 = " << max_square_c << endl;
    for(int i = 1; i*i <= max_square_c; ++i) roots[i*i]=i;

    int iter = 0;
    for(int b = n/2; b >= n/3; --b )
        for( int a = 1; a <= b; ++a )
        {
            if ( check( a, b, n ) )
            {
                cout << endl <<  a << " + " << b  << " + "
                     << roots[a*a+b*b] << " = " << n << endl;
                long long prod = a*b*roots[a*a+b*b];
                cout << "a.b.c = " << prod << endl;
            }
            ++iter;
            if ( iter % 1000 == 0 )
            {
                cout << '.';
                flush(cout);
            }
        }
    cout << endl;
}
