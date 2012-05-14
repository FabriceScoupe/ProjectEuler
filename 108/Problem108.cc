#include <iostream>
#include <cstdlib>
#include <vector>
#include <map>

using namespace std;

/***
In the following equation, x, y and n are positive integers:
1/x + 1/y = 1/n
For n = 4, there are exactly three distinct solutions:
1/5+1/20=1/4
1/6+1/12=1/4
1/8+1/8 =1/4
What is the least value of n for which the number of distinct
solutions exceeds one-thousand ?

(Linked to problem 110, but easier, so do this one first!
***/

// x > n and y > n
// Start from x = n + 1, up to x = 2*n
// 1/y = 1/n - 1/x = (x-n)/(n.x) or y = n.x / ( x - n )
// y solution if n*x % ( x - n ) == 0.
// n+1 <= x <= n or 1 <= k <= n test on k | n*(n+k)
// if k divisor of n or k divisor of (n+k)=> y solution.
// k divisor of n^2 and 1 <= k <= n
// Prime factor decomposition: n = Prod[k] Pk^mk
// Number of divisors of n = Prod[k](1+mk)
// Number of divisors of n^2 = Prod[k](1+2.mk)
// 
// Sol is 180180 = 2*2*3*3*5*7*11*13
// nd(180180^2)=5*5*3*3*3*3=2025   (nd()+1)/2 -> 1013
static vector<long long> primes;

int decomp( long long n, map<long long, int>& dm )
{
    dm.clear();
    vector<long long>::iterator it = primes.begin();
    long long m = n;
    while((m > 1) && (it != primes.end())) {
        while(m % (*it) == 0) {
            m /= (*it);
            dm[ *it ]++;
        }
        ++it;
    }
    int nd = 1;
    if (dm.empty()) {
        primes.push_back( n );
        dm[ n ]++;
    }
    for(map<long long, int>::iterator i = dm.begin(); i != dm.end(); ++i) {
        nd *= 1 + 2*i->second;
    }
    nd = ( nd + 1 ) / 2;
    // Returns: (numdivs(n^2)+1)/2
    return nd;
}

int main( int argc, char** argv )
{
    int limit = 1000;
    if ( argc > 1 ) limit = atoi( argv[ 1 ] );
    long long n = 1;
    int count = 0;
    primes.push_back( 2 );
    while(count <= limit) {
        ++n;
        if (n % 1000 == 0) { cout << '.'; flush( cout ); }
        count = 0;
        /**
        cout << "Testing n = " << n << ":" << endl;
        for( long long x = n+1; x <= 2*n; ++x )
        {
            long long y = n*x / ( x - n );
            if ( n*x % ( x - n ) == 0 )
            {
                ++count;
                cout <<"1/"<<x<<"+1/"<<y<<"=1/"<<n<<endl;
            }
        }
        cout << "Found "<<count<<" solutions for n = "<< n << endl;
        **/
        map<long long, int> m;
        count = decomp( n, m );
        //cout << "Calculated # of solutions for n = " << n << ": "
        //     << count << endl << endl; 
    }
    cout << endl << "Answer: " << n << endl;
    return 0;
}
