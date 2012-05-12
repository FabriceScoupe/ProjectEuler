#include <iostream>
using namespace std;

// Find the smallest pair of pentagonal numbers whose sum and
// difference is pentagonal.
// P(n) = n(3n-1)/2 (P(n+1)-P(n)=3n+1, recursion p:=p+n<<1+n+1)
// Find min |P(j)-P(k)| / P(j)+P(k)=P(s) and P(k)-P(j)=P(d)

// 3n^2-n-2p = 0 => n = (1+sqrt(1+24p))/6 must be integer > 0
//  " "  "  >= 0 => n >=  " " "
//
// P(n+1)-P(n) = 3n+1 so can use quick recursion p+=n<<1+n+1;++n
// j < k < s and d < k < s
// 
// P(j)+P(k)=P(s) and P(k)-P(j)=P(d):
// P(k)=P(d)+P(j) and P(s)=P(d)+2*P(j)
// Also: P(s)+P(d)=2P(k) => P(k) "in the middle" of P(d) and P(s)
// That is, P(k)-P(d)=P(s)-P(k)
// Also: P(s)-P(d)=2P(j) => P(j) "in the middle" of -P(d) and P(s)
// P(j)+P(d) = P(s)-P(j)
//
// Pick P(d) first: then look for j such P(j)+P(d)=P(k) and P(d)+2P(j)=P(s)
// P(d)+P(j)=P(k) with k >= d+1, k >= j+1, so P(k)>=P(d+1) and P(k)>=P(j+1)
// So: P(d)+P(j)>=P(d+1) so P(j) >= 3d+1, similarly P(d) >= 3j+1
//
// Given d, j such as 3d+1 <= P(j) and 3j+1 <= P(d)
// Check P(d)+P(j) is it P(k)?
// Check P(k)+P(j), is it P(s)?


int main( int argc, char** argv )
{
    int d = 1;
    long long pd = 1;
    long long min_pd = 1;
    int j = 1;
    int pj = 1;
    int min_j = 1;
    long long min_pj = 1;
    bool found = false;

    while (!found)
    {
        //cout << "Trying P(d=" << d << ")=" << pd << endl;
        // j must be such that P(j) >= 3d+1
        //int lower_bound = (d<<1)+d+1;
        int lower_bound = 3*d+1;
        while( pj < lower_bound )
        {
            //pj += (j<<1)+j+1;
            pj += 3*j+1;
            ++j;
        }
        min_j = j;
        min_pj = pj;
        //while( (j>>1)+j+1 <= pd )
        while( 3*j+1 <= pd )
        {
            //cout << "Trying P(j=" << j << ")=" << pj << endl;
            // Check P(j)+P(d) (P(k)?) and 2P(j)+P(d) (P(s)?)
            int k = ( d > j ? d : j );
            long long tmp_p = ( d > j ? pj : pd );
            // P(j)=P(k)-P(d) P(j)-(P(d+1)-P(d))=P(k)-P(d+1)
            // keep substracting until P(k) reached or overshot.
            while( tmp_p > 0 )
            {
                //tmp_p -= (k<<1)+k+1;
                tmp_p -= 3*k+1;
                ++k;
            }
            if ( 0 == tmp_p ) // Found P(k)=P(j)+P(d)
            {
                int s = k;
                long long tmp_pj = pj;
                long long tmp_ps = k*(3*k-1)/2;
                long long max_ps = tmp_ps<<(1-pd);
                // P(j) = P(s)-P(k) P(j)-(P(k+1)-P(k))=P(s)-P(k+1)
                // Keep substracting until P(s) reached or overshot
                while( ( tmp_pj > 0 ) && ( tmp_ps < max_ps ) )
                {
                    //tmp_ps  += (s<<1)+s+1;
                    //tmp_pj  -= (s<<1)+s+1;
                    tmp_ps  += 3*s+1;
                    tmp_pj  -= 3*s+1;
                    ++s;
                }
                if ( 0 == tmp_pj ) // Found P(s)=P(j)+P(j)+P(d)=P(j)+P(k)
                {
                    found = true;
                    min_pd = pd;
                    break;
                }
            }
            //pj += (j<<1)+j+1;
            pj += 3*j+1;
            ++j;
        }
        j = min_j;
        pj = min_pj;
        //pd += (d<<1)+d+1;
        pd += 3*d+1;
        ++d;
    }
    cout << endl << "min |Pk-Pj| = " << min_pd << endl;
}
