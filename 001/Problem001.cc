#include <iostream>
#include <cstdlib>

using namespace std;

// Closed form
int getSum1( int a, int b, int n )
{
    int max_a  = n / a - ( n % a ? 0 : 1 );
    int max_b  = n / b - ( n % b ? 0 : 1 );
    int max_ab = n / (a*b) - ( n % (a*b) ? 0 : 1 );
    int sum =   (max_a*(max_a+1)/2)* a         // + Sum of multiples of a
              + (max_b*(max_b+1)/2)* b         // + Sum of multiples of b
              - (max_ab*(max_ab+1)/2)* a * b;  // - Sum of multiples of a*b
    return sum;
}

// Brute force
int getSum2( int a, int b, int n )
{
    int sum = 0;
    for( int i = 1; i < n; ++i )
    {
        sum += ( ( i % a == 0 ) || ( i % b == 0 ) ? i : 0 );
    }
    return sum;
}


int main( int argc, char** argv )
{
    int n = 1000;
    if ( argc > 1 ) n = atoi( argv[1] );
    if ( n < 10 ) n = 10;

    cout << "Calculating sum of all multiples of 3 or 5 < " << n << endl;
    cout << endl << "Sum1 = " << getSum1(3,5,n) << endl;
    cout << endl << "Sum2 = " << getSum2(3,5,n) << endl;

    return 0;
}
