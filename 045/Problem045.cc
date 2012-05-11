#include <iostream>
using namespace std;

// After 40755, what is the next triangle number that is also
// pentagonal and hexagonal?
// T(n)=n(n+1)/2 P(n)=n(3n-1)/2 H(n)= n(2n-1)

// T(a)=P(b)=H(c) <=> a(a+1)/2 = b(3b-1)/2 = c(2c-1)
// Recursions: T(n+1)=T(n)+n+1 P(n+1)=P(n)+3n+1 H(n+1)=H(n)+4n+1

int main( int argc, char** argv )
{
    int a = 0;
    long long t = 0;
    int b = 0;
    long long p = 0;
    int c = 0;
    long long h = 0;
    long long target = 40755;
    bool found = false;
    while( ! found )
    {
        while( h < target ) { h += 4*c+1; ++c; }
        while( t < target ) { t += a+1; ++a; }
        while( p < target ) { p += 3*b+1; ++b; }
        cout << "h = "<<h<<" p = "<<p<<" t = "<<t<<endl;
        if ( ( p == target ) && ( t == target ) )
        {
            cout << "T("<<a<<")=P("<<b<<")=T("<<c<<")=" << h << endl;
            found = ( h > 40755 );
        }
        target += 4*c+1;
    }
}
