#include <iostream>
#include <cstdlib>
#include <vector>
using namespace std;

// First term in Fibonacci sequence to contain 1000 digits?
// ( n > 2 ) Fn = Fn-1 + Fn-2
// F1 = F2 = 1;

// Let's not be subtle...
typedef vector<char> BigInt;

void add( BigInt&a, BigInt& b, BigInt& c )
{
    c.clear();
    char carry = 0;
    for( int pos = 0; ( pos < a.size() ) || ( pos < b.size() ); ++pos )
    {
        char sum = ( pos < a.size() ? a[pos] : 0 ) +
                   ( pos < b.size() ? b[pos] : 0 ) +
                   carry;
        carry = sum / 10;
        c.push_back( sum % 10 );
    }
    if ( carry > 0 ) c.push_back( carry );
}

void dump( BigInt& a )
{
    int pos = a.size()-1;
    while( ( a[pos]==0 ) && ( pos > 0 ) ) --pos;
    while( pos >= 0 )
    {
        //cout << (int) a[pos];
        --pos;
    }
}

// First term in Fibonacci sequence to contain 1000 digits?
// ( n > 2 ) Fn = Fn-1 + Fn-2
// F1 = F2 = 1;
int main( int argc, char** argv )
{
    int n = 1000;
    if ( argc > 1 ) n = atoi( argv[1] );
    BigInt a,b,c;
    a.push_back(1);
    b.push_back(1);
    BigInt* f1 = &a;
    BigInt* f2 = &b;
    BigInt* f3 = &c;
    int idx = 2;
    do
    {
        ++idx;
        add( *f1, *f2, *f3 );
        //cout << idx << " term = ";
        //dump( *f3 );
        //cout << " " << f3->size() << " digits." << endl;
        // Rotate pointers
        BigInt* tmp = f1; f1 = f2; f2 = f3; f3 = tmp;
    } while( f2->size() < n );
    cout << "Index: " << idx << endl;
}
