#include <iostream>
#include <cstdlib>
#include <set>
#include <map>
#include <vector>
using namespace std;

/*
 * Project Euler: Problem 061 (http://projecteuler.net/problem=61)
 */

// Triangle, square, pentagonal, hexagonal, heptagonal and octagonal
// numbers are all figurate (polygonal) numbers and are generated by the
// following formulae:
// P(3,n) = n.(n+1)/2
// P(4,n) = n^2
// P(5,n) = n(3n-1)/2
// P(6,n) = n(2n-1)
// P(7,n) = n(5n-3)/2
// P(8,n) = n(3n-2)
// The ordered set of three 4-digit numbers: 8128,2882,8281 has interesting
// properties:
// 1/ The set is cyclic, in that the last two digits of each number is the
//    first two digits of the next number (including last and first);
// 2/ Each polygonal type: triangle (P3,127=8128), square (P4,91)=8281 and
//    pentagonal (P5,44=2882) is represented by a different number in the
//    set;
// 3/ This is the only 4-digit number set with this property.
//
// Find the sum of the only ordered set of six cyclic 4-digit numbers for 
// which each polygonal type (ie triangle, square, pentagonal, hexagonal,
// heptagonal and octagonal) is represented by a different number in the
// set.

// Generate sets of 4-digit numbers, look for cycles

int main( int argc, char** argv )
{
    const char* names[] = { "triangle", "square", "pentagonal",
        "hexagonal", "heptagonal", "octogonal" };

    map<int, int> m;

    // Build prefixes and suffixes maps
    int p = 0;
    for( int n = 10; p < 10000; ++n )
    {
        p = n*(3*n-2); if ((p>=1000)&&(p<10000)) m[ p ] = 5;
        p = (n*(5*n-3))/2; if ((p>=1000)&&(p<10000)) m[ p ] = 4;
        p = n*(2*n-1); if ((p>=1000)&&(p<10000)) m[ p ] = 3;
        p = (n*(3*n-1))/2; if ((p>=1000)&&(p<10000)) m[ p ] = 2;
        p = n*n; if ((p>=1000)&&(p<10000)) m[ p ] = 1;
        p = (n*(n+1))/2; if ((p>=1000)&&(p<10000)) m[ p ] = 0;
    }

    unsigned char busy = 0;
    map<int,int>::iterator n[6];
    int prev, curr;
    char flag = 0;
    for( n[0]=m.begin(); n[0]!=m.end(); ++n[0] )
    {
        busy = 1<<(n[0]->second);
        for( n[1]=m.begin(); n[1]!=m.end(); ++n[1] )
        {
            flag = 1<<(n[1]->second);
            prev = (n[0]->first)%100;
            curr = (n[1]->first)/100;
            if((!(busy&flag))&&(curr==prev))
            {
                busy |= 1 << (n[1]->second);
                for( n[2]=m.begin(); n[2]!=m.end(); ++n[2] )
                {
                    flag = 1<<(n[2]->second);
                    prev = (n[1]->first)%100;
                    curr = (n[2]->first)/100;
                    if((!(busy&flag))&&(curr==prev))
                    {
                        busy |= 1 << (n[2]->second);
                        for( n[3]=m.begin(); n[3]!=m.end(); ++n[3] )
                        {
                            flag = 1 << (n[3]->second);
                            prev = (n[2]->first)%100;
                            curr = (n[3]->first)/100;
                            if ((!(busy&flag))&&(curr==prev))
                            {
                                busy |= 1<<(n[3]->second);
                                for( n[4]=m.begin(); n[4]!=m.end(); ++n[4] )
                                {
                                    flag = 1<<(n[4]->second);
                                    prev = (n[3]->first)%100;
                                    curr = (n[4]->first)/100;
                                    if((!(busy&flag))&&(curr==prev))
                                    {
                                        busy |= 1<<(n[4]->second);
                                        for(n[5]=m.begin();
                                            n[5]!=m.end();++n[5])
                                        {
                                            if ((((n[5]->first)/100) ==
                                                 ((n[4]->first)%100)) &&
                                                (((n[5]->first)%100) ==
                                                 ((n[0]->first)/100)))
                                            {
                                                // found!
                                                int sum = 0;
                                                for( int i = 0; i < 6; ++i )
                                                {
                                                    flag = n[i]->second;
                                                    curr = n[i]->first;
                                                    cout << names[(int)flag];
                                                    cout << " " << curr << " ";
                                                    sum += curr;
                                                }
                                                cout << endl;
                                                cout << "Answer: "<<sum<<endl;
                                                return 0;
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return 1; /* Should not get to this point */
}
