#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <fstream>
#include <map>
#include <set>
#include <vector>
using namespace std;

// Each character on a computer is assigned a unique code and the preferred
// standard is ASCII (American Standard Code for Information Interchange).
// For example, uppercase A = 65, asterisk (*) = 42, and lowercase k = 107.
//
// A modern encryption method is to take a text file, convert the bytes to
// ASCII, then XOR each byte with a given value, taken from a secret key.
// The advantage with the XOR function is that using the same encryption key
// on the cipher text, restores the plain text; for example, 65 XOR 42 = 107,
// then 107 XOR 42 = 65.
//
// For unbreakable encryption, the key is the same length as the plain text
// message, and the key is made up of random bytes. The user would keep the
// encrypted message and the encryption key in different locations, and without
// both "halves", it is impossible to decrypt the message.
//
// Unfortunately, this method is impractical for most users, so the modified
// method is to use a password as a key. If the password is shorter than the
// message, which is likely, the key is repeated cyclically throughout the
// message. The balance for this method is using a sufficiently long password
// key for security, but short enough to be memorable.
//
// Your task has been made easy, as the encryption key consists of three lower
// case characters.
// Using cipher1.txt (right click and 'Save Link/Target As...'), a file
// containing the encrypted ASCII codes, and the knowledge that the plain text
// must contain common English words, decrypt the message and find the sum of
// the ASCII values in the original text.


// OK, so key is hex: k1, k2, k3  k. in [0x61 'a'..0x77 'z']
// Analyse distribution of the 3 cycles in file ( position % 3 = 0,1 or 2) 
// Compare with typical distribution of an English text and test
// hypotheses automatically.
// From: http://en.wikipedia.org/wiki/Letter_frequency:
// In decreasing freq: E,T,A,O,I,N,S,H,R,D,L,C,U,M,W,F,G,Y,P,B,V,K,J,X,Q,Z

static char* freqs = (char*)
    "EeTtAaOoIiNnSsHhRrDdLlCcUuMmWwFfGgYyPpBbVvKkJjXxQqZz";

void ParseFile( char* filename, vector<char>& message )
{
    //cout << "Parsing: " << filename << endl << endl;
    ifstream in( filename );
    if ( in )
    {
        char c = 0;
        char code = 0;
        do
        {
            if ( ! in.get(c) ) c = 0;
            if ( ( 0 == c ) || ( ',' == c ) )
            {
                message.push_back( code );
                //cout << setw(4) << (int) code << " ";
                code = 0;
            }
            else if ( ( c >= '0' ) && ( c <= '9' ) )
            {
                code *= 10;
                code += c - '0';
            }
        }
        while( c != 0 );
        in.close();
        //cout << endl;
    }
}

int main( int argc, char** argv )
{
    char* filename = (char*) "cipher1.txt";
    if ( argc > 1 ) filename = argv[ 1 ];
    vector<char> msg;
    ParseFile( filename, msg );
    map<char,int> bags[3];
    set<pair<int,char> > dists[3];
    for(unsigned int i = 0; i < msg.size(); ++i )
    {
        ++bags[i % 3][msg[i]];
    }
    for( int i = 0; i < 3; ++i )
        for( map<char,int>::iterator j=bags[i].begin(); j!=bags[i].end(); ++j )
            if ( dists[i].size() < 10 )
                dists[i].insert( pair<int,char>( j->second, j->first ));

    for( int i = 0; i < 3; ++i )
    {
        //cout << "Top 10 for " << i << ": ";
        set<pair<int,char> >::reverse_iterator j = dists[i].rbegin();
        for( ; j != dists[i].rend(); ++j )
        {
            //cout << setw(3) << (int) j->second << "/" << j->first << " ";
            ++j;
        }
        //cout << endl;
    }

    // Automatic hypotheses, based on freqs
    //cout << "Frequencies = " << freqs << endl << endl;

    char key[4];
    key[0]=0;key[1]=0;key[2]=0;key[3]=0;
    set<pair<int,char> >::reverse_iterator ri;
    
    for( int i = 0; i < 3; ++i )
    {
        bool  match  = false;
        for( char* l = freqs; (*l != 0 )&&(!match); ++l )
        {
            for( ri = dists[i].rbegin(); ri != dists[i].rend(); ++ri )
            {
                key[i] = *l ^ (ri->second);
                // Bad key?
                if ( (  key[i] < 'a' ) ||( key[i] > 'z' ) ) continue; 
                cout << "Trying key[" << i << "]=" << key[i] << endl;
                // Check decryption
                bool check = true;
                for(unsigned int j = i; check && (j < msg.size()); j += 3)
                {
                    char d = key[i] ^ msg[j];
                    // ASCII 0..31 control characters (not printable)
                    check = ( d >= 32 );
                    // "Strange" characters excluded (^~`)
                    check &= ( d != '^' ) && ( d != '~' ) && ( d != '`' );
                }
                if ( ! check ) continue;
                int sum = 0;
                for(unsigned int j = 0; j < msg.size(); ++j)
                {
                    char clear = ( key[j%3]>0? ( msg[j] ^ key[j%3]) : '.');
                    if (clear < 31) exit(1);
                    sum += clear;
                    cout << (char) clear;
                }
                cout << endl << endl << "Sum = " << sum << endl;
                cout << endl << "Keep this? (y|n)" << endl;
                char yes_or_no = 'y';
                //cin >> yes_or_no;
                match = ( 'y' == yes_or_no ) || ( 'Y' == yes_or_no );
                
                if ( match ) break;
            }
        }
    }
}
