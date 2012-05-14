#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

// NOTE: This problem is a more challenging version of Problem 81.
// 
// The minimal path sum in the 5 by 5 matrix below, by starting in any cell
// in the left column and finishing in any cell in the right column, and only
// moving up, down, and right, is indicated in red and bold; the sum is equal
// to 994.
// 
// 131 673 234 103 18 
// 201 96 342 965 150 
// 630 803 746 422 111 
// 537 699 497 121 956 
// 805 732 524 37 331 
//  
// Find the minimal path sum, in matrix.txt (right click and 
// 'Save Link/Target As...'), a 31K text file containing a 80 by 80 matrix,
// from the left column to the right column.

// Same idea as for 81, but this time with a column "swiping" from left to
// right. Possible paths include current column, so a wee twist there.

int test_mat[] = {
 131, 673, 234, 103,  18,
 201,  96, 342, 965, 150,
 630, 803, 746, 422, 111,
 537, 699, 497, 121, 956,
 805, 732, 524,  37, 331, -1
};

int min_path_sum( vector<int>& matrix, int dim )
{
    int* tmp_col = new int[ dim ];
    int  min     = 0;
    for( int j = 1; j < dim-1; ++j )
    {
        for( int i = 0; i < dim; ++i )
        {
            int sum_col = 0;
            min = matrix[i*dim + j-1];
            for( int k = i-1; k >= 0; --k )
            {
                sum_col += matrix[ k*dim + j ];
                if ( matrix[ k*dim + j-1 ] + sum_col < min )
                    min = matrix[ k*dim + j-1 ] + sum_col;
            }
            sum_col = 0;
            for( int k = i+1; k < dim; ++k )
            {
                sum_col += matrix[ k*dim + j ];
                if ( matrix[ k*dim + j-1 ] + sum_col < min )
                    min = matrix[ k*dim + j-1 ] + sum_col;
            }
            tmp_col[i] = min + matrix[ i*dim + j ];
        }
        for( int i = 0; i < dim; ++i ) matrix[i*dim + j]=tmp_col[i];
    }
    delete[] tmp_col;
    for( int i = 0; i < dim; ++i )
        matrix[ i*dim + dim-1 ] += matrix[ i*dim + dim-2 ];

    min = matrix[ dim-1 ];
    for( int i = 1; i < dim; ++i )
        if ( matrix[ i*dim + dim-1 ] < min ) min = matrix[ i*dim + dim-1 ];

    return min;
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

/*
    cout << endl << "Test matrix: min path sum = "
         << min_path_sum( t_mat, 5 ) << endl;
*/

    char* filename = (char*) "matrix.txt";
    if ( argc > 1 ) filename = argv[1];

    vector< int > mat;
    parseMatrix( filename, mat );
    cout << "Size of mat: " << mat.size() << endl;
    int r = 1;
    while( r*r < (int) mat.size() ) ++r;
    cout << "Root = " << r << endl;
    cout << endl << "Min path sum = " << min_path_sum( mat, r ) << endl << endl;
}
