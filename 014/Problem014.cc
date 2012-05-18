#include <iostream>
#include <cstdlib>
#include <map>
using namespace std;

/*
 * Project Euler: Problem 014 (http://projecteuler.net/problem=14)
 */

// Finding starting number < 1000000 producing longest chain.

map<long long,int> lengths;

static inline long long next( long long n )
{
    return( n % 2 == 0 ? n/2 : 3*n+1 );
}

// length of sequence starting with n0
int length( long long n0 )
{
    int       count = 1;
    long long n     = n0;
    //cout << "Sequence " << n0; 
    do {
        n = next(n);
        //cout << " -> " << n;
        int len = lengths[n]; // know the length of this sequence?
        if ( len > 0 ) {
            //cout << " + " << len; // then simply add it and get out
            count += len;
            break;
        } else {
            ++count;
        }
    } while( n > 1 );
    //cout << " ( " << count << " )" << endl;
    lengths[n0] = count; // learning!
    return count;
}

int main( int argc, char** argv )
{
    long long n = 1000000LL;
    if ( argc > 1 ) n = atol( argv[1] );
 
    int max = 0;
    long long max_n0 = 0;
    for( long long i = 2; i < n; ++i ) {
        int l = length(i);
        if ( l > max ) {
            max = l;
            max_n0 = i;
        }
        if ( i % 1000 == 0 ) { cout << '.'; flush( cout ); }
    }
    cout << endl;
    cout << "Longest sequence starting under " << n << ": " << endl;
    cout << "Start with " << max_n0 << ", " << max << " long." << endl;
    cout << "Answer: " << max_n0 << endl;
    return 0;
}
