#include <iostream>
#include <string.h>

using namespace std;

/***
We shall define a square lamina to be a square outline with a square "hole"
so that the shape possesses vertical and horizontal symmetry.

Given eight tiles it is possible to form a lamina in only one way:
3x3 square with a 1x1 hole in the middle.
However, using thirty-two tiles it is possible to form two distinct laminae.

If t represents the number of tiles used,
we shall say that t = 8 is type L(1) and t = 32 is type L(2).

Let N(n) be the number of t ≤ 1000000 such that t is type L(n);
for example, N(15) = 832.

What is ∑ N(n) for 1 ≤ n ≤ 10?
***/

// Similar to problem 173.

void build_L( int t, int* L )
{
    int max_r1 = t / 4 + 1;
    for( int r1 = 3; r1 <= max_r1; ++r1 )
    {
        for( int r2 = r1-2; r2 > 0; r2 -= 2 )
        { 
            int x = r1*r1 - r2*r2;
            if ( x > t ) break;
            ++L[ x ];
        }
    }
}

int main( int argc, char** argv )
{
    int L[1000001];
    memset( L, 0, 1000001*sizeof( int ) );
    
    build_L( 1000000, L );
    cout << "8 is type L(" << L[8] << "), 32 type L(" << L[32] << ")" << endl;

    int N[16];
    memset( N, 0, 16*sizeof(int) );
    for( int i = 1; i <= 1000000; ++i )
    {
        int li = L[i];
        if ( ( li > 0 ) && ( li <= 15 ) ) ++N[li];
    }

    cout << "N(15) = " << N[15] << endl;
    int sum_N = 0;
    for( int i = 1; i <= 10; ++i ) sum_N += N[i];
    cout << "Sum[n=1..10] N(n) = " << sum_N << endl; 
}
