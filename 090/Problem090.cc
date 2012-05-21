#include <iostream>
#include <string>
#include <vector>

/*
 * Project Euler: Problem 090 (http://projecteuler.net/problem=90)
 */

// ============================================================================
// Two dice, each with distinct digits among [0..9].
// Must be able to display all squares 0 < x < 100, ie:
// 01, 04, 09, 16, 25, 36, 49, 64, 81.
// A 6 can become a 9.
// ============================================================================

using namespace std;

// Brute force...

inline bool find(char c, char a[])
{
    bool found = false;
    for(int i=0; (!found) && (c>=a[i]) && (i<6); ++i) found = (c == a[i]);
    return found;
}

inline bool check_constraints(char* a, char* b)
{
    return (
        ( (find(0,a)&&find(1,b))||(find(0,b)&&find(1,a)) ) &&
        ( (find(0,a)&&find(4,b))||(find(0,b)&&find(4,a)) ) &&
        ( (find(0,a)&&(find(6,b)||find(9,b)))||
          (find(0,b)&&(find(6,a)||find(9,a))) ) &&
        ( (find(1,a)&&(find(6,b)||find(9,b)))||
          (find(1,b)&&(find(6,a)||find(9,a))) ) &&
        ( (find(2,a)&&find(5,b))||(find(2,b)&&find(5,a)) ) &&
        ( (find(3,a)&&(find(6,b)||find(9,b)))||
          (find(3,b)&&(find(6,a)||find(9,a))) ) &&
        ( (find(4,a)&&(find(6,b)||find(9,b)))||
          (find(4,b)&&(find(6,a)||find(9,a))) ) &&
        ( (find(8,a)&&find(1,b))||(find(8,b)&&find(1,a)) ) );
}

int main(int argc, char** argv)
{
    char a[7] = {0,0,0,0,0,0,0};
    char b[7] = {0,0,0,0,0,0,0};

    // Generate possible dice
    vector<string> dv;
    for(a[0] = 0; a[0] <= 4; ++a[0])
        for(a[1] = a[0]+1; a[1] <= 5; ++a[1])
            for(a[2] = a[1]+1; a[2] <= 6; ++a[2])
                for(a[3] = a[2]+1; a[3] <= 7; ++a[3])
                    for(a[4] = a[3]+1; a[4] <= 8; ++a[4])
                        for(a[5] = a[4]+1; a[5] <= 9; ++a[5]) {
                            for(int i = 0; i < 6; ++i) b[i] = a[i]+'0';
                            //cout << b << endl;
                            dv.push_back(b);
                        }

   cout << dv.size() << " dice generated." << endl << endl;

   int count = 0;
   for(unsigned int i = 0; i < dv.size(); ++i) {
       for(unsigned int j = i; j < dv.size(); ++j) {
           for(int k = 0; k < 6; ++k) {
               a[k] = dv[i][k] - '0';
               b[k] = dv[j][k] - '0';
           }
           if (check_constraints(a,b)) {
               ++count;
               //cout << "Found: " << dv[i] << " / " << dv[j] << endl;
           }
       }
   }

   cout << endl << count << " combinations found." << endl;
   cout << "Answer: " << count << endl;
   return 0;
}
