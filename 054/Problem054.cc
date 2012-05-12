#include <iostream>
#include <fstream>
#include <map>
using namespace std;

// How many hands did Player 1 win in the game of poker?
// H(earts) C(lub) S(pade) D(iamond)
// 2,3,4,5,6,7,8,9,10,J,Q,K,A
// High Card < One Pair < Two Pairs < Three of a Kind
// < Straight < Flush < Full House < Four of a Kind < Straight Flush
// < Royal Flush (10,J,Q,K,A).

struct Hand
{
    enum Combination 
    {
        HIGH_CARD         = 0,
        ONE_PAIR,        // 1
        TWO_PAIRS,       // 2
        THREE_OF_A_KIND, // 3
        STRAIGHT,        // 4
        FLUSH,           // 5
        FULL_HOUSE,      // 6
        FOUR_OF_A_KIND,  // 7
        STRAIGHT_FLUSH,  // 8
        ROYAL_FLUSH      // 9
    };

    map<char,char> value_map;
    map<char,char> suit_map;
    Combination    combi;
    char           primary;
    char           secondary;

    Hand() : value_map(), suit_map(), combi( HIGH_CARD ),
             primary( 0 ), secondary( 0 ) { };

    void clear()
    {
        value_map.clear();
        suit_map.clear();
        combi = HIGH_CARD;
        primary = 0;
        secondary = 0;
    }

    void add( char value, char suit )
    {
        ++value_map[ value ];
        char vm = value_map[ value ];
        ++suit_map[ suit ];
        char sm = suit_map[ suit ];
        if ( 2 == vm )
        {
            if ( HIGH_CARD == combi )
            {
                combi = ONE_PAIR;
                primary = value;
            }
            else if ( ONE_PAIR == combi )
            {
                combi = TWO_PAIRS;
                secondary = ( value > primary ? primary : value );
                primary = ( value > primary ? value : primary );
            }
            else if ( THREE_OF_A_KIND == combi )
            {
                combi = FULL_HOUSE;
                secondary = value;
            }
        }
        else if ( 3 == vm )
        {
            if ( ONE_PAIR == combi )
            {
                combi = THREE_OF_A_KIND;
            }
            else if ( TWO_PAIRS == combi )
            {
                combi = FULL_HOUSE;
                secondary = ( value > primary ? primary : value );
                primary = ( value > primary ? value : primary );
            }
        }
        else if ( 4 == vm )
        {
            combi = FOUR_OF_A_KIND;
        }

        if ( 5 == value_map.size() )
        {
            map<char,char>::iterator first = value_map.begin();
            map<char,char>::reverse_iterator last = value_map.rbegin();
            if ( last->first - first->first == 4 )
            {
                 combi = STRAIGHT;
                 primary = last->first;
            }
        }

        if ( 5 == sm )
        {
            if ( STRAIGHT == combi )
            {
                combi = ( 14 == primary ? ROYAL_FLUSH : STRAIGHT_FLUSH );
            }
            else
            {
                combi = FLUSH;
            }
        }
    }

    bool less_than( Hand& right )
    {
        bool result;
        if ( combi != right.combi )
        {
            result = ( combi < right.combi );
        }
        else if ( primary != right.primary )
        {
            result = ( primary < right.primary );
        }
        else if ( secondary != right.secondary )
        {
            result = ( secondary < right.secondary );
        }
        else
        {
            map<char,char>::reverse_iterator i1 = value_map.rbegin();
            map<char,char>::reverse_iterator i2 = right.value_map.rbegin();
            while( i1->first == i2->first )
            {
                ++i1;
                ++i2;
            }
            result = ( i1->first < i2->first );
        }
        return result;
    }
};



int ParseHands( const char* filename )
{
    int won_by_1 = 0;

    ifstream in( filename );
    if ( in )
    {
        char c = 0;
        char cards = 0;
        char value = 0;
        Hand h1, h2;
        Hand* h = &h1;
        do
        {
            if ( ! in.get(c) ) c = 0;
            if ( '\n' == c )
            {
                if ( !h1.less_than(h2) )
                {
                    ++won_by_1;
                }
                //cout << " won by player" << (h1.less_than(h2)?2:1) << " ";
                //cout << h1.combi << " vs " << h2.combi << endl;
                h1.clear();
                h2.clear();
                h = &h1;
                cards = 0;
            }
            else if (('C'==c)||('H'==c)||('S'==c)||('D'==c))
            {
                ++cards;
                h->add( value, c );
                //cout << c;
                if ( 5 == cards ) { h = &h2; /* cout << "  / "; */ }
                //if ( 10 == cards ){ cout << "  | "; flush( cout ); }
            }
            else if ((c>='2')&&(c<='9'))
            {
                value = c-'0';
                //cout << c;
            }
            else
            {
                switch( c )
                {
                    case 'T': value = 10; break;
                    case 'J': value = 11; break;
                    case 'Q': value = 12; break;
                    case 'K': value = 13; break;
                    case 'A': value = 14; break;
                    default: break;
                }
                //if (( c != '\r' )&&( c!= 0 )) cout << c; 
            }
        }
        while( c != 0 );
        in.close();
    }
    cout << endl << "Won by player 1: " << won_by_1 << endl;
    return won_by_1;
}

int main( int argc, char** argv )
{
    char* filename = (char*) "poker.txt";
    if ( argc > 1 ) filename = argv[ 1 ];
    ParseHands( filename );
}
