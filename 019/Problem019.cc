#include <iostream>
#include <cstdlib>
using namespace std;

// How many Sundays fell on the first of the month during the 20th century,
// ie between 1 Jan 1901 and 31 Dec 2000?
// Calibration: 1 Jan 1900 -> Monday
// Apr, Jun, Sep, Nov 30 days
// Leap years: if ( y % 4 == 0 ) && ( ( y % 100 != 0 ) || ( y % 400 == 0 ) )
//

const char* dayNames[] = {
    "Monday", "Tuesday", "Wednesday", "Thursday",
    "Friday", "Saturday", "Sunday"
};

const char* monthNames[] = {
    "January", "February", "March", "April", "May", "June",
    "July", "August", "September", "October", "November", "December"
};

// Number of days elapsed since 1/1/1900 given date (day,month,year)
// day from 1..31, month 1..12, year 1900..2000
int weekDay( int d, int m, int y )
{
    // Calculate number of day since 1 Jan 1900
    int numDays = 0;
    int tmp_m = 1;
    int tmp_y = 1900;
    while( (100*tmp_y + tmp_m) < (100*y+m) )
    {
        bool leap = ( tmp_y % 4 == 0 ) &&
                    ( ( tmp_y % 100 != 0 ) || ( tmp_y % 400 == 0 ) );
        if ( tmp_m == 2 )
        {
            numDays += ( leap ? 29 : 28 );
        }
        else if ( ( tmp_m == 4 ) ||
                  ( tmp_m == 6 ) ||
                  ( tmp_m == 9 ) || 
                  ( tmp_m == 11 ) )
        {
            numDays += 30;
        }
        else
        {
            numDays += 31;
        }
        ++tmp_m;
        if ( tmp_m > 12 )
        {
            tmp_m = 1;
            ++tmp_y;
        }
    }
    numDays += d-1;
    return numDays;
}

int main( int argc, char** argv )
{
    int d = 1;
    int m = 1;
    int y = 1901;
    if ( argc > 1 ) d = atoi( argv[1] );
    if ( argc > 2 ) m = atoi( argv[2] );
    if ( argc > 3 ) y = atoi( argv[3] );

    cout << d << " " << monthNames[m-1] << " " << y << " = "
         << dayNames[ weekDay( d, m, y ) % 7 ] << endl;

    int count = 0;
    for( y = 1901; y <= 2000; ++y )
        for( m = 1; m <= 12; ++m )
            if ( ( weekDay( 1, m, y ) % 7 ) == 6 )
            {
                ++count;
                cout << '.';
            }
    cout << endl;
    cout << "Number of Sundays on 1st of month in 20th C = " << count << endl;
}
