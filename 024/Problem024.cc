#include <iostream>
#include <cstdlib>
#include <string.h>
using namespace std;

/*
 * Project Euler: Problem 024 (http://projecteuler.net/problem=24)
 */

// Find millionth lexicographic permutation of {0,1,2,3,4,5,6,7,8,9}

static inline void swap( char& a, char& b )
{
    //cout << "Swapping " << (int) a << " and " << (int) b << endl;
    char tmp = a; a = b; b = tmp;
}

// Reversing set
static inline void reverse( char* set, int length )
{
    for( int i = 0; 2*i < length; ++i ) swap( set[i], set[ length -1 - i ] );
}

// Get next permutation in set, or return false if last one reached.
bool next_perm( char* set, int dim )
{
    bool ok = false;
    if ( dim > 2 ) {
        ok = next_perm( set + 1, dim - 1 );
        if ( ! ok ) {
             // No next perm for set + 1 => set + 1 "reverse" ordered
             // Try and find smallest elem in set+1 greater than set[0]
             int pos = dim-1;
             while( ( pos > 0 ) && ( set[0] > set[pos] ) ) --pos;
             if ( pos > 0 ) {
                 swap( set[0], set[pos] );
                 // reverse order of set+1
                 reverse( set+1, dim-1 );
                 ok = true;
             }
        }
    } else if ( 2 == dim ) {
        ok = ( set[ 1 ] > set[ 0 ] );
        if ( ok ) swap( set[ 1 ], set[ 0 ] );
    }
    return ok;
}

int main( int argc, char** argv )
{
    int n = 1000000;
    char* raw = (char*) "0123456789";
    if ( argc > 1 ) n = atoi( argv[1] );
    if ( argc > 2 ) raw = argv[2];

    int len = strlen( raw );
    char* data = new char[ len+1 ];
    data[ len ] = 0;
    int i = 0;
    for( i = 0; i < len; ++i ) data[i] = raw[i];

    for( i = 1; i < n; ++i ) {
        //if ( i % 1000 == 0 ) { cout << '.'; flush( cout ); }
        if ( ! next_perm( data, len ) ) {
            cout << endl << i << "th permutation was the last one!" << endl;
            exit(1);
        }
    }

    cout << endl <<  n << "th permutation of " << raw << ":" << endl;
    cout << "Answer: " << data << endl;
    return 0;
}
