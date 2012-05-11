#include <iostream>
#include <set>
using namespace std;

// Find the first four consecutive integers to have four distinct
// prime factors.
// E.g. 14 = 2 x 7 15 = 3 x 5 (two consecutive integers to have
// two distinct prime factors).

// n, n+1, n+2, n+3 : 2 are even, 1 is a multiple of 3, 1 is a multiple of 4
// Smaller integer with 4 distinct prime factor 2x3x5x7=210

void decompose( long long n, set<long long>& sd )
{
    sd.clear();
    cout << n << "= ";
    int d = 2;
    long long m = n;
    int v = 1;
    while( m > 1 )
    {
        while( m % d == 0 )
        {
            v *= d;
            m /= d;
        }
        if ( v > 1 )
        {
            sd.insert(v);
            cout << v << "\t";
        }
        v = 1;
        ++d;
    }
    cout << endl;
}

bool addDistinctSets( set<long long>& src, set<long long>& tgt )
{
    bool ok = true;
    for( set<long long>::iterator i = src.begin(); i != src.end(); ++i )
    {
        if ( tgt.find( *i ) != tgt.end() )
        {
            ok = false;
            break;
        }
        else
        {
            tgt.insert( *i );
        }
    }
}


int main( int argc, char** argv )
{
    // Not particularly fast...
    int n[5];
    set<long long> sd[5];
    char count = 1;
    n[1]=210;
    bool shiftAgain = false;
    while( count < 5 )
    {
        decompose( n[count], sd[count] );
        if ( 4 == sd[ count ].size() )
        {
             if ( (!shiftAgain) && addDistinctSets( sd[ count ], sd[ 0 ] ) )
             {
                 if ( count < 4 ) n[count+1] = n[count]+1;
                 ++count;
             }
             else
             {
                 sd[0].clear();
                 shiftAgain = false;
                 // Move everything one step to the left
                 // n[1<-2] n[2<-3] n[3<-4] n[4] new number
                 for( int i = 1; i < count; ++i )
                 {
                     n[i]  = n[i+1];
                     sd[i] = sd[i+1];
                     shiftAgain |= (!addDistinctSets( sd[i], sd[0] ));
                 }
                 ++n[count];
             }
        }
        else
        {
            n[1] = n[count]+1;
            count = 1;
            sd[0].clear();
        }
    }
    cout << endl << "-----" << endl;
    for( int i = 1; i <= 4; ++i )
    {
        cout << n[i] << ": ";
        for( set<long long>::iterator it=sd[i].begin(); it!=sd[i].end(); ++it )
        {
            cout << *it << " ";
        }
        cout << endl;
    }
}
