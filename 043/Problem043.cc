#include <iostream>
using namespace std;

// Find the sum of all 0 to 9 pandigital numbers with the following 
// property: let n be d1d2d3d4d5d6d7d8d9d10 (digits in "natural" order)
// d2d3d4 % 2 == 0
// d3d4d5 % 3 == 0
// d4d5d6 % 5 == 0
// d5d6d7 % 7 == 0
// d6d7d8 % 11 == 0
// d7d8d9 % 13 == 0
// d8d9d10 % 17 == 0

void swap( char& a, char& b )
{
    char tmp = a; a = b; b = tmp;
}

// Reversing set
void reverse( char* set, int length )
{
    for( int i = 0; 2*i < length; ++i ) swap( set[i], set[ length -1 - i ] );
}

// Get next permutation in set, or return false if last one reached.
bool next_perm( char* set, int dim )
{
    bool ok = false;
    if ( dim > 2 )
    {
        ok = next_perm( set + 1, dim - 1 );
        if ( ! ok )
        {
             // No next perm for set + 1 => set + 1 "reverse" ordered
             // Try and find smallest elem in set+1 greater than set[0]
             int pos = dim-1;
             while( ( pos > 0 ) && ( set[0] > set[pos] ) ) --pos;
             if ( pos > 0 )
             {
                 swap( set[0], set[pos] );
                 // reverse order of set+1
                 reverse( set+1, dim-1 );
                 ok = true;
             }
        }
    }
    else if ( 2 == dim )
    {
        ok = ( set[ 1 ] > set[ 0 ] );
        if ( ok ) swap( set[ 1 ], set[ 0 ] );
    }
    return ok;
}

int main( int argc, char** argv )
{
    long long sum = 0;
    char n[11];
    n[10]=0;
    for( int i = 0; i < 10; ++i ) n[i]=i;
   
    do
    {
        if ( ( n[3] % 2 == 0 ) &&
             ( ( n[2]+n[3]+n[4] ) % 3 == 0 ) &&
             ( ( n[5] == 5 ) || ( n[5] == 0 ) ) &&
             ( ( 100*n[4]+10*n[5]+n[6] ) % 7 == 0 ) &&
             ( ( 100*n[5]+10*n[6]+n[7] ) % 11 == 0 ) &&
             ( ( 100*n[6]+10*n[7]+n[8] ) % 13 == 0 ) &&
             ( ( 100*n[7]+10*n[8]+n[9] ) % 17 == 0 ) )
        {
            cout << "Found: ";
            long long val = 0;
            for( int i = 0; i < 10; ++i )
            {
                cout << (int)n[i];
                val *= 10;
                val += n[i];
            }
            sum += val;
            cout << endl;
        }
    } while( next_perm( n, 10 ) );
    cout << endl << "Sum = " << sum << endl;
}
