#include <iostream>
#include <iomanip>
#include <map>

using namespace std;

/***
Peter has nine four-sided (pyramidal) dice,
each with faces numbered 1, 2, 3, 4.
Colin has six six-sided (cubic) dice,
each with faces numbered 1, 2, 3, 4, 5, 6.

Peter and Colin roll their dice and compare totals: the highest total wins.
The result is a draw if the totals are equal.

What is the probability that Pyramidal Pete beats Cubic Colin? Give your answer rounded to seven decimal places in the form 0.abcdefg
***/

// Build discrete probability distributions for both dice combinations
// Prob( X = x ) 
// for 9 d4 -> from 9 to 36
// for 6 d6 -> from 6 to 36
// Calculate
// 
void roll_map( int ndice, int nsides, map< int, int >& hist )
{
    char* dice = new char[ ndice ];
    for( int i = 0; i < ndice; ++i ) dice[i] = 1;
    hist.clear();
    while( dice[ ndice-1 ] <= nsides )
    {
        char sum = 0;
        for( int i = 0; i < ndice; ++i ) sum += dice[ i ];
        ++hist[ sum ];
        ++dice[ 0 ];
        char carry = 0;
        if ( dice[ 0 ] > nsides )
        {
            carry = 1;
            dice[ 0 ] = 1;
        }
        for( int i = 1; ( i < ndice-1 )&&( carry > 0 ); ++i )
        {
            ++dice[ i ];
            if ( dice[ i ] > nsides )
            {
                dice[ i ] = 1;
            }
            else
            {
                carry = 0;
            }
        }
        if ( carry > 0 ) ++dice[ ndice-1 ]; 
    }
    delete[] dice;
}

int main( int argc, char** argv )
{
    map< int, int > hist9d4;
    map< int, int > hist6d6;

    roll_map( 9, 4, hist9d4 );
    roll_map( 6, 6, hist6d6 );

    int norm9d4 = 0;
    int norm6d6 = 0;

    for( int i = 6; i <= 36; ++i )
    {
        norm9d4 += hist9d4[ i ];
        norm6d6 += hist6d6[ i ];
        cout << "[" << i << "] -> " << hist9d4[ i ] << " vs " << hist6d6[ i ]
             << endl;
    }

    cout << "Total 9d4 = " << norm9d4 << endl;
    cout << "Total 6d6 = " << norm6d6 << endl;

    map< int, double > prob_9d4_gte_x;
    map< int, double > prob_6d6_eq_x;

    for( int i = 36; i >= 6; --i )
    {
        prob_6d6_eq_x[ i ] = (double) hist6d6[ i ] / (double) norm6d6;
        hist9d4[ i ] += hist9d4[ i+1 ];
        prob_9d4_gte_x[ i ] = (double) hist9d4[ i ] / (double) norm9d4;
        cout << "Prob(6d6 = " << i << ") = " << prob_6d6_eq_x[ i ]
             << " Prob(9d4 >= " << i << ") = " << prob_9d4_gte_x[ i ] << endl;
    }

    double prob = 0.0;
    for( int i = 6; i <= 36; ++i )
    {
        prob += prob_6d6_eq_x[ i ] * prob_9d4_gte_x[ i+1 ];
    }

    cout << "Probability of 9d4 beating 6d6 = " << setprecision( 7 )
         << prob << endl;

    return 0;
}
