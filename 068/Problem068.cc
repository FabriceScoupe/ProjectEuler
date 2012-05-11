#include <iostream>
#include <vector>
using namespace std;

// [...] Using the numbers 1 to 10 and depending on arrangements, it is
// possible to form 16- and 17-digit strings.
// What is the maximum 16-digit string for a "magic" 5-gon ring?
// (maximum string for 3-gon is 432621513.

// 10 positions (1 to 10). 1 to 5 -> ring, 6 to 10 outside
// Graph: 10 vertices, 10 edges:
// 1-2, 2-3, 3-4, 4-5, 5-1 (ring)
// 1-6, 2-7, 3-8, 4-9, 5-10 ("star" links)
// Sums: (6,1,2), (7,2,3), (8,3,4), (9,4,5), (10,5,1)
// Ring positions appear twice, star ones only once
// Sum of sums = a6+a7+a8+a9+a10+ 2*(a1+a2+a3+a4+a5)
// Min = 6+7+8+9+10+2*(1+2+3+4+5)=40+2*15=70=5*14
// Max = 1+2+3+4+5+2*(6+7+8+9+10)=15+2*40=95=5*19
// So magic sum between 14 and 19.

// Not subtle at all: lexicographic permutations of 0123456789,
// Check if solution, if yes get string, then check max!
// 10! = 3628800 permutations to check.

void swap( char& a, char& b )
{
    //cout << "Swapping " << (int) a << " and " << (int) b << endl;
    char tmp = a; a = b; b = tmp;
}

// Reversing set
void reverse( char* set, int length )
{
    for( int i = 0; 2*i < length; ++i ) swap( set[i], set[ length -1 - i ] );
}

// Get next permutation in set, or return false if last one reached.
bool next_perm( char* set, int dim )
{
    bool ok = false;
    if ( dim > 2 )
    {
        ok = next_perm( set + 1, dim - 1 );
        if ( ! ok )
        {
             // No next perm for set + 1 => set + 1 "reverse" ordered
             // Try and find smallest elem in set+1 greater than set[0]
             int pos = dim-1;
             while( ( pos > 0 ) && ( set[0] > set[pos] ) ) --pos;
             if ( pos > 0 )
             {
                 swap( set[0], set[pos] );
                 // reverse order of set+1
                 reverse( set+1, dim-1 );
                 ok = true;
             }
        }
    }
    else if ( 2 == dim )
    {
        ok = ( set[ 1 ] > set[ 0 ] );
        if ( ok ) swap( set[ 1 ], set[ 0 ] );
    }
    return ok;
}

int main( int argc, char** argv )
{
    char data[10];
    for( int i = 0; i < 10; ++i ) data[ i ] = i+1;
    long long max_s = 0;
    vector<char> selems;
    // Sums: (6,1,2), (7,2,3), (8,3,4), (9,4,5), (10,5,1)
    do
    {
        char s[5];
        for( int i = 0; i < 5; ++i )
        {
            s[i] = data[5+i] + data[i] + data[(i+1)%5];
        }
        if ((s[0]==s[1])&&(s[2]==s[3])&&(s[4]==s[0])&&(s[1]==s[2]))
        {
            // Solution found!
            char m = 7;
            int shift = 0;
            for( int i = 0; i < 5; ++i )
            {
                if (data[i+5] < m)
                {
                    m = data[i+5];
                    shift = i;
                }
            }
            cout << (int) s[0] << " : ";
            selems.clear();
            for( int i = 0; i < 5; ++i )
            {
                cout << "(" << (int) data[5+((i+shift)%5)] << ", "
                     << (int) data[(i+shift)%5] << ", "
                     << (int) data[(i+1+shift)%5] << ") ";
                selems.push_back( data[5+((i+shift)%5)] );
                selems.push_back( data[(i+shift)%5 ] );
                selems.push_back( data[(i+1+shift)%5 ] );
            }
            long long str = 0;
            for( int i = 0; i < selems.size(); ++i )
            {
                str *= 10;
                if ( selems[i] == 10 )
                {
                    str = (str+1)*10;
                }
                else
                {
                    str += selems[i];
                }
            }
            cout << "  " << str << endl;
            if ( ( str < 10000000000000000LL )&&( str > max_s ) ) max_s = str;
        }
    }
    while( next_perm( data, 10 ));
    cout << endl << "Maximum 16-digit string = " << max_s << endl;
}
