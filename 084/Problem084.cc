#include <iostream>
#include <cstdlib>
#include <map>
#include <set>

using namespace std;

/*
 * Project Euler: Problem 084 (http://projecteuler.net/problem=84)
 */

// In the game, Monopoly, the standard board is set up in the following way:
//
//GO A1 CC1 A2 T1 R1 B1 CH1 B2 B3 JAIL 
//H2                              C1 
//T2                              U1 
//H1                              C2 
//CH3                             C3 
//R4                              R2 
//G3                              D1 
//CC3                             CC2 
//G2                              D2 
//G1                              D3 
//G2J F3 U2 F2 F1 R3 E3 E2 CH2 E1 FP 
//
// A player starts on the GO square and adds the scores on two 6-sided dice 
// to determine the number of squares they advance in a clockwise direction.
// Without any further rules we would expect to visit each square with equal
// probability: 2.5%. However, landing on G2J (Go To Jail),
//  CC (community chest), and CH (chance) changes this distribution.
//
// In addition to G2J, and one card from each of CC and CH, that orders the
// player to go directly to jail, if a player rolls three consecutive doubles,
// they do not advance the result of their 3rd roll. Instead they proceed
// directly to jail.
//
// At the beginning of the game, the CC and CH cards are shuffled. When a
// player lands on CC or CH they take a card from the top of the respective
// pile and, after following the instructions, it is returned to the bottom
// of the pile. There are sixteen cards in each pile, but for the purpose of
// this problem we are only concerned with cards that order a movement; any
// instruction not concerned with movement will be ignored and the player will
// remain on the CC/CH square.
//
// Community Chest (2/16 cards): 
// Advance to GO 
// Go to JAIL 
// Chance (10/16 cards): 
// Advance to GO 
// Go to JAIL 
// Go to C1 
// Go to E3 
// Go to H2 
// Go to R1 
// Go to next R (railway company) 
// Go to next R 
// Go to next U (utility company) 
// Go back 3 squares. 
// The heart of this problem concerns the likelihood of visiting a particular
// square. That is, the probability of finishing at that square after a roll.
// For this reason it should be clear that, with the exception of G2J for which
// the probability of finishing on it is zero, the CH squares will have the
// lowest probabilities, as 5/8 request a movement to another square, and it
// is the final square that the player finishes at on each roll that we are
// interested in. We shall make no distinction between "Just Visiting" and
// being sent to JAIL, and we shall also ignore the rule about requiring a
// double to "get out of jail", assuming that they pay to get out on their
// next turn.
//
// By starting at GO and numbering the squares sequentially from 00 to 39 we
// can concatenate these two-digit numbers to produce strings that correspond
// with sets of squares.
//
// Statistically it can be shown that the three most popular squares, in order,
// are JAIL (6.24%) = Square 10, E3 (3.18%) = Square 24, and GO (3.09%) = 
// Square 00. So these three most popular squares can be listed with the
// six-digit modal string: 102400.
//
// If, instead of using two 6-sided dice, two 4-sided dice are used, find the
// six-digit modal string.

// Brute force: Monte Carlo.

/*
static const char* board[] = {
//  00      01    02     03     04    05    06     07     08    09
    "GO",   "A1", "CC1", "A2",  "T1", "R1", "B1",  "CH1", "B2", "B3",
    "JAIL", "C1", "U1" , "C2",  "C3", "R2", "D1",  "CC2", "D2", "D3",
    "FP",   "E1", "CH2", "E2",  "E3", "R3", "F1",  "F2" , "U2", "F3",
    "G2J",  "G1", "G2",  "CC3", "G3", "R4", "CH3", "H1" , "T2", "H2"
};
*/

static int community[16];
static int community_card = 0;
static int chance[16];
static int chance_card = 0;

void shuffle_cards( int* pack )
{
    //cout << "Shuffling...";
    for( int i = 0; i < 16; ++i ) pack[i] = i+1;
    int j,k,tmp;
    while( rand() % 100 < 99 )
    {
        //cout << '.';
        j = rand() % 16; k = rand() % 16;
        tmp = pack[ j ]; pack[ j ] = pack[ k ]; pack[ k ] = tmp;
    }
    //cout << endl;
}

inline int pick_community( int pos )
{
   int ret = pos;
   switch( community[ community_card ] )
   {
       case 1: ret = 0; break;
       case 2: ret = 10; break;
       default: break;
   }
   ++community_card;
   if ( 16 == community_card ) community_card = 0;
   return ret;
}

inline int pick_chance( int pos )
{
    int ret = pos;
    switch( chance[ chance_card ] )
    {
        case 1: ret = 0; break;
        case 2: ret = 10; break;
        case 3: ret = 11; break;
        case 4: ret = 24; break;
        case 5: ret = 39; break;
        case 6: ret = 5; break;
        case 7:
        case 8: if ( 7 == pos )
                {
                    ret = 15;
                }
                else if ( 22 == pos )
                {
                    ret = 25;
                }
                else
                {
                    ret = 5;
                }
                break;

        case 9: if ( 22 == pos )
                {
                    ret = 28;
                }
                else
                {
                    ret = 12;
                }
                break;

        case 10: ret -= 3; break;

        default: break;
    }
    ++chance_card;
    if ( 16 == chance_card ) chance_card = 0;
    return ret;
}

inline int roll( int sides, bool& is_double )
{
    int r1 = rand() % sides;
    int r2 = rand() % sides;
    is_double = ( r1 == r2 );
    return( r1 + r2 + 2 );
}

int main( int argc, char** argv )
{
    int sides = 4; // Number of sides on dice
    if ( argc > 1 ) sides = atoi( argv[ 1 ] );
    int seed = 0; // Random seed
    if ( argc > 2 ) seed = atoi( argv[ 2 ] );
    int iters = 1000000; // Iterations
    if ( argc > 3 ) iters = atoi( argv[ 3 ] );

    srand( seed );
    shuffle_cards( community );
    //for( int i = 0; i < 16; ++i ) cout << community[ i ] << " ";
    //cout << endl;
    shuffle_cards( chance );
    //for( int i = 0; i < 16; ++i ) cout << chance[ i ] << " ";
    //cout << endl;

    map< int, int > dist;
    int pos = 0;
    int doubles = 0;
    for( int iter = 0; iter < iters; ++iter )
    {
        //if ( iter % 10000 == 0 ) { cout << '.'; flush( cout ); }
        bool is_double;
        //do
        //{
            pos += roll( sides, is_double );
            if ( pos > 39 ) pos -= 40;
            doubles = ( is_double ? doubles+1 : 0 );
            if ( ( 3 == doubles ) || ( 30 == pos ) )
            {
                pos = 10;
                doubles = 0;
            }
            else 
            {
                if ((7==pos)||(22==pos)||(36==pos))
                {
                    pos = pick_chance( pos );
                }
                if ((2==pos)||(17==pos)||(33==pos))
                {
                    pos = pick_community( pos );
                }
             }
        //}
        //while( is_double && ( pos != 10 ) );
        dist[ pos ]++;
    }
    //cout << endl;

    set< pair< int, int > > freq;
    for( int i = 0; i < 40; ++i ) freq.insert( pair<int,int>( dist[i], i ) );
    set<pair<int, int> >::reverse_iterator it = freq.rbegin();
    /*
    for(;it != freq.rend(); ++it ) {
        cout << it->second << " (" << it->first << ")" << endl;
    }
    */
    cout << "Answer: " << it->second; ++it;
    cout << it->second; ++it;
    cout << it->second << endl;
    return 0;
}
