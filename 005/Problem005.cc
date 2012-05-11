#include <iostream>
#include <cstdlib>
#include <map>

using namespace std;

// Find smallest common multiple of integers 1 to n
int findSmallestCommonMultiple( int n )
{
    map< int, int > decomp;
    for( int i = 2; i <= n; ++i )
    {
        cout << i << " = ";
        int p = 1;
        int j = i;
        while( j > 1 )
        {
            int m = 0;
            ++p;
            while( j % p == 0 )
            {
                cout << p << " ";
                ++m;
                j /= p;
            }
            if ( m > decomp[ p ] ) decomp[ p ] = m;
        }
        cout << endl;
    }

    int r = 1;
    for( map<int,int>::iterator i = decomp.begin();
         i != decomp.end(); ++i )
    {
        for( int j = 0; j < i->second; ++j )
        {
            cout << i->first << " ";
            r *= i->first;
        }
    }
    cout << endl;
    return r;
}

int main( int argc, char** argv )
{
    int n = 20;
    if ( argc > 1 ) n = atoi( argv[1] );
    int s = findSmallestCommonMultiple( n );
    cout << "Smallest common multiple of " << n << " = " << s << endl;
}
