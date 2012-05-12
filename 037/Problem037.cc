#include <iostream>
#include <vector>
#include <map>
using namespace std;

// Find the sum of the only 11 primes that are both truncable from left to 
// right and right to left:
// 3797, 797, 97, 7, 3, 37, 379, 3797 for instance.
// 37, 73, 797, and 3797 already given, so 7 left.
// Cannot contain 0,4,6,8 obviously.
// Can start with 5: 53 works, but only possible position for 5 (or 2)
// Cannot start or end with 1, or 9
// Pattern: ^[2357][1379]*[37]$
//

int root( int n )
{
    int r = 1;
    while( r * r < n ) ++r;
    return r;
}

bool checkPrime( int p )
{
    static map<int,char> cache;
    if ( ( p > 2 ) && ( p % 2 == 0 ) )  return false;
    if ( cache[ p ] > 0 ) return true;
    for( int d = 3; d <= root( p ); d += 2 ) if ( p % d == 0 ) return false;
    cache[ p ] = 1;
    return true;
}

bool checkTruncablePrime( vector<char>& dv, int& p )
{
    bool ok = true;
    int a = 0;
    int b = 0;
    int pw = 1;
    for( int i = 0; ( i < (int) dv.size() ) && ok; ++i )
    {
        a += pw*dv[i];
        pw *= 10;
        b *= 10;
        b += dv[ dv.size()-1-i ];
        ok = checkPrime( a ) && ( checkPrime( b ) );
    }
    p = a;
    if ( ok ) cout << "Found: " << p << endl;
    return ok;
}

int main( int argc, char** argv )
{
    int count = 0;
    int sum = 0;
    vector<char> dv;
    dv.push_back( 3 ); dv.push_back( 2 ); // Start at 23
    while( count < 11 )
    {
        int p = 0;
        if ( checkTruncablePrime( dv, p ) )
        {
            ++count;
            sum += p;
        }
        int nd = dv.size();
        // Pattern: ^[2357][1379]*[37]$
        if ( 3 == dv[ 0 ] ) { dv[ 0 ] = 7; continue; }
        dv[ 0 ] = 3;
        bool carry = true;
        for( int d = 1; ( d <= nd -2 ) && carry; ++d ) // middle digits
        {
            carry = false;
            switch( dv[ d ] )
            {
                case 1: dv[ d ] = 3; break;
                case 3: dv[ d ] = 7; break;
                case 7: dv[ d ] = 9; break;
                default: dv[ d ] = 1; carry = true; break;
            }
        }
        if ( ! carry ) continue;
        // start digit
        switch( dv[ nd - 1] )
        {
            case 2: dv[ nd-1 ] = 3; break;
            case 3: dv[ nd-1 ] = 5; break;
            case 5: dv[ nd-1 ] = 7; break;
            default: dv[ nd-1 ] = 1; dv.push_back( 2 ); break;
        }
    }
    cout << "sum = " << sum << endl;
}
