#include <iostream>
#include <vector>
#include <set>
#include <fstream>
using namespace std;

// NOTE: This problem is a significantly more challenging version of Problem 81
// In the 5 by 5 matrix below, the minimal path sum from the top left to the
// bottom right, by moving left, right, up, and down, is indicated in bold red
// and is equal to 2297.
// 
// 131 673 234 103 18 
// 201 96 342 965 150 
// 630 803 746 422 111 
// 537 699 497 121 956 
// 805 732 524 37 331 
//  
// Find the minimal path sum, in matrix.txt (right click and 'Save Link/Target
// As...'), a 31K text file containing a 80 by 80 matrix, from the top left to
// the bottom right by moving left, right, up, and down.

// Dijkstra's shortest path algorithm, basically.
// Twist: cost of link = sum of matrix values at both ends

int test_mat[] = {
 131, 673, 234, 103,  18,
 201,  96, 342, 965, 150,
 630, 803, 746, 422, 111,
 537, 699, 497, 121, 956,
 805, 732, 524,  37, 331, -1
};

int min_path_sum( vector<int>& m0, int dim )
{
    vector<int> m(dim*dim);
    set<int> unvisited;
    for( int i = 0; i < dim*dim; ++i ) m[ i ] = 10000000; // "Infinity"
    m[ 0 ] = m0[ 0 ];
    int c = 0; // current cell
    int nc = 0; // next cell
    int min = 0;
    int mc = 0;
    int iter = 0;
    int n,e,s,w; // neighbour indices

    while( m0[c] > 0 )
    {
        ++iter;
        mc = m[c]+m0[c];
        n = ( c >= dim ? c - dim : -1 );
        s = ( c / dim < dim-1 ? c + dim : -1 ); 
        w = ( c % dim > 0 ? c - 1 : -1 );
        e = ( c % dim < dim-1 ? c + 1 : -1 );
        // Check all neighbours
        int nb = 0;
        min = 10000000;
        if ((n>0)&&(m0[n]>0)&&(mc+m0[n]<m[n]))
        {
            ++nb;
            unvisited.insert(n);
            m[n] = mc + m0[n];
            if ( m[n] < min ) min = m[n];
        }
        if ((s>0)&&(m0[s]>0)&&(mc+m0[s]<m[s]))
        {
            ++nb;
            unvisited.insert(s);
            m[s] = mc + m0[s];
            if ( m[s] < min ) min = m[s];
        }
        if ((w>0)&&(m0[w]>0)&&(mc+m0[w]<m[w]))
        {
            ++nb;
            unvisited.insert(w);
            m[w] = mc + m0[w];
            if ( m[w] < min ) min = m[w];
        }
        if ((e>0)&&(m0[e]>0)&&(mc+m0[e]<m[e]))
        {
            ++nb;
            unvisited.insert(e);
            m[e] = mc+m0[e];
            if ( m[e] < min ) min = m[e];
        }

        //cout << "("<<c/dim<<","<<c%dim<<")="<<m0[c]<<" "<<mc<<" "<<nb<<endl;
        m0[c] = - m0[c]; // mark as visited
        set<int>::iterator it = unvisited.find( c );
        if ( it != unvisited.end() ) unvisited.erase( it );

        if ( ! unvisited.empty() )
        {
            min = 10000000;
            for( it = unvisited.begin(); it != unvisited.end(); ++it )
            {
                // "Greedy" algorithm
                if ( m[*it] < min ) { min = m[*it]; nc = *it; }
            }
            c = nc;
        }
    }
    cout << endl << iter << " iterations." << endl;
    cout << unvisited.size() << " unvisited nodes." << endl;

    return (-m0[dim*dim-1]+m[dim*dim-1])/2;
}

void parseMatrix( char* filename, vector<int>& mat )
{
    cout << "Parsing: " << filename << endl << endl;
    ifstream in( filename );
    if ( in )
    {
        char c = 0;
        int m = -1;
        do
        {
            if ( ! in.get(c) ) c = 0;
            if ( ( c >= '0' ) && ( c <= '9' ) )
            {
                if ( m < 0 ) m = 0;
                m = 10*m + c - '0';
            }
            else if ( m >= 0 )
            {
                mat.push_back( m );
                m = -1;
            }
            //cout << ( c > 0 ? c : '\n' );
        }
   
        while( c != 0 );
        in.close();
    }
}

int main( int argc, char** argv )
{
    vector<int> t_mat;
    int* i = test_mat;
    while( *i >= 0 ) {
        t_mat.push_back( *i );
        ++i;
    }

    int min = min_path_sum( t_mat, 5 );
    //cout << endl << "Test matrix: min path sum = " << min << endl;

    char* filename = (char*) "matrix.txt";
    if ( argc > 1 ) filename = argv[1];

    vector< int > mat;
    parseMatrix( filename, mat );
    cout << "Size of mat: " << mat.size() << endl;
    int r = 1;
    while( r*r < (int) mat.size() ) ++r;
    cout << "Root = " << r << endl;
    min = min_path_sum( mat, r );
    cout << endl << "Min path sum = " << min << endl << endl;
}
