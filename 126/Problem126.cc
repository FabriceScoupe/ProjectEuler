#include <iostream>
#include <cstdlib>

using namespace std;

/*
 * The minimum number of cubes to cover every visible face on a cuboid
 * measuring 3 x 2 x 1 is 22.
 *
 * If we add a second layer to this solid it would require 46 cubes to 
 * cover every visible face, the third layer would require 76 cubes, and the
 * fourth layer would require one hundred and eighteen cubes to cover every
 * visible face.
 *
 * However, the first layer on a cuboid measuring 5 x 1 x 1 also requires 22
 * cubes; similarly the first layer on cuboids measuring 5 x 3 x 1, 7 x 2 x 1,
 * and 11 x 1 x 1 all contain 46 cubes.
 *
 * We shall define C(n) to represent the number of cuboids that contain n
 * cubes in one of its layers.
 * So C(22)=2, C(46)=4, C(78)=5 and C(118)=8.
 * It turns out that 154 is the least value of n for which C(n)=10.
 * Find the least value of n for which C(n)=1000.
 */

// Cuboid (a,b,c) (West-East/South-North/Down-Up)
// First layer nl(1) = 2(ab + bc + ca)
// Second layer nl(2) =
// Continued "propagation" yields nl(1) more cubes => + nl(1);
// + 12 "edges" (4 times the 3 different types) = 4(a + b + c)
// Hypothesis quadratic form: nl(l, a, b, c) = A.l^2+B.l+C
// nl(1,a,b,c) = 2(ab+bc+ca) = A + B + C
// nl(2,a,b,c) = nl(1,a,b,c)+4(a+b+c) = 4A + 2B + C
// 3A + B = 4(a+b+c);
// Next propagation: 
// nl(3,a,b,c) = nl(1,a,b,c) (continued "propagation" outward)
//             + 8*(a+b+c) (2 x "edges")
//             + 8 "vertices"
//             = nl(2,a,b,c) + 4(a+b+c)+8
//             = 9A + 3B + C
// 5A + B = 4(a+b+c)+8
//
// 2A = 8 => A = 4
// B = 4(a+b+c)-12
// C = 2(ab+bc+ca) - 4 - 4(a+b+c) + 12 = 2(ab+bc+ca)-4(a+b+c)+8
//
// nl(l,a,b,c) = 4.l^2+4(a+b+c-3).l+2(ab+bc+ca)-4(a+b+c)+8
// Or, considering s = a+b+c and p = ab+bc+ca:
// nl(l,s,p) = 4.l^2 + 4(s-3).l + 2p-4s+8
//
// Looking for number of tuples (l,a,b,c) such as:
// nl(l,a,b,c) = n => that number is C(n).
// n odd => C(n) = 0, so only consider even numbers
//
// nl(0,a,b,c) = 2(ab+bc+ca)-4(a+b+c)+8
// nl(l+1,a,b,c) = nl(l,a,b,c)+4+8l+4(a+b+c-3)
//               = nl(l,a,b,c)+4(2l+a+b+c-2)
// 

int nl(int l, int a, int b, int c) {
    int s = a+b+c;
    int p = a*b+b*c+c*a;
    return(4*l*l+4*(s-3)*l+2*p-4*s+8);
}

int main(int argc, char* argv[])
{
    // Assuming that n is <= 20000, must consider all cubes up to ~5000(^3).

    int dim_max = 5000;
    if (argc > 1) dim_max = atoi(argv[1]);
    int ncubs_max = 20000;
    if (argc > 2) ncubs_max = atoi(argv[2]);
    int limit = 1000;
    if (argc > 3) limit = atoi(argv[3]);

    cout << "nl(1,1,2,3) = " << nl(1,1,2,3) << endl;
    cout << "nl(2,1,2,3) = " << nl(2,1,2,3) << endl;
    cout << "nl(3,1,2,3) = " << nl(3,1,2,3) << endl;
    cout << "nl(4,1,2,3) = " << nl(4,1,2,3) << endl;
    cout << "nl(1,1,1,5) = " << nl(1,1,1,5) << endl;
    cout << "nl(1,1,3,5) = " << nl(1,1,3,5) << endl;
    cout << "nl(1,1,2,7) = " << nl(1,1,2,7) << endl;
    cout << "nl(1,1,1,11) = " << nl(1,1,1,11) << endl;

    int* ncubs = new int [ncubs_max / 2]; // Only even values possible

    for(int a = 1; a <= dim_max; ++a) {
        cout << '.'; flush(cout);
        for(int b = a; b <= dim_max; ++b) {
            //cout << 'b'; flush(cout);
            for(int c = b; c <= dim_max; ++c) {
                //cout << 'c'; flush(cout);
                int s = a+b+c;
                int p = a*b+b*c+c*a;
                int l = 0;
                int nl = 2*p-4*s+8;
                do {
                    //cout << 'l'; flush(cout);
                    nl += 4*(2*l+s-2);
                    ++l;
                    if (nl < (ncubs_max)) ++ncubs[nl/2];
                } while(nl < ncubs_max);
            }
        }
    }
    cout << endl;

    for(int i = 0; i < (ncubs_max / 2); ++i) {
        if (limit == ncubs[i]) {
            cout << "C(" << i*2 << ") = " << ncubs[i] << endl;
            break;
        }
    }
    return 0;
}
