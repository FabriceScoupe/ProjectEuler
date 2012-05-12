#include <iostream>
using namespace std;

// Find the sum of all numbers that can be written as the sum of
// fifth powers of their digits.
//
// 0, 1, 32, 243, 1024, 3125, 7776, 16807, 32768, 59049
// integer N = sum[k=0..n] digit(k)*10^k = sum[k=0..n] digit(k)^5
// upper bound: N <= (n+1)*(9^5) <=> N <= 59049*(n+1)
// also (min digit)^5 <= N <= (n+1)(max digit)^5
// so (min digit)^5 cannot have more digits than N.
// 6*59049 = 354294 has 6 digits (n=5) so N <= 354294
// 
// lower bound: if N has x digits, only digit d such as d^5 has x or less
// digits can be considered
// 1 digit : only 0 or 1 N = { 0, 1 }
// 2 digits: only 0,1,2 but 2^5=32 starts with 3 so N = { }
// 3 digits: only 0..3, 3^4 numbers to test if brute force
// 4 digits: 0..7, 7^5 numbers by brute force
// 5 digits: 0..9, 9^5 " "
// 6 digits: 0..9, between 100000 and 354294, 254295 numbers to test
//

int power5( char d )
{
    int p = 0;
    switch( d )
    {
        case 0: p = 0; break;
        case 1: p = 1; break;
        case 2: p = 32; break;
        case 3: p = 243; break;
        case 4: p = 1024; break;
        case 5: p = 3125; break;
        case 6: p = 7776; break;
        case 7: p = 16807; break;
        case 8: p = 32768; break;
        case 9: p = 59049; break;

        default: break;
    }
    return p;
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
        default: break;
    }
    return p;
}

// Returns max digit such as digit^5 has n digits or less
char max_digit( char n )
{
    char m = 9;
    switch( n )
    {
        case 1:  m = 1; break;
        case 2:  m = 2; break;
        case 3:  m = 3; break;
        case 4:  m = 6; break;
        default: m = 9; break;
    }
    return m;
}

// Brute-force-ish!
// Returns sum of n-digit numbers that are = sum of digits^5
int sum_for_n_digits( char nd )
{
    int sum = 0;

    int max  = power10( nd ) - 1;
    int max2 = nd * power5( max_digit( nd ) );
    if ( max2 < max ) max = max2;

    int  n1 = power10( nd - 1 );
    int  n2 = 1;
    char cp = 0;
    char cd = 0;

    while( ( cp < nd ) && ( n1 <= max ) )
    {
        //cout << "n1 = " << n1 << ", n2 = " << n2 << endl;

        if ( n1 == n2 ) // Bingo!
        {
            //cout << "Found: " << n1 << endl;
            sum += n1;
        }

        // Go to next number
        cp = 0;
        cd = n1 % 10;
        while( ( max_digit(nd) == cd ) && ( cp < nd ) )
        {
            n2 -= power5( max_digit( nd ) );
            n1 -= max_digit( nd )*power10( cp );
            cd = ( n1 / power10( cp+1 ) ) % 10;
            ++cp;
        }
        n2 += power5( cd + 1 ) - power5( cd );
        n1 += power10( cp );
    }

    return sum;
}

int calls_to_sum_rec = 0; // Just for measurements

// Recursive
int sum_for_n_digits_rec( char nd, int& nfound, int offset = 0, char md = 0 )
{
    ++calls_to_sum_rec;

    int  sum   = 0;
    char max_d = ( md > 0 ? md : max_digit( nd ) );
    char min_d = ( md > 0 ? 0 : 1 );

    nfound = 0;

    if ( nd > 1 )
    {
        for( char d = min_d; d <= max_d; ++d )
        {
            int off = offset + d * power10( nd-1 ) - power5( d );

            int nf = 0;
            int s  = sum_for_n_digits_rec( nd-1, nf, off, max_d );
            sum += d*power10( nd-1 )*nf + s;
            nfound += nf;
            /*
            if ( nf > 0 )
                cout << "Found, digit(" << nd-1 <<") = " << (int) d << endl;
            */
        }
    }
    else
    {
        for( char d = min_d; d <= max_d; ++d )
        {
            if ( power5( d ) == offset + d )
            {
                sum += d;
                ++nfound;
                //cout << "Found, digit(" << nd-1 <<") = " << (int) d << endl;
            }
            else if ( power5( d ) - d > offset )
            {
                break;
            }
        } 
    }

    return sum;
}


int main( int argc, char** argv )
{
    int sum = 0;
    //sum += sum_for_n_digits(1); // ignore, as 1^5 not a sum.
    sum += sum_for_n_digits(2);
    sum += sum_for_n_digits(3);
    sum += sum_for_n_digits(4);
    sum += sum_for_n_digits(5);
    sum += sum_for_n_digits(6);
    cout << endl <<  "Sum = " << sum << endl << endl;

    int nfound = 0;
    sum = 0;
    //sum += sum_for_n_digits_rec(1, nfound); // Same as above
    sum += sum_for_n_digits_rec(2, nfound);
    sum += sum_for_n_digits_rec(3, nfound);
    sum += sum_for_n_digits_rec(4, nfound);
    sum += sum_for_n_digits_rec(5, nfound);
    sum += sum_for_n_digits_rec(6, nfound);
    cout << "Recursive sum = " << sum << endl;
    cout << "Calls to sum_for_n_digits_rec = " << calls_to_sum_rec << endl;
}
