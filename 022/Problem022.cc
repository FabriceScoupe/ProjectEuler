#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
using namespace std;

// Total alphabetical score of sorted name list
// Score = sum of alphabetical value * position in sorted list

// Trick: map is actually sorted when accessed via iterator later on.
typedef map< string, int > StringMap;

void parseNames( const char* filename, StringMap& names )
{
    ifstream in( filename );
    if (in)
    {
        char c = 0;
        vector<char> current;
        bool ok = true;
        do
        {
            if ( ! in.get(c) ) c = 0;
            if ( ( 0 == c ) || ( ',' == c ) )
            {
                current.push_back(0);
                string tmp_s( &current[0] );
                int sum = 0;
                for( int i = 0; i < tmp_s.length(); ++i )
                    sum += tmp_s[i] - 'A' + 1;
                names[ tmp_s ] = sum;
                current.clear();
            }
            else if ( ( c >= 'A' ) && ( c <= 'Z' ) )
            {
                current.push_back(c);
            }
        } while( c != 0 ); 
        in.close();
    }
}


int main( int argc, char** argv )
{
    char* filename = (char*) "names.txt";
    if ( argc > 1 ) filename = argv[1];
    StringMap names;
    parseNames( (const char*) filename, names );
    int count = 0;
    long long total = 0;
    for( StringMap::iterator it = names.begin();
         it != names.end(); ++it )
    {
        ++count;
        //cout << "#" << count << ": " << it->first 
        //     << " (" << it->second << ")" << endl;
        total += ( it->second ) * count;
    }
    cout << "Total score = " << total << endl;
}
