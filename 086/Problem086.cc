#include <iostream>
#include <cstdlib>

using namespace std;

/*
 * Project Euler: Problem 086 (http://projecteuler.net/problem=86)
 */

// A spider, S, sits in one corner of a cuboid room, measuring 6 by 5 by 3,
// and a fly, F, sits in the opposite corner. By travelling on the surfaces of
// the room the shortest "straight line" distance from S to F is 10 and the
// path is shown on the diagram.
// However, there are up to three "shortest" path candidates for any given
// cuboid and the shortest route is not always integer.
// By considering all cuboid rooms with integer dimensions, up to a maximum
// size of M by M by M, there are exactly 2060 cuboids for which the shortest
// distance is integer when M=100, and this is the least value of M for which
// the number of solutions first exceeds two thousand;
// the number of solutions is 1975 when M=99.
// Find the least value of M such that the number of solutions first exceeds
// one million.

// "Unfold" the cuboid AxBxC ( A<=B<=C )
// Possible path lengths (squares):
// (A+B)^2 + C^2 = A^2 + B^2 + C^2 + 2 AB
// (A+C)^2 + B^2 = A^2 + B^2 + C^2 + 2 AC
// (B+C)^2 + A^2 = A^2 + B^2 + C^2 + 2 BC
// AB <= AC and AB <= BC so shortest is (A+B)^2 + C^2
// if (A+B)^2 + C^2 is a perfect square => bingo, count it.
//
// Knowing count(M), what is count(M+1) ?
// Reset to A = 1; B = 1; C = M+1;
// Increment B and "range" A from 1 to B, until B = M+1.
// Add found delta count to count(M).
//
// Min A = 1; B = 1; C = M; Max A=B=C=M
// Min path: C^2 + 2 Max path 5*C^2
// How many perfect squares S such as C^2 + 2 <= S <= 5*C^2 ?

int main( int argc, char** argv )
{
    unsigned int limit = 1000000;
    if ( argc > 1 ) limit = (unsigned int) atoi( argv[ 1 ] );

    unsigned int count = 0;
    unsigned int c = 1;

    while(count <= limit) {
        unsigned long c2 = c*c;
        for(unsigned int b = 1; b <= c; ++b) {
            unsigned int  r = c;
            for(unsigned long ab = b+1; ab <= 2*b; ++ab) {
                unsigned long l = (ab)*(ab) + c2;
                unsigned long r2 = r*r;
                while(r2 < l) {
                    r2 += 2*r+1;
                    ++r;
                }
                if (r2 == l) ++count;
            }
        }
        cout << '.'; flush(cout);
        //cout << "count(" << c << ") = " << count << endl;
        ++c;
    }
    cout << endl << "Answer: " << c-1 << endl;
    return 0;
}
