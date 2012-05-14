#include <iostream>
#include <cstdlib>
#include <vector>
using namespace std;

// Continued fractions:
// e = [2; 1,2,1,1,4,1,1,6,1,1,....,1,2k,1,...]
// Convergents:
// E0 = 2 ; E1 = 2 + 1 | 1 + 1 | 2 = 2 + 2/3 = 8 / 3
// E3 = 11/4 ; E4 = 19/7 ; E5 = 87/32 ; E6 = 106/39 ;
// E7 = 193/71 ; E8 = 1264 / 465 ; E9 = 1457 / 536
//
// Sum of digits of numerator of 10th convergent (E9) = 1+4+5+7 = 17
// Find the sum of digits in the numerator of 100th convergent of CF of e.

// a0 = 2; a(k>0) = ( k % 3 == 2 ? 2*(k/3+1) : 1 )
// a + 1 / b = ( ab + 1 ) / b
// Operate in reverse: start from a100
// Calculate F100 = a100
// Fn-1 = a(n-1) + 1 / Fn until F0 = E100 reached.
// Reuse problem 57's stuff (BigInt)
// Fn = Nn/Dn with N100 = a100 and D100 = 1
// Fn-1 = a(n-1) + Dn/Nn <=> Nn-1 = a(n-1).Nn + Dn, Dn-1 = Nn

typedef vector<char> BigInt;

// Add BigInt a and b into s
void add( BigInt& a, BigInt& b, BigInt& s )
{
    s.clear();

    for(unsigned int i = 0; (i < a.size()) || (i < b.size()); ++i) {
        s.push_back(0);
    }
    s.push_back(0);

    for(unsigned int i = 0; (i < a.size()) || (i < b.size()); ++i )
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
    while(0 == s[s.size()-1]) s.erase( (++s.rbegin()).base() );
}

// Multiply BigInt a and b into c
void multiply( BigInt& a, BigInt& b, BigInt& c )
{
    c.clear();
    int deg_a = a.size(); // Degree of a
    while( a[deg_a-1] == 0 ) --deg_a;
    int deg_b = b.size(); // Degree of b
    while( b[deg_b-1] == 0 ) --deg_b;

    for(int i = 0; i < deg_a+deg_b; ++i) c.push_back( 0 );
    for(int i = 0; i < deg_a; ++i) {
        for( int j = 0; j < deg_b; ++j ) {
            int prod = a[i]*b[j];
            int pos = i+j;
            while( ( prod > 0 ) || ( c[pos] >= 10 ) ) {
                c[pos] += prod % 10;
                if (c[pos] >= 10 ) {
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
    for(unsigned int i = n.size(); i > 0; --i) cout << (int) n[i-1];
}

void int2BigInt( int n, BigInt& b )
{
    int m = n;
    b.clear();
    while(m > 0) {
        b.push_back( m % 10 );
        m /= 10;
    }
}

int a_euler( int k )
{
    return( 0 == k ? 2 : ( k % 3 ) == 2 ? 2*((k/3)+1) : 1 );
}

int main( int argc, char** argv )
{
    int n = 99;
    if ( argc > 1 ) n = atoi( argv[ 1 ] );
    int m = n;
    BigInt n_curr, n_prev;
    BigInt d_curr, d_prev;
    BigInt tmp;
    BigInt a_prev;
    int2BigInt( a_euler( n ), n_curr );
    d_curr.push_back( 1 );
    while( n > 0 ) {
// Fn = Nn/Dn with N100 = a100 and D100 = 1
// Fn-1 = a(n-1) + Dn/Nn <=> Nn-1 = a(n-1).Nn + Dn, Dn-1 = Nn
        int2BigInt( a_euler( n-1 ), a_prev );
        multiply( a_prev, n_curr, tmp );
        n_prev = tmp;
        add( n_prev, d_curr, tmp );
        n_prev = tmp;
        d_prev = n_curr;
        --n;
        n_curr = n_prev;
        d_curr = d_prev;
    }

    cout << "E(" << m << ")= ";
    dump( n_curr ); 
    cout << " / ";
    dump( d_curr );
    cout << endl;

    int sum = 0;
    for(unsigned int i = 0; i < n_curr.size(); ++i) sum += n_curr[i];
    cout << endl << "sum = " << sum << endl;
    return 0;
}
