#include <iostream>
using namespace std;

// Discover all fractions with an unorthodox cancelling method.

// possible cases: 
// 1) (10a+b)/(10c+b) = a/c => 10ac+bc=10ac+ab => a = c but a < c so no.
// 2) (10b+a)/(10c+b) = a/c => 10bc+ac=10ac+ab => 10bc = a(9c+b)
// 3) (10b+a)/(10b+c) = a/c => 10bc+ac=10ab+ac => a = c impossible.
// 4) (10a+b)/(10b+c) = a/c => 10ac+bc=10ab+ac => c(9a+b)=10ab

int main( int argc, char** argv )
{
    int prod1 = 1;
    int prod2 = 1;

    for( int a = 1; a <= 9; ++a )
    {
        for( int b = 1; b <= 9; ++b )
        {
            for( int c = a+1; c <= 9; ++c ) // a < c
            {
                if( 10*b*c == a*(9*c+b) )
                {
                    cout << b << a << "/" << c << b << " = " 
                         << a << "/" << c << endl;
                    prod1 *= a;
                    prod2 *= c;
                }
                else if ( 10*a*b == c*(9*a+b) )
                {
                    cout << a << b << "/" << b << c << " = "
                         << a << "/" << c << endl;
                    prod1 *= a;
                    prod2 *= c;
                }
            }
        }
    }

    for( char d = 2; d <= 9; ++d )
    {
        while( ( 0 == ( prod1 % d ) ) && ( 0 == ( prod2 % d ) ) )
        {
            prod1 /= d;
            prod2 /= d;
        }
    }
    cout << "Product is " << prod1 << "/" << prod2 << endl;
}
