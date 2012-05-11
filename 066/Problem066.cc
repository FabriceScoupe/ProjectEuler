#include <iostream>
#include <vector>
#include <map>
#include <cstdlib>
using namespace std;

// Consider quadratic Diophantine equations of the form: x^2-D.y^2 = 1
// For example when D=13, the minimal solution in x is 649^2-13*180^2 = 1
// It can be assumed that there are no solutions in positive integers
// when D is square.
// By finding minimal solutions in x for D = {2,3,5,6,7}, we get:
// 3^2-2*2^2 = 1
// 2^2-3*1^2 = 1
// 9^2-5*4^2 = 1
// 5^2-6*2^2 = 1
// 8^2-7*3^2 = 1
// Hence max { min x / E y / x^2 - D*y^2 = 1 } when D <= 7 is 5
// Find that max when D <= 1000

// Looked up "Diophantine equations" in Wikipedia and found out that
// this is "Pell's Equation", which can be solved by using the convergents
// of the continued fraction of sqrt(D): try numerator for x and denominator
// for y, at some point a solution will emerge.
// So, re-use solutions of problems 65 and 

struct BigInt : public vector<char>
{
    bool operator< ( const BigInt& right ) const
    {
        bool yes = false;
        if ( this->size() != right.size() )
        {
            yes = ( size() < right.size() );
        }
        else
        {
            for( int i = size()-1; i >= 0; --i )
            {
                if ( (*this)[i] != right[i] )
                {
                    yes = ( (*this)[i] < right[i] );
                    break;
                }
            }
        }
        return yes;
    }
};

// Add BigInt a and b into s
void add( BigInt& a, BigInt& b, BigInt& s )
{
    s.clear();

    for( int i = 0; ( i < a.size()) || ( i < b.size() ); ++i ) s.push_back(0);
    s.push_back( 0 ); // For carry, if need be.

    for( int i = 0; ( i < a.size()) || ( i < b.size() ); ++i )
    {
        char da = ( i < a.size() ? a[i] : 0 );
        char db = ( i < b.size() ? b[i] : 0 );
        s[i] += da + db;
        if ( s[ i ] >= 10 )
        {
            s[ i ] -= 10;
            ++s[ i+1 ];
        }
    }
    // Clean-up leading zeroes
    while( 0 == s[ s.size()-1 ] ) s.erase( (++s.rbegin()).base() );
}

// Multiply BigInt a and b into c
void multiply( BigInt& a, BigInt& b, BigInt& c )
{
    c.clear();
    int deg_a = a.size();             // Degree of a
    while( a[deg_a-1] == 0 ) --deg_a; // Ignore leading zeroes
    int deg_b = b.size();             // Degree of b
    while( b[deg_b-1] == 0 ) --deg_b; // Ignore leading zeroes

    for( int i = 0; i < deg_a+deg_b; ++i ) c.push_back( 0 );
    for( int i = 0; i < deg_a; ++i )
    {
        for( int j = 0; j < deg_b; ++j )
        {
            int prod = a[i]*b[j];
            int pos = i+j;
            while( ( prod > 0 ) || ( c[pos] >= 10 ) )
            {
                c[pos] += prod % 10;
                if (c[pos] >= 10 )
                {
                    c[pos]-=10;
                    ++c[pos+1];
                }
                prod /= 10;
                ++pos;
            }
        }
    }
    while( 0 == c[ c.size()-1 ] ) c.erase( (++c.rbegin()).base() );
}

void dump( BigInt& n )
{
    for( int i = n.size()-1; i >= 0; --i ) cout << (int) n[i];
}

void int2BigInt( int n, BigInt& b )
{
    int m = n;
    b.clear();
    while( m > 0 )
    {
        b.push_back( m % 10 );
        m /= 10;
    }
}

int floor_root( int n )
{
    int r = 1;
    while( r * r <= n ) ++r;
    return r-1;
}

long long a_root( int dd, int n )
{
    static map< pair<int,int>, long long > cache;
    map< pair<int,int>, long long >::iterator hit = 
        cache.find( pair<int,int>( dd, n ) );
    if ( hit != cache.end() ) return hit->second;

    long long m,d,a,m_next,d_next,a_next;
    long long r = floor_root( dd );
    m = 0;
    d = 1;
    a = r;
    for( int i = 1; i <= n; ++i )
    {
        m_next = d*a - m;
        d_next = (dd - m_next*m_next) / d;
        a_next = ( r + m_next ) / d_next;
        m = m_next;
        d = d_next;
        a = a_next;
    }
    cache[ pair< int,int >( dd, n ) ] = a;
    return a;
}

// Return element n in series S0 = a0, S1 = a0 + 1/a1, ...
// Of convergents of continued fraction of sqrt(d).
void getNumDenom( int m, int d, BigInt& num, BigInt& denom )
{
    num.clear();
    denom.clear();

    int n = m;
    BigInt n_curr, n_prev;
    BigInt d_curr, d_prev;
    BigInt tmp;
    BigInt a_prev;
    int2BigInt( a_root( d, n ), n_curr );
    d_curr.push_back( 1 );
    while( n > 0 )
    {
// Fn = Nn/Dn with N100 = a100 and D100 = 1
// Fn-1 = a(n-1) + Dn/Nn <=> Nn-1 = a(n-1).Nn + Dn, Dn-1 = Nn
        int2BigInt( a_root( d, n-1 ), a_prev );
        multiply( a_prev, n_curr, tmp );
        n_prev = tmp;
        add( n_prev, d_curr, tmp );
        n_prev = tmp;
        d_prev = n_curr;
        --n;
        n_curr = n_prev;
        d_curr = d_prev;
    }
    num   = n_curr;
    denom = d_curr;
}

int main( int argc, char** argv )
{
    int limit = 1000;
    if ( argc > 1 ) limit = atoi( argv[ 1 ] );
    int r = 1; // root tracker
    BigInt num, denom, sqr1, sqr2, dmul, tmp, max_x;
    int max_d = 0;

    for( int i = 2; i <= limit; ++i )
    {
        if ( r*r < i ) ++r;
        if ( r*r == i ) continue; // Skip squares
        bool found = false;
        int n = 0;
        do
        {
            getNumDenom( n, i, num, denom );
            multiply( num, num, sqr1 );
            multiply( denom, denom, sqr2 );
            int2BigInt( i, dmul );
            multiply( dmul, sqr2, tmp );
            sqr2 = tmp;
            int2BigInt( 1, dmul );
            add( dmul, sqr2, tmp );
            found = ( sqr1 == tmp );
            ++n;
        }
        while( !found );
        if ( max_x < num ) // Using BigInt operator< defined above!
        {
            max_x = num;
            max_d = i;
        }
        cout << "For D=" << i << ": ( x = ";
        dump( num );
        cout << ", y = ";
        dump( denom );
        cout << "), max D so far = " << max_d << endl;
    }
}
