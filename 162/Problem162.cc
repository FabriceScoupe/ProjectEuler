#include <iostream>
#include <iomanip>
#include <cstdlib>
using namespace std;

/*
 * Project Euler: Problem 162 (http://projecteuler.net/problem=162)
 */

// Total number of 16-digits hex numbers: 16^16 (including leading 0s)
// Total number of 16-digits without any 0,1 or A: 13^16
// => Numbers with 

int main(int argc, char* argv[])
{
    int max_n = 16;
    if (argc > 1) max_n = atoi(argv[1]);
    unsigned long long count = 0ULL;

    cout << "Answer: " << uppercase << hex << count << endl;
    return 0;
}
