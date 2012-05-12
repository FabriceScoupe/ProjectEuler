#include <iostream>
#include <fstream>
#include <set>

using namespace std;

// How many triangle words in file?
// t(n)=n(n+1)/2 word value = sum[k=0..length-1] char[k]-'A'+1

int numberOfTriangleWords( const char* filename )
{
    int count = 0;
    set<int> triangles;
    int sum = 0;
    for( int i = 1; i <= 50; ++i )
    {
        sum += i;
        triangles.insert( sum );
    }

    ifstream in( filename );
    if ( in )
    {
        char c = 0;
        int value = 0;
        do
        {
            if ( ! in.get(c) ) c = 0;
            if ( ( 0 == c ) || ( ',' == c ) )
            {
                if ( triangles.find( value ) != triangles.end() )
                {
                    //cout << " (triangle=" << value << ")";
                    ++count;
                }
                //cout << endl;
                value = 0;
            }
            else if ( ( c >= 'A' ) && ( c <= 'Z' ) )
            {
                //cout << c;
                value += c - 'A' + 1;
            }
        }
        while( c != 0 );
        in.close();
    }
    return count;
}

int main( int argc, char** argv )
{
    char* filename = (char*) "words.txt";
    if ( argc > 1 ) filename = argv[1];
    int count = numberOfTriangleWords( filename );
    cout << endl << "Number of triangle words = " << count << endl;
}
