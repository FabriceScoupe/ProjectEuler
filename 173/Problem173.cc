#include <iostream>
#include <cstdlib>

using namespace std;

/***
We shall define a square lamina to be a square outline with a square "hole"
so that the shape possesses vertical and horizontal symmetry. For example,
using exactly thirty-two square tiles we can form two different square
laminae:

With one-hundred tiles, and not necessarily using all of the tiles at one time,
it is possible to form forty-one different square laminae.

Using up to one million tiles how many different square laminae can be formed?
***/

// n tiles: square shape from floor(sqrt(n)) to floor( n / 4 )+1

int main( int argc, char** argv )
{
    int limit = 1000000;
    if ( argc > 1 ) limit = atoi( argv[ 1 ] );

    int l = limit / 4+1;

    int count = 0;

    for( int r1 = 3; r1 <= l ; ++r1 )
    {
        for( int r2 = r1 - 2; (r2>0)&&((r1*r1-r2*r2)<=limit); r2-=2 )
        {
            //cout << r1 << "^2-" << r2 << "^2 = " << r1*r1-r2*r2 << endl;
            ++count;
        }
    }

    cout << count << " square laminae are possible with "
         << limit << " tiles." << endl;
}
