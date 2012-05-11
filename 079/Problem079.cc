#include <iostream>
#include <map>
#include <set>
using namespace std;

// A common security method used for online banking is to ask the user for
// three random characters from a passcode. For example, if the passcode was
// 531278, they may asked for the 2nd, 3rd, and 5th characters; the expected
// reply would be: 317.
// The text file, keylog.txt, contains fifty successful login attempts.
// Given that the three characters are always asked for in order, analyse
// the file so as to determine the shortest possible secret passcode of
// unknown length.

// Each line gives 2 constraints: charX < charY < charZ ( < meaning "before" )
// A given char may be repeated several times.
// Build a directional graph, charX -> charY meaning charX followed by charY
// Then find shortest path across the graph going through all connected
// vertices.
//
// 10 vertices (0 to 9) edge = 2 digit number (31, 19)
// At most 10 "followers" => building matrix (10,10)
// Assume that no digit is repeated in password (let's see)

// raw logins dumped from keylog.txt file
int logins[] = {
319, 680, 180, 690, 129, 620, 762, 689, 762, 318, 368, 710, 720, 710, 629, 168,
160, 689, 716, 731, 736, 729, 316, 729, 729, 710, 769, 290, 719, 680, 318, 389,
162, 289, 162, 718, 729, 319, 790, 680, 890, 362, 319, 760, 316, 729, 380, 319,
728, 716, 0
};

static int matrix[10][10];
void dump_matrix( )
{
    cout << "   0 1 2 3 4 5 6 7 8 9" << endl;
    cout << "   | | | | | | | | | |" << endl;

    for( int i=0; i<10; ++i )
    {
        cout << i << "--";
        for( int j=0; j<10; ++j )
        {
            int m = matrix[i][j];
            cout << ( m ? 'X' : '.' ) << ' ';
        }
        cout << endl;
    }
}

int main( int argc, char** argv )
{
    for( int i = 0; i < 10; ++i ) for( int j = 0; j < 10; ++j ) matrix[i][j]=0;

    // Build matrix
    for( int* l = logins; *l != 0; ++l )
    {
        int v1 = (*l)/100;
        int v2 = ((*l)%100)/10;
        int f2 = (*l)%10;
        cout << v1 << "->" << v2 << "->" << f2 << endl;
        matrix[v1][v2] = 1; // First constraint => one edge
        matrix[v2][f2] = 1; // 2nd constraint   => another edge
    }

    cout << endl << "Original graph matrix: " << endl << endl;
    dump_matrix();

    // Recoup information: the followers of my followers are my followers!
    int tmp[10];
    for( int i=0; i<10; ++i )
    {
        for( int j=0; j<10; ++j ) tmp[j] = matrix[i][j]; // save row

        for( int j=0; j<10; ++j )
        {
            if ( matrix[i][j] > 0 )
            {
                for( int k=0; k<10; ++k )
                {
                    tmp[k] |= matrix[j][k];
                }
            }
        }
  
        for( int j=0; j<10; ++j ) matrix[i][j] = tmp[j];
    }

    cout << endl << "After follower recoup: " << endl << endl;
    dump_matrix();

    // Recoup information: the predecessors of my predecessors ... etc, etc.
    for( int j=0; j<10; ++j )
    {
        for( int i=0; i<10; ++i ) tmp[i] = matrix[i][j]; // save column

        for( int i=0; i<10; ++i )
        {
            if ( matrix[i][j] > 0 )
            {
                for( int k=0; k<10; ++k )
                {
                    tmp[k] |= matrix[k][j];
                }
            }
        }
  
        for( int i=0; i<10; ++i ) matrix[i][j] = tmp[i];
    }

    cout << endl << "After predecessor recoup: " << endl << endl;
    dump_matrix();

    set< pair< int, int > > by_row;
    set< pair< int, int > > by_col;

    for( int i = 0; i < 10; ++i )
    {
        int row_sum = 0;
        int col_sum = 0;
        for( int j = 0; j < 10; ++j )
        {
            row_sum += matrix[i][j];
            col_sum += matrix[j][i];
        }
        if ( row_sum + col_sum > 0 )
        {
            by_row.insert( pair<int,int>( 9 - row_sum, i ) );
            by_col.insert( pair<int,int>( col_sum, i ) );
        }
    }

    cout << endl << "Password by row: ";
    set< pair< int, int > >::iterator it;
    for( it = by_row.begin(); it != by_row.end(); ++it )
        cout << it->second;

    cout << endl << "Password by col: ";
    for( it = by_col.begin(); it != by_col.end(); ++it )
        cout << it->second;
    cout << endl;
}
