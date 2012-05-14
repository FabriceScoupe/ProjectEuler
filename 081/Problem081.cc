#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

// In the 5 by 5 matrix below, the minimal path sum from the top left
// to the bottom right, by only moving to the right and down, is indicated
// in bold red and is equal to 2427.
//
// 131 673 234 103 18 
// 201 96  342 965 150 
// 630 803 746 422 111 
// 537 699 497 121 956 
// 805 732 524 37  331 
// 
// Find the minimal path sum, in matrix.txt (right click and 'Save Link/Target
// As...'), a 31K text file containing a 80 by 80 matrix, from the top left to
// the bottom right by only moving right and down.

// Idea: propagate a bottom-left/top-right diagonal through the matrix from
// the top-left to the bottom-right. For each cell on this diagonal, 
// add the minimum of its above and left neighbours (if they exist).
// When diagonal reaches bottom-right corner, we have our minimum.

int test_mat[] = {
 131, 673, 234, 103,  18,
 201,  96, 342, 965, 150,
 630, 803, 746, 422, 111,
 537, 699, 497, 121, 956,
 805, 732, 524,  37, 331, -1
};

int min_path_sum( vector<int>& matrix, int dim )
{
    if ( 0 == dim ) return 0;
    if ( 1 == dim ) return matrix[0];
    int max = 0;
    for( int i = 0; i < dim*dim; ++i ) if (matrix[i] > max) max = matrix[i];
    max *= 2*dim-1; // At most, sum <= max * 2 * (dim-1)

    for( int d = 1; d < 2*dim-1; ++d ) {
        int i0 = d;
        int j0 = 0;
        while( i0 >= dim ) {
            --i0;
            ++j0;
        }

        do {
            int up = ( i0 > 0 ? matrix[(i0-1)*dim+j0] : max+1 );
            int left = ( j0 > 0 ? matrix[i0*dim+j0-1] : max+1 );
            matrix[i0*dim+j0] += ( up < left ? up : left );
            --i0; ++j0;
        } while( ( i0 >= 0 ) && ( j0 < dim ) );
    }
    return matrix[ dim*dim-1 ];
}

void show_path( vector<int>& orig, vector<int>& sums, int dim )
{
     int i = dim-1; int j = dim-1;
     int check_sum = 0;
     int max = 0;
     for( int k = 0; k < dim*dim; ++k ) if ( sums[k] > max ) max = sums[k];
     while( ( i>=0 ) && ( j>=0 ) )
     {
         check_sum += orig[i*dim+j];
         cout << orig[i*dim+j] << " ("<<i<<","<<j<<") ";
         int up   = ( i > 0 ? sums[(i-1)*dim+j] : max+1 );
         int left = ( j > 0 ? sums[i*dim+j-1] : max+1 );
         i -= ( up < left ? 1 : 0 );
         j -= ( up < left ? 0 : 1 );
     }
     cout << endl << endl << "Check_sum = " << check_sum << endl;
}

void parseMatrix( char* filename, vector<int>& mat )
{
    cout << "Parsing: " << filename << endl << endl;
    ifstream in( filename );
    if ( in ) {
        char c = 0;
        int m = -1;
        do {
            if ( ! in.get(c) ) c = 0;
            if ( ( c >= '0' ) && ( c <= '9' ) ) {
                if ( m < 0 ) m = 0;
                m = 10*m + c - '0';
            } else if ( m >= 0 ) {
                mat.push_back( m );
                m = -1;
            }
            //cout << ( c > 0 ? c : '\n' );
        } while( c != 0 );
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

/*
    for( int i=0; i<5; ++i ) for( int j=0; j<5; ++j )
        cout << t_mat[i*5+j] << ( j < 4 ? ',' : '\n' );
*/

    vector<int> t_mat_o( t_mat );

/*
    cout << endl << "Test matrix: min path sum = "
         << min_path_sum( t_mat, 5 ) << endl;

    show_path( t_mat_o, t_mat, 5 );
*/

    char* filename = (char*) "matrix.txt";
    if ( argc > 1 ) filename = argv[1];

    vector< int > mat;
    parseMatrix( filename, mat );
    cout << "Size of mat: " << mat.size() << endl;
    int r = 1;
    while( r*r < (int) mat.size() ) ++r;
    cout << "Root = " << r << endl;
    if ( r <= 10 )
    {
        for( int i = 0; i < r; ++i ) for( int j = 0; j < r; ++j )
            cout << mat[i*r+j] << ( j < r-1 ? ",": "\r\n");
    }

    vector< int > mat_o( mat );
    int min = min_path_sum( mat, r );
    
    if ( r <= 10 )
    {
        cout << endl;
        for( int i = 0; i < r; ++i ) for( int j = 0; j < r; ++j )
            cout << mat[i*r+j] << ( j < r-1 ? ",": "\r\n");
    }

    cout << endl << "Min path sum = " << min << endl << endl;

    //show_path( mat_o, mat, r );

    return 0;
}
