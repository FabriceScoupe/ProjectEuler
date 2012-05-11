#include <iostream>
#include <cstdlib>
using namespace std;

// Difference between sum(i=1 to i=n) of square(i) and
//                    square( sum(i=1 to i=n) of i.
//
// sum(i=0 to n) of i = n*(n+1)/2, square n*n*(n+1)*(n+1)/4
//
// sum(i=0 to n) of i*i = a*n^3 + b*n^2 + c*n + d = SumSq(n)
// SumSq(0) = 0 => d = 0 => SumSq(n) = (an^2+bn+c)n
// SumSq(1) = 1 => a+b+c = 1
// SumSq(2) = 5 => 4a+2b+c = 5/2 => 3a + b = 3/2
// SumSq(3) = 14 => 9a+3b+c = 14/3 => c = 14/3 - 9/2 = 1/6 => a + b = 5/6
// => 2a = 3/2 - 5/6 = 2/3 => a = 1/3 => b = 1/2
// SumSq(n) = n * ( n^2/3 + n/2 + 1/6) = 1/6*n*(2n^2+3n+1)
//          = (2n+1)*(n+1)*n/6
//
// Diff = n^2*(n+1)^2/4 - n*(n+1)*(2n+1)/6
//      = 1/12*n*(n+1)*( 3*n*(n+1) - 2*(2n+1) )
//      = 1/12*n*(n+1)*(n-1)*(3n+2)

int sumSquare( int n )
{
    return( ( n * (n+1) * (2*n+1) / 6 ) );
}

int squareSum( int n )
{
   int s = ( n * ( n + 1 ) ) / 2;
   return ( s * s );
}

int diff( int n )
{
   return( ( n * (n+1) * (n-1) * (3*n+2) ) / 12 );
}

int main( int argc, char** argv )
{
    int n = 100;
    if ( argc > 1 ) n = atoi( argv[1] );
    int sumSq = sumSquare( n );
    int sqSum = squareSum( n );
    cout << sqSum << " - " << sumSq << " = " << sqSum - sumSq
         << " = " << diff( n ) << endl;
}
