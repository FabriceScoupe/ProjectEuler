#include <iostream>
#include <set>

using namespace std;

/***
By using each of the digits from the set {1,2,3,4} exactly once, and making
use of the four arithmetic operations (+,-,*,.) and brackets or parentheses,
it is possible to form different positive integer targets.

For example:
8 = ( 4 * ( 1 + 3 ) ) / 2
14 = 4 * ( 3 + 1 / 2 )
19 = 4 * ( 2 + 3 ) - 1
36 = 3 * 4 * ( 2 + 1 )

Note that concatenations of the digits, like 12 + 34, are not allowed.

Using the set { 1,2,3,4 }, it is possible to obtain 31 different target
numbers of which 36 is the maximum, and each of the numbers 1 to 28 can be
obtained before encountering the first non-expressible number.

Find the set of four distinct digits a < b < c < d, for which the longest
set of consecutive integers, 1 to n, can be obtained, giving your answer
as a string: abcd.
***/

// Thinking in Reverse Polish Notation:
// Operands a, b, c and d, then 3 possible operations among +,-,* and /
// ( 4 * ( 1 + 3 ) ) / 2 -> 1 3 + 4 * 2 /
// 4 * ( 3 + 1 / 2 ) -> 1 2 / 3 + 4 *
// ...
// Permutations -> 4! = 24.
// 4*4*4 = 64 different series of operations
//
// Also case: a b op1 c d op2 op3 !

inline void eval( int na, int da, int nb, int db, char op, int&n, int& d )
{
    int nn;
    int dd;
    switch( op )
    {
        case 0: // Addition na/da + nb/db = (db*na + da*nb) / (da*db)
            nn = db*na + da*nb;
            dd = da*db;
            break;
            
        case 1: // Substraction na/da - nb/db = (db*na - da*nb) / (da*db)
            nn = db*na - db*nb;
            dd = da*db;
            break;

        case 2: // Multiplication
            nn = na*nb;
            dd = da*db;
            break;

        case 3: // Division
            nn = na*db;
            dd = da*nb;
            break;
    }

    if ( nn % dd == 0 )
    {
        nn /= dd;
        dd = 1;
    }
    n = nn;
    d = dd;
}

int calc( char a1, char a2, char a3, char a4, char op1, char op2, char op3 )
{
    int n;
    int d;
    eval( a1, 1, a2, 1, op1, n, d );
    eval( n , d, a3, 1, op2, n, d );
    eval( n , d, a4, 1, op3, n, d );
    int ir = 0;
    if ( 1 == d ) ir = n;
    return ir;
}

int calc2( char a1, char a2, char a3, char a4, char op1, char op2, char op3 )
{
    int n1;
    int d1;
    eval( a1, 1, a2, 1, op1, n1, d1 );
    int n2;
    int d2;
    eval( a3, 1, a4, 1, op2, n2, d2 );
    eval( n1 , d1, n2, d2, op3, n1, d1 );
    int ir = 0;
    if ( 1 == d1 ) ir = n1;
    return ir;
}

int max_n( char a, char b, char c, char d )
{
    set< int > results;
    for( char op1 = 0; op1 < 4; ++op1 )
        for( char op2 = 0; op2 < 4; ++op2 )
            for( char op3 = 0; op3 < 4; ++op3 )
    {
        results.insert( calc( a,b,c,d,op1,op2,op3 ) );
        results.insert( calc( a,b,d,c,op1,op2,op3 ) );
        results.insert( calc( a,c,b,d,op1,op2,op3 ) );
        results.insert( calc( a,c,d,b,op1,op2,op3 ) );
        results.insert( calc( a,d,b,c,op1,op2,op3 ) );
        results.insert( calc( a,d,c,b,op1,op2,op3 ) );
        results.insert( calc( b,a,c,d,op1,op2,op3 ) );
        results.insert( calc( b,a,d,c,op1,op2,op3 ) );
        results.insert( calc( b,c,a,d,op1,op2,op3 ) );
        results.insert( calc( b,c,d,a,op1,op2,op3 ) );
        results.insert( calc( b,d,a,c,op1,op2,op3 ) );
        results.insert( calc( b,d,c,a,op1,op2,op3 ) );
        results.insert( calc( c,a,b,d,op1,op2,op3 ) );
        results.insert( calc( c,a,d,b,op1,op2,op3 ) );
        results.insert( calc( c,b,a,d,op1,op2,op3 ) );
        results.insert( calc( c,b,d,a,op1,op2,op3 ) );
        results.insert( calc( c,d,a,b,op1,op2,op3 ) );
        results.insert( calc( c,d,b,a,op1,op2,op3 ) );
        results.insert( calc( d,a,b,c,op1,op2,op3 ) );
        results.insert( calc( d,a,c,b,op1,op2,op3 ) );
        results.insert( calc( d,b,a,c,op1,op2,op3 ) );
        results.insert( calc( d,b,c,a,op1,op2,op3 ) );
        results.insert( calc( d,c,a,b,op1,op2,op3 ) );
        results.insert( calc( d,c,b,a,op1,op2,op3 ) );

        results.insert( calc2( a,b,c,d,op1,op2,op3 ) );
        results.insert( calc2( a,b,d,c,op1,op2,op3 ) );
        results.insert( calc2( a,c,b,d,op1,op2,op3 ) );
        results.insert( calc2( a,c,d,b,op1,op2,op3 ) );
        results.insert( calc2( a,d,b,c,op1,op2,op3 ) );
        results.insert( calc2( a,d,c,b,op1,op2,op3 ) );
        results.insert( calc2( b,a,c,d,op1,op2,op3 ) );
        results.insert( calc2( b,a,d,c,op1,op2,op3 ) );
        results.insert( calc2( b,c,a,d,op1,op2,op3 ) );
        results.insert( calc2( b,c,d,a,op1,op2,op3 ) );
        results.insert( calc2( b,d,a,c,op1,op2,op3 ) );
        results.insert( calc2( b,d,c,a,op1,op2,op3 ) );
        results.insert( calc2( c,a,b,d,op1,op2,op3 ) );
        results.insert( calc2( c,a,d,b,op1,op2,op3 ) );
        results.insert( calc2( c,b,a,d,op1,op2,op3 ) );
        results.insert( calc2( c,b,d,a,op1,op2,op3 ) );
        results.insert( calc2( c,d,a,b,op1,op2,op3 ) );
        results.insert( calc2( c,d,b,a,op1,op2,op3 ) );
        results.insert( calc2( d,a,b,c,op1,op2,op3 ) );
        results.insert( calc2( d,a,c,b,op1,op2,op3 ) );
        results.insert( calc2( d,b,a,c,op1,op2,op3 ) );
        results.insert( calc2( d,b,c,a,op1,op2,op3 ) );
        results.insert( calc2( d,c,a,b,op1,op2,op3 ) );
        results.insert( calc2( d,c,b,a,op1,op2,op3 ) );
    }

    set<int>::iterator it = results.begin();
    for( ; (it != results.end())&&(*it<1); ++it );
    int max_n = 0;
    if ( ( it != results.end() )&&( *it == 1 ) )
    {
        for( ; it != results.end(); ++it)
        {
            if ( *it == max_n+1 ) ++max_n;
        }
    }
    return max_n;
}

int main( int argc, char** argv )
{
    int ma = 1; int mb = 2; int mc = 3; int md = 4;
    int max = 28;

    for( char a = 1; a <= 9; ++a )
        for( char b = a+1; b <= 9; ++b )
            for( char c = b+1; c <= 9; ++c )
                for( char d = c+1; d <= 9; ++d )
    {
        int m = max_n( a,b,c,d );
        cout<<"{"<<(int)a<<","<<(int)b<<","<<(int)c<<","<<(int)d
            <<"} -> "<<m<<endl;
        if ( m > max )
        {
            ma = a; mb = b; mc = c; md = d;
            max = m;
        }
    }

    cout <<endl<<"Max: {"<<ma<<","<<mb<<","<<mc<<","<<md<<"} => "<<max<<endl;
}
