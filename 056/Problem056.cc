#include <iostream>
#include <cstdlib>
#include <vector>
using namespace std;

/*
 * Project Euler: Problem 056 (http://projecteuler.net/problem=56)
 */

// A googol (10^100) is a massive number: one followed by one-hundred zeros;
// 100^100 is almost unimaginably large: one followed by two-hundred zeros.
// Despite their size, the sum of the digits in each number is only 1.
//
// Considering natural numbers of the form, a^b, where a, b < 100,
// what is the maximum digital sum?

// Not subtle, use BigInts

typedef vector<char> BigInt;

// Multiply BigInt a and BigInt b, into c, returns c's sum of digits
int multiply( BigInt& a, BigInt& b, BigInt& c )
{
    c.clear();
    int deg_a = a.size(); // Degree of a
    while( a[deg_a-1] == 0 ) --deg_a;
    int deg_b = b.size(); // Degree of b
    while( b[deg_b-1] == 0 ) --deg_b;

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
    int digit_sum = 0;
    for( int i = 0; i < (int) c.size(); ++i ) digit_sum += c[ i ];
    return digit_sum;
}

void int2BigInt( int n, BigInt& bn )
{
    bn.clear();
    int m = n;
    while( m > 0 )
    {
        bn.push_back( m % 10 );
        m /= 10;
    }
}

void dump( BigInt& b )
{
    int i = ( b[ b.size()-1 ] == 0 ? b.size()-2 : b.size()-1 );
    for( ; i >= 0; --i ) cout << (int) b[i];
    cout << endl;
}

int main( int argc, char** argv )
{
    int limit = 100;
    if ( argc > 1 ) limit = atoi( argv[ 1 ] );

    int    max_sum = 0;
    int    max_a   = 0;
    int    max_b   = 0;
    BigInt max_prod;
    for( int a = 2; a < limit; ++a )
    {
        if ( a % 10 == 0 ) continue; // Skip multiples of 10
        BigInt big_a;
        int2BigInt( a, big_a );
        BigInt big_a2 = big_a;
        BigInt big_prod;
        
        for( int b = 2; b < limit; ++b )
        {
            int sum = multiply( big_a, big_a2, big_prod );
            //cout << a << "^" << b << "= (" << sum << ")\t";
            //dump( big_prod );
            if ( sum > max_sum )
            {
                max_sum = sum;
                max_a = a;
                max_b = b;
                max_prod = big_prod;
            }
            big_a2.clear();
            big_a2 = big_prod;
        }
    }
    cout << endl << "Answer: " << max_sum << endl;
    cout << "For " << max_a << "^" << max_b << " = ";
    dump( max_prod );
    return 0;
}
