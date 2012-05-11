#include <iostream>
#include <iomanip>
#include <cstdlib>
using namespace std;

// Sum of numbers on diagonals of spiral 1001 x 1001

// Closed formula: sum for spiral n x n (n odd) = sd(n)
// sd(1) = 1, sd(3) = sd(1) + 3 + 5 + 7 + 9 = 25 (4 corners)
// sd(5) = sd(3) + 25 + 21 + 17 + 13 = 101
// ...
// Odd and even recursions:
// ------------------------
// sd(n+2) = sd(n) + 4.(n+2)^2 - 6(n+1) 
//  = sd(n) + 4n^2 + 16n + 16 - 6n - 6 = sd(n) + 4n^2 + 10n + 10
//
// for n even sd(2) = 10
// sd(n+2) = sd(n) + 4n^2 + 10n + 10 = sd(n) + f(n)
// so sd(1)=1 sd(2)=10 sd(3)=sd(1)+f(1) sd(4)=sd(2)+f(2)
// sd(5)=sd(1)+f(1)+f(3) sd(6)=sd(2)+f(2)+f(4) ...
// 
// sum(k) for odd k up to n = 1 + 3 + 5 + ... n = so(n) (n odd)
// = (n+1)/2 + 0 + 2 + ... + n-1 = (n+1)/2 + se(n-1)
// but so(n) + se(n-1) = n.(n+1)/2 => so(n) = (n+1)^2/4,
// and se(n-1) = (n+1)(n-1)/4 => se(n) = n(n+2)/4
//
// sum(k^2) for odd k up to n = 1 + 9 + 25 + ... + n^2 = s2o(n)
// = 1+0 + 5+4 + 9+16 + 13+36 + ... +(2n-1)+(n-1)^2
// = 2.so(n)-(n+1)/2 + s2e(n-1) = n(n+1)/2 + s2e(n-1)
// but s2o(n) + s2e(n-1) = n(n+1)(2n+1)/6 => s2o(n) = n(n+1)(n+2)/6
// => s2e(n-1)= n(n-1)(n+1)/6 => se(n) = n(n+1)(n+2)/6
//
// sum(f(k)) for odd k up to n = sfo(n) = 4.s2o(n)+10so(n)+10(n+1)/2
// sfo(n) = 2n(n+1)(n+2)/3 + 5(n+1)^2/2 + 5(n+1)
//        = (n+1)/6.[4n(n+2)+15(n+1)+30]=(n+1).(4n^2+23n+45)/6
// sfe(n) = 2n(n+1)(n+2)/3 + 5n(n+2)/2 + 5n
//        = n/6.[4(n+1)(n+2)+15(n+2)+30]= n.(4n^2+27n+68)/6
//
// Closed forms for odd and even terms:
// ------------------------------------
// n odd : sd(n) = 1 + sfo(n-2) ; sd(n+2) = 1 + sfo(n)
// n even: sd(n) = 10 + sfe(n-2) ; sd(n+1) = 10 + sfe(n-1)
// 
// (n odd): sd(n+2)-sd(n+1)= -9 + sfo(n) - sfe(n-1)
// = -9 + 4(s2o(n)-s2e(n-1))+10(so(n)-se(n-1)+10
// = -9 + 2n(n+1) + 5(n+1) + 10
// sd(n)-sd(n-1) =  1 + 2(n-2)(n-1) + 5(n-1) = 1 + (n-1)(2n+1)
//               = 2n^2-n = n(2n-1)
//
// (n even): sd(n)-sd(n-1)= sd(n)-(sd(n-2)+sd(n-1)-sd(n-2))
// = sd(n) - sd(n-2) - (n-1)(2n-3)
// = 4(n-2)^2+10(n-2)+10 - 2n^2 + 5n - 3
// = 4n^2 - 16n + 16 + 10n - 20 + 10 - 2n^2 + 5n - 3
// = 2n^2 - n  + 3
// = n(2n-1) + 3
//
// Simpler recursion:
// ------------------
// => sd(0)=0 sd(n>0) = sd(n-1) + n*(2*n-1) + (n%2?0:3)
//
// So: "fully" closed formula?
// ---------------------------
// sum(k=1..n)[2n^2-n] = n(n+1)(2n+1)/3 - n(n+1)/2
// so: sd(n) = n(n+1)(4n-1)/6 + 3*(n-(n%2?1:0))/2

long long sfo( long long n ) { return( (4*n*n+23*n+45)*(n+1)/6 ); }
long long sfe( long long n ) { return( (4*n*n+27*n+68)*n/6 ); }

// Closed form (odd/even)
int closed_sum_diags( int n )
{
    return ( n % 2 != 0 ? 1  + sfo(n-2)
                        : 10 + sfe(n-2) );
}

// Fully closed form
long long fully_closed_sum_diags( long long n )
{
    return( (n*(n+1)*(4*n-1))/6 + 3*(n-(n%2?1:0))/2 );
}

// Simpler recursion
int rec_sum_diags( int n )
{
    int s = 0;
    for( int i = 1; i <= n; ++i )
        s += i * ( 2*i - 1 ) + ((i%2)?0:3);
    return s;
}

// Recursive (odd/even)
int sum_diags( int n )
{
    int s = ( n % 2 != 0 ? 1 : 10 );
    int i = ( n % 2 != 0 ? 1 : 2 );
    while( i < n )
    {
        s += 4*i*i + 10*i + 10;
        i += 2;
    }
    return s;
}


// Brute force...
void buildSpiral( int* spiral, int dim )
{
    int n  = dim * dim;
    // dim odd => start top-right corner, otherwise bottom-left one
    // dim odd => going left first, else going right first
    int x  = ( dim % 2 == 0 ? dim-1 : 0 );
    int y  = ( dim % 2 == 0 ? 0 : dim-1 );
    int dx = 0;
    int dy = ( dim % 2 == 0 ? +1 : -1 );
    while( n >= 1 )
    {
        spiral[ x * dim + y ] = n;
        --n;
        int tmp_x = x + dx;
        int tmp_y = y + dy;
        if ( ( tmp_x < 0 ) || ( tmp_x >= dim ) ||
             ( tmp_y < 0 ) || ( tmp_y >= dim ) ||
             ( spiral[ tmp_x * dim + tmp_y ] > 0 ) )
        {
            // Change direction
            // right(0,-1)->down(1,0)->left(0,1)->up(-1,0)
            tmp_x = -dy;
            tmp_y = dx;
            dx = tmp_x;
            dy = tmp_y;
        }
        x += dx;
        y += dy;
    }
}

int main( int argc, char** argv )
{
    int n = 1001;
    if ( argc > 1 ) n = atoi( argv[1] );
    int* spiral = new int[ n*n ];
    for( int i = 0; i < n*n; ++i ) spiral[i] = 0;
    buildSpiral( spiral, n );
    if ( n <= 10 )
    {
        for( int i = 0; i < n*n; ++i )
        {
            cout << setw(2) << spiral[i] << " ";
            if ( i % n == n-1 ) cout << endl;
        }
    }
    delete[] spiral;
    cout << "Sum of diagonals              = ";
    long long sum = 0;
    // Top-left to bottom-right
    for( int i = 0; i < n*n; i += n+1 ) sum += spiral[i];
    // Top-right to bottom-left, watch that bottom-right corner!
    for( int i = n-1; i < n*n-1; i+= n-1 ) sum += spiral[i]; 
    if ( ( n > 1 ) && ( n % 2 != 0 ) )
    {
        --sum;
    }
    cout << sum << endl;

    cout << "Check: sum_diags              = " << sum_diags(n) << endl;
    cout << "Check: closed_sum_diags       = " << closed_sum_diags(n) << endl;
    cout << "Check: rec_sum_diags          = " << rec_sum_diags(n) << endl;
    cout << "Check: fully_closed_sum_diags = " 
         << fully_closed_sum_diags(n) << endl;
}
