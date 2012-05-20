#include <iostream>
#include <vector>
#include <set>
#include <fstream>

using namespace std;

/***
Let S(A) represent the sum of elements in set A of size n.
We shall call it a special sum set if for any two non-empty disjoint
subsets,
B and C, the following properties are true:

S(B) !=  S(C); that is, sums of subsets cannot be equal.
If B contains more elements than C then S(B) > S(C).
For example, {81, 88, 75, 42, 87, 84, 86, 65} is not a special sum set
because
65 + 87 + 88 = 75 + 81 + 84,
whereas {157, 150, 164, 119, 79, 159, 161, 139, 158} satisfies both
rules
for all possible subset pair combinations and S(A) = 1286.

Using sets.txt (right click and "Save Link/Target As..."), a 4K text
file
with one-hundred sets containing seven to twelve elements
(the two examples given above are the first two sets in the file),
identify all the special sum sets, A1, A2, ..., Ak,
and find the value of S(A1) + S(A2) + ... + S(Ak).
***/

// See Problem 103! Re-use the check functions, simplified.

// Convenient Type Aliases:
typedef unsigned int  uint;
typedef vector<uint>  Set;

// Check that min sum of k+1 elements is bigger than max sum of k elements.
bool check_min_max(const Set& A)
{
    uint min_sum = A[0];
    uint max_sum = 0;

    for(uint k = 1; 2*k < A.size(); ++k) {
        min_sum += A[k];
        max_sum += A[A.size()-k];
        if (min_sum <= max_sum) return false;
    }
    return true;
}

// Calculate sum of subset of A, given by number p in 0..2^n-1 (n bits)
static inline uint sum(const Set& A, uint p = 0)
{
    if (0 == p) p = (1 << A.size())-1;
    uint s = 0;
    uint q = p;
    for(uint j = 0; j < A.size(); ++j, q >>= 1) if (q & 1) s += A[j];
    return s;
}

// Check that there are no equal sums for any 2 subsets of A
bool check_unequal_sums(const Set& A)
{
    uint p2n = 1 << A.size();
    uint max_sum = sum(A);
    Set sums2parts(max_sum+1);
    for(uint s = 0; s <= max_sum; ++s) sums2parts[s] = p2n;

    // For all subsets of A (illustrated by numbers from 1 to 2^n-1):
    for(uint p = 1; p < p2n; ++p) {
        uint  s = sum(A, p);
        uint& parts = sums2parts[s];
        // Equal sums detected
        if (parts < p2n) return false;
        parts = p;
    }
    return true;
}

void dump(const Set& A, bool separated = false)
{
    cout << (separated ? "A = { " : "");
    for(uint i = 0; i < A.size(); ++i) cout << A[i] << (separated ? " " : "");
    cout << (separated ? "}" : "") << endl;
}

// Check whether this is a special set, if special returns sum, else 0
static inline uint is_special( const Set& s )
{
   return((check_min_max(s) && (check_unequal_sums(s))) ? sum(s) : 0);
}

int parseFile( char* filename )
{
   int total = 0;
   ifstream in( filename );
   char c = 0;
   int  n = 0;
   set<int> t_s; // temp set for sorting values
   if ( in ) do {
       if ( ! in.get( c ) ) c = 0;
       if ( ( '\r' == c ) || ( '\n' == c ) || ( 0 == c ) ) {
           if ( n > 0 ) {
               t_s.insert( n );
               Set s;
               for(set<int>::iterator i = t_s.begin(); i != t_s.end(); ++i) {
                   s.push_back(*i);
               }
               n = 0;
               //dump(s, true);
               int tmp = is_special( s );
               //cout << " special sum = " << tmp << endl;
               total += tmp;
               t_s.clear();
           }
       } else if ( ',' == c ) {
           t_s.insert( n );
           n = 0;
       } else if ( ( c >= '0' ) && ( c <= '9' ) ) {
           n *= 10;
           n += c - '0';
       }
   } while( c != 0 );
   return total;
}

int main( int argc, char** argv )
{
   char* filename = (char*) "sets.txt";
   if ( argc > 1 ) filename = argv[ 1 ];
   cout << "Sum of special sets' sum:" << endl;
   cout << "Answer: " << parseFile( filename ) << endl;
   return 0;
}
