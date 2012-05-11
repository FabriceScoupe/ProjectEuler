#include <iostream>
#include <vector>
#include <fstream>
#include <map>
#include <set>

using namespace std;

/***
Removing links in graph to achieve maximum savings while keeping
all vertices connected.
***/

// Graph is not oriented: matrix is symetric, diagonal is 0
// so n by n matrix can be simply stored as n*(n-1)/2 elements.
// But here graph is small enough so keep matrix.
// Only consider A(i,j) with j > i (zeroes on diag anyway)

// Minimum Spanning Tree, Greedy Algorithm.


void uploadMatrix( char* filename, vector< int >& m )
{
    m.clear();
    ifstream in( filename );
    char c = 0;
    int  n = -1;
    if ( in ) do 
    {
        if ( ! in.get( c ) ) c = 0;
        if ( '-' == c ) c = '0';
        if ( ( ',' == c ) || ( '\n' == c ) || ( 0 == c ) )
        {
            if ( n >= 0 )
            {
                m.push_back( n );
                n = -1;
            }
        }
        else if ( ( c >= '0' ) && ( c <= '9' ) )
        {
            if ( n < 0 ) n = 0;
            n *= 10;
            n += c - '0';
        }
    }
    while( c != 0 );
    cout << "Matrix with " << m.size() << " elements uploaded." << endl;
}


int weight( int r, const vector< int >& m )
{
    int w = 0;
    for( int i = 0; i < r; ++i )
        for( int j = i+1; j < r; ++j )
            w += m[ i*r + j ];
    return w;
}

// Create Minimum Spanning Tree
void buildMST( int r, const vector< int >& m, vector< int >& mst )
{
    map< int, pair< int, int > > table;
    map< int, pair< int, int > >::iterator it;
    set< int > mst_nodes;
    mst.clear();
    for( int i = 0; i < r*r; ++i ) mst.push_back( 0 );

    table[ 0 ] = pair<int,int>(0,0); // start MST at node 0
    while( ! table.empty() )
    {
        it = table.begin(); // Get cheapest link
        int new_node = it->second.first;
        if ( mst_nodes.find( new_node ) != mst_nodes.end() )
        {
            table.erase( it );
            continue;
        }
        mst_nodes.insert( new_node );
        int old_node = it->second.second;
        if ( new_node != old_node )
        {
            mst[ new_node*r + old_node ] = it->first;
            mst[ old_node*r + new_node ] = it->first;
        }
        table.erase( it );
        // Add links radiating from new node to nodes not in MST
        for( int i = 0; i < r; ++i )
        {
            if ( ( mst_nodes.find( i ) == mst_nodes.end() ) &&
                 ( m[i*r+new_node] > 0 ) )
            {
                table[ m[ i*r+new_node ] ] = pair<int,int>( i, new_node );
            }
        }
    }
}

int main( int argc, char** argv )
{
    char* filename = (char*) "network.txt";
    if ( argc > 1 ) filename = argv[ 1 ];
    vector< int > m;
    uploadMatrix( filename, m );
    int r = 1;
    while( r*r < m.size() ) ++r;
    int w1 = weight( r, m );
    cout << "Initial weight = " << w1 << endl;
    vector< int > mst;
    buildMST( r, m, mst );
    int w2 = weight( r, mst );
    cout << "Final weight = " << w2 << endl;
    cout << "Savings = " << w1 - w2 << endl;
}
