#include <iostream>
#include <fstream>
#include <cstring>
#include <stack>
#include <map>
#include <cassert>

using namespace std;

class Grid
{
public:
    Grid() : num_zeroes(81)
    {
        for( int i = 0; i < 81; ++i ) {
            grid[i]  = 0;
            check[i] = 511; 
        }
    }

    Grid( const Grid& g ) : num_zeroes( g.num_zeroes )
    {
        for( int i = 0; i < 81; ++i ) {
            grid[i] = g.grid[i];
            check[i] = g.check[i];
        }
    }

    Grid& operator=( const Grid& g )
    {
        num_zeroes = g.num_zeroes;
        for( int i = 0; i < 81; ++i ) {
            grid[i]  = g.grid[i];
            check[i] = g.check[i];
        }
        return *this;
    }

    void get_possible_values( int index, stack<char>& result )
    {
        int chk = check[index];
        char c = 0;
        while( chk > 0 ) {
            ++c;
            if (chk & 1) result.push( c );
            chk >>= 1;
        }
    }

    int count_ones( int chk, char& last )
    {
        int cnt = 0;
        last = 0;
        while( chk > 0 ) {
            ++last;
            if ( chk & 1 ) ++cnt;
            chk >>= 1;
        }
        return cnt;
    }

    // Recursion! Take copy of grid beforehand...!
    bool try_to_add( int index, char val )
    {
        assert( val > 0 );
        assert( ( index >= 0 ) && ( index < 81 ) );

        if (grid[index] == val) return true; // Already added.

        if (!(check[index] & 1<<(val-1))) return false; // Not allowed.

        bool ok = true;

        grid[index] = val;
        check[index] = 0;
        --num_zeroes;

        int row = index / 9;
        int col = index % 9;
        int sqr = (row/3)*3;
        int sqc = (col/3)*3;

        int idx[3];
        stack< pair< int, char > > to_add;

        for( int x = 0; ok && (x < 9); ++x ) {
            idx[0] = x*9 + col; // update column
            idx[1] = row*9 + x; // update row
            idx[2] = (sqr+x/3)*9+(sqc+x%3); // update square

            for( int i = 0; ok && (i < 3); ++i ) {
                if (grid[idx[i]] > 0) continue;
                int& chk = check[idx[i]];
                chk &= ~(1<<(val-1));
                if (0 == chk) ok = false; // Impossible, contradiction.
            }
        }

        // Spot singletons and add to stack
        for( int x = 0; ok && (x < 9); ++x ) {
            idx[0] = x*9 + col; // update column
            idx[1] = row*9 + x; // update row
            idx[2] = (sqr+x/3)*9+(sqc+x%3); // update square

            for( int i = 0; ok && (i < 3); ++i ) {
                if (grid[idx[i]] > 0) continue;
                char l;
                int co = count_ones( grid[idx[i]], l );
                if ( 1 == co ) {
                    to_add.push(pair<int,char>(idx[i],l));
                }
            }
        }

        while( ok && ( ! to_add.empty() ) ) {
            pair<int,char> p = to_add.top(); to_add.pop();
            ok = try_to_add( p.first, p.second );
        }

        return ok;
    }

    int zeroes() { return num_zeroes; } 
    char* get_grid() { return grid; }

    int first_3_digits() { return 100*grid[0]+10*grid[1]+grid[2]; }

private:
    char grid [81];
    int  check[81];
    int  num_zeroes;
};


void dump( char* grid )
{
    static const char* vline = "+-------+-------+-------+";
    for( int i = 0; i < 81; ++i ) {
        if ( i % 27 == 0 ) cout << vline << endl;
        if ( i % 3 == 0 ) cout << "| ";
        cout << (int) grid[i] << " ";
        if ( i % 9 == 8 ) cout << "|" << endl;
    }
    cout << vline << endl;
}

int solve( char* grid )
{
    Grid g;
    bool ok = true;
    for( int i = 0; ok && ( i < 81 ); ++i ) {
        if ( grid[i] ) ok = g.try_to_add( i, grid[i] );
    }

    if ( ! ok )
    {
        cout << "Invalid grid!" << endl;
        return -1;
    }

    if ( g.zeroes() > 0 ) {
        stack< Grid > sols;
        sols.push( g );
        bool keep_going = true;
        while( keep_going ) {
            assert( sols.size() > 0 ); 
            Grid g0 = sols.top(); sols.pop();
            char* tg = g0.get_grid();
            for( int i = 0; keep_going && (i<81); ++i ) {
                if ( tg[i] > 0 ) continue;
                stack<char> s;
                g0.get_possible_values(i,s);
                while( ! s.empty() ) {
                    char c = s.top(); s.pop();
                    assert( c > 0 );
                    Grid g1 = g0;
                    if ( g1.try_to_add( i, c ) ) {
                        sols.push( g1 );
                        if ( g1.zeroes() == 0 )
                        {
                            g = g1;
                            keep_going = false;
                            break;
                        }
                    }
                }
                break;
            }
        }
    }

    cout << endl << endl << "Solution:" << endl;
    dump( g.get_grid() );
    int result = g.first_3_digits();
    cout << "First 3 digits = " << result << endl << endl;

    return result;
}

int main( int argc, char** argv )
{
    char* filename = (char*) "sudoku.txt";
    if ( argc > 1 ) filename = argv[1];
    ifstream in( filename );
    char c = 0;
    bool skip_line = false;
    char grid[ 81 ]; memset( grid, 0, 81 );
    char items = 0;
    int  cnt = 0;
    int  sum = 0;

    if ( in ) do
    {
        if ( ! in.get( c ) ) c = 0;
        switch( c )
        {
            case 'G': skip_line = true; break;
            case '\r': break;
            case '\n': skip_line = false; break;
            default:
                if ( ! skip_line )
                {
                    if ( ( c >= '0' ) && ( c <= '9' ) )
                    {
                        grid[ items++ ] = c - '0';
                    }
                    if ( 81 == items )
                    {
                        cout << "Grid #" << ++cnt << ":" << endl;
                        dump( grid );
                        sum += solve( grid );
                        cout << endl;
                        items = 0;
                        memset( grid, 0, 81 );
                    }
                }
                break;
        }
    }
    while( c != 0 );

    cout << endl << "The sum is : " << sum << endl;
}
