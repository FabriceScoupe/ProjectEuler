#include <iostream>
#include <cstdlib>
using namespace std;

// Finding the n-th digit of the fractional part of the irrational
// number whose decimal fraction is created by concatenating the
// positive integers: 0.1234567891011121314151617...
//
// 9 one-digit integers contribute first 9 digits (1 to 9)
// 100-10=90 2-digit integers contribute next 180 digits (10 to 189)
// 1000-100=900 3-digit integers ... next 2700 digits (190 to 2889)
// 9000 4-digit numbers ... next 36000 digits (2890 to 38889)
// 90000 5-digit numbers ... 450000 digits (38890 to 488889)
// 900000 6-digit numbers ... 5400000 digits (488890 to 5888889)

char d( int n )
{
    int nd = 1;
    int nn = 9;
    int max_n = 9;
    int pw10 = 1;
    while( n > max_n )
    {
        ++nd;
        pw10 *= 10;
        nn *= 10;
        max_n += nd*nn;
    }
    int min_n = max_n - nd*nn + 1;
    int i = ( ( n - min_n ) / nd ) + pw10;
    char wd = nd - (( n - min_n ) % nd ); // which digit of i?
    char result;
    do
    {
        result = i % 10;
        i /= 10;
        --wd;
    }
    while( wd > 0 );
    return result;
}


int main( int argc, char** argv )
{
    cout << "Test: d(12) = " << (int) d(12) << endl;
    cout << "d(1) = " << (int) d(1) << endl;
    cout << "d(10) = " << (int) d(10) << endl;
    cout << "d(100) = " << (int) d(100) << endl;
    cout << "d(1000) = " << (int) d(1000) << endl;
    cout << "d(10000) = " << (int) d(10000) << endl;
    cout << "d(100000) = " << (int) d(100000) << endl;
    cout << "d(100000) = " << (int) d(100000) << endl;
    int prod = d(1)*d(10)*d(100)*d(1000)*d(10000)*d(100000)*d(1000000);
    cout << endl << "Product = " << prod << endl;
}
