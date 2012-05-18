#include <iostream>
#include <cstdlib>
#include <vector>
using namespace std;

/*
 * Project Euler: Problem 020 (http://projecteuler.net/problem=20)
 */

// Sum of digits in 100!

typedef vector<char> BigInt;

void int2BigInt( int n, BigInt& c )
{
    c.clear();
    int m = n;
    while( m > 0 )
    {
        c.push_back( m % 10 );
        m /= 10;
    }
}

void bigInt2BigInt( BigInt& src, BigInt& tgt )
{
    tgt.clear();
    for( int i = 0; i < (int) src.size(); ++i ) tgt.push_back( src[i] );
}

void dump( BigInt& a )
{
    int i = a.size()-1;
    while( a[i] == 0 ) --i;
    while( i >= 0 )
    {
        cout << (int) a[i];
        --i;
    }
    cout << endl;
}

void multiply( BigInt& a, BigInt& b, BigInt& c )
{
    c.clear();
    int deg_a = a.size(); // Degree of a
    while( a[deg_a-1] == 0 ) --deg_a;
    int deg_b = b.size(); // Degree of b
    while( b[deg_b-1] == 0 ) --deg_b;
    for( int i = 0; i < deg_a+deg_b; ++i ) c.push_back(0);

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
}

int main( int argc, char** argv )
{
    int n = 100;
    if ( argc > 1 ) n = atoi(argv[1]);
    BigInt a;
    int2BigInt(1, a);
    BigInt b;
    BigInt c;
    for( int i = 2; i <= n; ++i )
    {
       int2BigInt( i, b );
       multiply( a, b, c );
       bigInt2BigInt( c, a );
    }
    cout << n << "! = ";
    dump(c);
    cout << "Sum of digits of " << n << "! :" << endl;
    int sum = 0;
    for( int i = 0; i < (int) c.size(); ++i ) sum += c[i];
    cout << "Answer: " << sum << endl;
    return 0;
}
