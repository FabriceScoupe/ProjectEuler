#include <iostream>
#include <set>
#include <stack>
#include <map>
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

// B != 0, C != 0, B ^ C = 0 => S(B) != S(C)
// card B > card C => S(B) > S(C)
// For given card n, Cn such as card C = n with S(Cn)=max(S(C))
// map n -> max(S(C) / card C = n); max(n)
// map n -> min(S(C) / card C = n); min(n)
// for 1 < n < card A, min(n) > max(n-1)

inline int sum( const set<int>& s )
{
   int sum = 0;
   for( set<int>::iterator i=s.begin(); i!=s.end(); ++i ) sum += *i;
   return sum;
}

void dump( const set<int>& s )
{
   cout << "{ ";
   for( set<int>::iterator i=s.begin(); i!=s.end(); ++i ) cout << *i <<
" ";
   cout << "}";
}

// Generates the set of parts of set s
void get_parts( const set<int>& s, set< set< int > >& parts )
{
   parts.clear();
   set< int > t;    
   parts.insert( t ); // Insert empty set
   int d = 1;
   while( d < s.size() )
   {
       for( set< set< int > >::iterator pit = parts.begin();
            pit != parts.end(); ++pit )
       {
           for( set< int >::iterator sit = s.begin(); sit != s.end();
++sit )
           {
               set< int > u = *pit;
               u.insert( *sit );
               parts.insert( u );
           }
       }
       ++d;
   }
}

// Check whether this is a special set, if special returns sum, else 0
int is_special( const set<int>& s )
{
   // Generate set of parts
   set< set< int > > p;
   get_parts( s, p );
   set< int > e;
   p.erase( p.find( e ) ); // erase empty set
   p.erase( p.find( s ) ); // erase full set
   cout << "size of p = " << p.size() << endl;

   set< int > sums;
   map< int, int > mins;
   map< int, int > maxs;
   for( set< set< int > >::iterator pit = p.begin();
        pit != p.end(); ++pit )
   {
       int tmp = sum( *pit );
       // Checking that all parts have different sums
       if ( sums.find( tmp ) != sums.end() ) return 0;
       sums.insert( tmp );
       int& mn = mins[ pit->size() ];
       if ( ( 0 == mn ) || ( tmp < mn ) ) mn = tmp;
       int& mx = maxs[ pit->size() ];
       if ( tmp > mx ) mx = tmp;
   }
   // Checking 1 < n < card s, min(n) > max(n-1)
   for( int d = 2; d < s.size(); ++d )
   {
       if ( mins[ d ] <= maxs[ d-1 ] ) return 0;
   }
   return sum(s);
}

int parseFile( char* filename )
{
   int total = 0;
   ifstream in( filename );
   char c = 0;
   int  n = 0;
   set< int > s;
   if ( in ) do
   {
       if ( ! in.get( c ) ) c = 0;
       if ( ( '\r' == c ) || ( '\n' == c ) || ( 0 == c ) )
       {
           if ( n > 0 )
           {
               s.insert( n );
               n = 0;
               dump( s );
               int tmp = is_special( s );
               cout << " special sum = " << tmp << endl;
               total += tmp;
               s.clear();
           }
       }
       else if ( ',' == c )
       {
           s.insert( n );
           n = 0;
       }
       else if ( ( c >= '0' ) && ( c <= '9' ) )
       {
           n *= 10;
           n += c - '0';
       }
   }
   while( c != 0 );
   return total;
}

int main( int argc, char** argv )
{
   char* filename = (char*) "sets.txt";
   if ( argc > 1 ) filename = argv[ 1 ];
   cout << "Sum of special sets' sum = " << parseFile( filename ) <<
endl;
}
