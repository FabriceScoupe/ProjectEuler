#include <iostream>
#include <cstdlib>

using namespace std;

/*
 * Project Euler: Problem 100 (http://projecteuler.net/problem=100)
 */

/***
If a box contains twenty-one coloured discs, composed of fifteen blue discs
and six red discs, and two discs were taken at random, it can be seen that
the probability of taking two blue discs, P(BB) = (15/21)×(14/20) = 1/2.

The next such arrangement, for which there is exactly 50% chance of taking
two blue discs at random, is a box containing eighty-five blue discs and
thirty-five red discs.

By finding the first arrangement to contain over 10^(12) = 1,000,000,000,000
discs in total, determine the number of blue discs that the box would contain.
***/

// N = B + R
// P(BB) = (B/N).((B-1)/(N-1)) = 1/2
// B.(B-1) = N.(N-1)/2 = T(N-1) (triangular number)
// 2.T(B-1) = T(N-1)
// Ex: T(2)=3 T(3)=6 => B=3 N=4 P(BB)=3/4.2/3=1/2
// 
// Looking up triangular numbers (& square ones) in Wikipedia and Wolfram.
// saw a method to get to "Pell's Equation", try something similar here:
// 4B(B-1)=(2B-1)^2-1
// 8B(B-1)=4N(N-1) <=> 2(2B-1)^2-2 = (2N-1)^2 - 1
// (2N-1)^2 - 2(2B-1)^2 = -1
// x = 2N-1 and y = 2B-1
// x^2 - 2 y^2 = -1 (Pell-like equation!)
// Solution will be linked to the continuous fraction of 2, see problem 57.
// Expansions of continuous fraction of 2:
// (1,1): 1 - 2 = -1 => yes
// x = 1 => N = 1, y = 1 => B = 1 invalid since B < N, but fundamental sol.
// (3,2): 3^2 - 2.2^2 = 1 => no
// (7,5): 49 - 2.25 = -1 => yes!
// x = 7 => N = 4 y = 5 => B = 3 => case seen above
// Fundamental solution is (1,1).
// See Wolfram (http://mathworld.wolfram.com/PellEquation.html) for the
// recursion used below.
// x0 = 7 y0 = 5

void next( long long& x, long long& y )
{
    long long xx = x + 2*y;
    long long yy = y + x;
    x = xx;
    y = yy;
}

int main( int argc, char** argv )
{
    long long min = 1000000000000LL;
    if ( argc > 1 ) min = atoll( argv[ 1 ] );
    long long x = 1;
    long long y = 1;
    do
    {
        next(x,y); // solution for x^2-2y^2=1, so ignore
        next(x,y); // solution for x^2-2y^2=-1, that's the one!
        cout << "B = " << ( y + 1 ) / 2 << " N = " << ( x + 1 ) / 2 << endl;
    }
    while( ( x + 1 ) / 2 <= min );
    cout << "Answer: " << (y + 1) / 2;
    return 0;
}
