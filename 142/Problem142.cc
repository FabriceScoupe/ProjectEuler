#include <iostream>
#include <set>
#include <map>
using namespace std;

typedef unsigned long long ull;

/*
 * Project Euler: Problem 142 (http://projecteuler.net/problem=142)
 */

// x > y > z > 0
// x+y, x-y, x+z, x-z, y+z, y-z all perfect squares.
// Smallest (x+y+z) ?

// x+y > x+z > y+z
// x+y = f^2; x+z = e^2; y+z=d^2 => f > e > d
// x-y < x-z > y-z ; x-z = (x-y)+(y-z)
// x-y = a^2; y-z = b^2; x-z = c^2
// a < c > b 
//
// x-z = x-y + y-z => c^2 = a^2 + b^2 => (a,b,c) pythagorean triple.
// Generating Pythagorean triples?
// https://en.wikipedia.org/wiki/Formulas_for_generating_Pythagorean_triples
//  = u^2+2uv, b = 2v^2+2uv, c=u^2+2v^2+2uv (u,v >= 1)
//
// z, y = z+(y-z), x = z+(y-z)+(x-y) 
// z, y = z+b^2, x = z+b^2+a^2=z+c^2
// y+z=2z+b^2=d^2
// x+z=2z+c^2=e^2
// x+y=2z+b^2+c^2 = f^2
//
// (x+y)=f^2=x+z+y-z=e^2+b^2 => (b, e, f) another Pythagorean triple
// (x+z)=e^2=x-y+y+z=a^2+d^2 => (a, d, e) another Pythagorean triple
// (y+z)=d^2=y+x-x+z=f^2-c^2
// => f^2 = c^2+d^2 => and yet another triple (c, d, f)
// a < c and b < c
// d < e < f
// (a,b,c), (a, d, e), (b, e, f) and (d, c, f) pythagorean triples
// 2z = d^2-b^2 = e^2 - c^2 = f^2 - b^2 - c^2
// d > b, e > c, (d*d-b*b)=(e*e-c*c)
// x+y+z = 3*(d*d-b*b)/2+b*b+c*c

static set<pair<ull, ull> > triples;
static map<ull, set<ull> > int2triples;

// Check pythagorean triple (a,b,c)
// Try and find (a,d,e) such than (b,e,f) and (c,d,f) are triple.
// 2z = d^2-b^2 = e^2 - c^2 = f^2 - b^2 - c^2 (d > b, e > c)
ull check_triple(ull a2, ull b2) {
    set<ull>::iterator it;
    ull best_sum = 0;
    ull c2 = a2 + b2;
    for(it = int2triples[a2].begin(); it != int2triples[a2].end(); ++it) {
        ull d2 = *it;
        ull e2 = a2+b2;
        if ((d2 <= b2)||(e2 <= c2)) continue;
        if (((e2-c2) != (d2-b2))||((d2-b2) % 2 != 0)) continue;
        if ((triples.find(pair<ull,ull>(b2,e2)) == triples.end()) &&
            (triples.find(pair<ull,ull>(e2,b2)) == triples.end())) continue;
        ull f2 = b2+e2;
        if ((triples.find(pair<ull,ull>(c2,d2)) == triples.end()) &&
            (triples.find(pair<ull,ull>(d2,c2)) == triples.end())) continue;
        ull g2 = c2+e2;
        if (g2 != f2) continue;
        cout << "a2 = "<<a2<<" b2 = "<<b2<<" c2 = "<<c2<<endl;
        cout << "\ta2 = " <<a2<<" d2 = "<<d2<<" e2 = "<<e2<<endl;
        cout << "\t\tb2 = " << b2 << " e2 = " << e2 << " f2 = " << f2 << endl;
        cout << "\t\t\tc2 = " << c2 <<" d2 = " << e2 <<" g2 = " << g2 << endl;
        ull z = (d2-b2)/2;
        ull y = z + b2;
        ull x = y + a2;
        if ((0 == best_sum) || (x+y+z < best_sum)) {
            best_sum = x+y+z;
            cout << x <<" + "<< y <<" + "<< z <<" = "<< best_sum << endl;
        }
    }
    return best_sum;
}

int main(int argc, char* argv[])
{
    ull best_sum = 0;

    cout << "Generating pythagoreans triples" << endl;
    for(ull n = 1; n <= 1000; ++n) {
        cout << '.'; flush(cout);
        for(ull m = n+1; m <= 1000; ++m) {
            for(int k = 1; k <= 10; ++k) {
                ull s1 = k*m*m-n*n;
                ull s2 = k*2*m*n;
                triples.insert(pair<ull,ull>(s1*s1, s2*s2));
                int2triples[s1*s1].insert(s2*s2);
                int2triples[s2*s2].insert(s1*s1);
            }
        }
    }
    cout << endl << "Number of triples = " << triples.size() << endl;

    for(set<pair<ull,ull> >::iterator it1 = triples.begin(); 
        it1 != triples.end(); ++it1)
    {
        ull sum1 = check_triple(it1->first, it1->second);
        ull sum2 = check_triple(it1->second, it1->first);
        if ((0 == best_sum) || ((sum1 > 0) && (sum1 < best_sum))) {
             best_sum = sum1;
        }
        if ((0 == best_sum) || ((sum2 > 0) && (sum2 < best_sum))) {
             best_sum = sum2;
        }
    }

    cout << "Answer: " << best_sum << endl;
    return 0;
}
