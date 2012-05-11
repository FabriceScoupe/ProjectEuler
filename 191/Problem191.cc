#include <iostream>
#include <cstdlib>
#include <vector>

using namespace std;

/***
 * A particular school offers cash rewards to children with good attendance
 * and punctuality. If they are absent for three consecutive days or late on
 * more than one occasion then they forfeit their prize.
 *
 * During an n-day period a trinary string is formed for each child consisting
 * of L's (late), O's (on time), and A's (absent).
 *
 * Although there are eighty-one trinary strings for a 4-day period that can be
 * formed, exactly forty-three strings would lead to a prize:
 *
 * OOOO OOOA OOOL OOAO OOAA OOAL OOLO OOLA OAOO OAOA
 * OAOL OAAO OAAL OALO OALA OLOO OLOA OLAO OLAA AOOO
 * AOOA AOOL AOAO AOAA AOAL AOLO AOLA AAOO AAOA AAOL
 * AALO AALA ALOO ALOA ALAO ALAA LOOO LOOA LOAO LOAA
 * LAOO LAOA LAAO
 *
 * How many "prize" strings exist over a 30-day period?
 *
 ***/

// By recursion!
//
// For 1: O A L
// nps(1) = 3, nwl(1) = 1, nax(1) = 1, naa(1) = 0
// For 2: OO OA OL AO AA AL LO LA
// nps(2) = 8, nwl(2)=4 nax(2)=2 naa(2)=1
// For 3: OOO OOA OOL OAO OAA OAL OLO OLA AOO AOA
//        AOL AAO AAL ALO ALA LOO LOA LAO LAA
//
// nps(3) = 19
// nwl(3) = 12
// nax(3) = 5
// naa(3) = 2
//
int main(int argc, char** argv)
{
    int n = 30;
    if (argc > 1) n = atoi(argv[1]);

    vector<long> nps(n); // Number of prize strings
    vector<long> naa(n); // Number of strings starting with AA
    vector<long> nax(n); // Number of strings starting with AO or AL
    vector<long> naxwl(n); // # of strings with a L and starting with AO or AL
    vector<long> nwl(n); // Number of strings with a L
    vector<long> naawl(n); // # of strings with a L and starting with AA

    nps[0]   = 3; // O, A, L
    nax[0]   = 1;
    naxwl[0] = 0;
    naa[0]   = 0;
    nwl[0]   = 1;
    naawl[0] = 0;

    for(int i = 1; i < n; ++i) {
        /**
        nps[i] =  nps[i-1]-nwl[i-1]; // Add L only to  no-L strings
        nps[i] += nps[i-1];          // Add O to all strings
        nps[i] += nps[i-1]-naa[i-1]; // Add A only to non-AA strings
        **/
        nps[i] = 3*nps[i-1]-nwl[i-1]-naa[i-1];

        // Adding A to a string with no AX or no AA => make a A
        nax[i] = /*A+*/ nps[i-1]-nax[i-1]-naa[i-1];
        naxwl[i] = nwl[i-1]-naxwl[i-1]-naawl[i-1];

        naa[i] =  /*A+*/ nax[i-1];
        naawl[i] = naxwl[i-1];

        /**
        nwl[i] =  nps[i-1]-nwl[i-1];  // L added to no-L strings
               += nwl[i-1];           // O added to with-L strings
               += nwl[i-1]-naawl[i-1] // A added to with-L non AA strings
        **/
        nwl[i] = nps[i-1]+nwl[i-1]-naawl[i-1];

        /**
        cout <<i+1<<":\tnps="<<nps[i]<<"\tnax="<<nax[i]
                  <<"\tnaa="<<naa[i]<<"\tnwl="<<nwl[i]<<endl;
        **/
    }

    cout << "Number of " << n << "-long prize strings = " << nps[n-1] << endl;
}
