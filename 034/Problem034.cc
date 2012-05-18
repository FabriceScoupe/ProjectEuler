#include <iostream>
using namespace std;

/*
 * Project Euler: Problem 034 (http://projecteuler.net/problem=34)
 */

// Find sum of all numbers which are equal to the sum of the factorial of
// their digits (1! and 2! are not sums, so not included).
//
// 0!=1; 1!=1; 2!=2; 3!=6; 4!=24; 5!=120; 6!=720; 7!= 5040; 8!=40320; 9!=362880
// sum[k=0..n] Dk.10^k = sum[k=0..n] Dk! <= (n+1)(max(Dk))! <= (n+1)362880
// 8*362880 = 2903040 has 7 digits, 7*362880 = 2540160 ok, so 7 digits max
// 2+6*362880 = 2177282 => at most 2999999.
// Also see problem 30.
//
int fact( char d )
{
    int f = 1;
    switch(d)
    {
        case 2: f = 2; break;
        case 3: f = 6; break;
        case 4: f = 24; break;
        case 5: f = 120; break;
        case 6: f = 720; break;
        case 7: f = 5040; break;
        case 8: f = 40320; break;
        case 9: f = 362880; break;
        default: break;
    }
    return f;
}

// Returns max digit such as digit! has n digits or less
char max_digit( char nd )
{
    int m = 9;
    switch( nd )
    {
        case 1: m=3; break;
        case 2: m=4; break;
        case 3: m=6; break;
        case 4: m=7; break;
        case 5: m=8; break;
        // case 6: m=9; break;
        default: break;
    }
    return m;
}

int power10( char n )
{
    int p = 1;
    switch( n )
    {
        case 0: p = 1; break;
        case 1: p = 10; break;
        case 2: p = 100; break;
        case 3: p = 1000; break;
        case 4: p = 10000; break;
        case 5: p = 100000; break;
        case 6: p = 1000000; break;
        case 7: p = 10000000; break;
        case 8: p = 100000000; break;
        default: break;
    }
    return p;
}


// Brute-force
// Returns sum of n-digit numbers that are = sum of digit!
int sum_for_n_digits( char nd )
{
    int sum = 0;

    int max  = power10( nd ) - 1;
    int max2 = nd * fact( max_digit( nd ) );
    if ( max2 < max ) max = max2;

    int  n1 = power10( nd - 1 );
    int  n2 = nd; // Remember: 0! = 1
    char cp = 0;
    char cd = 0;

    while( ( cp < nd ) && ( n1 <= max ) )
    {
        //cout << "n1 = " << n1 << ", n2 = " << n2 << endl;

        if ( n1 == n2 ) // Bingo!
        {
            cout << "Found: " << n1 << endl;
            sum += n1;
        }

        // Go to next number
        cp = 0;
        cd = n1 % 10;
        while( ( max_digit(nd) == cd ) && ( cp < nd ) )
        {
            n2 -= fact( max_digit( nd ) ) - 1; // 0! = 1 so adjust
            n1 -= max_digit( nd )*power10( cp );
            cd = ( n1 / power10( cp+1 ) ) % 10;
            ++cp;
        }
        n2 += fact( cd + 1 ) - fact( cd );
        n1 += power10( cp );
    }

    return sum;
}

int main( int argc, char** argv )
{
    int sum = 0;
    //sum += sum_for_n_digits(1); // ignore, as 1! and 2! not sums
    sum += sum_for_n_digits(2);
    sum += sum_for_n_digits(3);
    sum += sum_for_n_digits(4);
    sum += sum_for_n_digits(5);
    sum += sum_for_n_digits(6);
    sum += sum_for_n_digits(7);
    cout << endl <<  "Answer: " << sum << endl << endl;
    return 0;
}
