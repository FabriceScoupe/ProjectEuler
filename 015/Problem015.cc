#include <iostream>
#include <cstdlib>
using namespace std;

// Number of top-left to bottom-right routes in a 20x20 grid
// (0,0) to (20,20)
// No backtracking: at each node, increment is (0,1) or (1,0)
// 40 increments necessary from (0,0) to (20,20).
// There must be 20 "right" increments and 20 "down" increments.
// Number of routes = number of ways to order those increments,
// ignoring permutations of identical increments:
// 40! / (20! * 20!).
//
// For 2x2 grid: 4!/(2!x2!) = 6 ways.
// General formula: NxN grid -> NRoutes(N) = (2N)! / (N! * N!)
// = Prod[k=1..N](N+k)/Prod[k=1..N](k)
// = 2N/N*(2N-1)*(2N-2)/(N-1)*...*(N+2)/2*(N+1)

long long numberRoutes( int grid_N )
{
    long long result = 1;
    int divisor = 1;
    for( int i = 1; i <= grid_N; ++i )
    {
        result *= (i+grid_N);
        divisor *= i;
        if ( result % divisor == 0 )
        {
            result /= divisor;
            divisor = 1;
        }
    }
    return result;
}

int main( int argc, char** argv )
{
    int n = 20;
    if ( argc > 1 ) n = atoi( argv[1] );
    cout << "Number of top-left to bottom-right routes in a " 
         << n << " x " << n << " grid = " << numberRoutes( n ) << endl;
}
