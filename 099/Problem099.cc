#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

/***
Comparing two numbers written in index form like 2^11 and 3^7 is not
difficult, as any calculator will confirm that 2^11=2048 < 3^7= 2187.

However, confirming that 632382^518061 > 519432^525806 would be much more
difficult, as both numbers contain over three million digits.

Using base_exp.txt, a 22K test file containing 1000 lines with a base/exponent
pair on each line, determine which line number has the greatest numerical
value.
***/

// Use logarithms!

int max_line( char* filename )
{
    double max = 0.0;
    int    max_line = 0;

    ifstream in( filename );
    if ( in )
    {
        char c = 0;

        int  num = 0;
        int  line = 0;
        double val = 0.0;

        do
        {
            if ( ! in.get( c ) ) c = 0;
            if ( ( c >= '0' ) && ( c <= '9' ) )
            {
                num = num*10 + (c-'0');
            }
            else if ( ',' == c )
            {
                cout << num << ',';
                val = log( num );
                num = 0;
            }
            else if ( num > 0 )
            {
                cout << num << " = ";
                val *= num;
                cout << val;
                ++line;
                if ( val > max )
                {
                    max = val;
                    max_line = line;
                    cout << " (NEW MAX)";
                }
                cout << " line = " << line << endl;
                val = 0.0;
                num = 0;
            }
        }
        while( c != 0 );
        in.close();
    }
    return max_line;
}


int main( int argc, char** argv )
{
    char* filename = (char*) "base_exp.txt";
    if ( argc > 1 ) filename = argv[ 1 ];
   
    int mline = max_line( filename );
    cout << "Max line: " << mline << endl;
}
