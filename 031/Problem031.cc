#include <iostream>
#include <cstdlib>
#include <vector>
#include <map>
using namespace std;

// Number of ways of making £2 with any number of coins from set:
// {1p,2p,5p,10p,20p,50p,£1 and £2)

// Using brute-force: generating all possible partitions,
// putting them in a map to make sure we avoid repetitions!

typedef map< int, int > Partition;
typedef map< Partition, int > PartitionMap;
typedef map< int, vector< Partition > > DerivationMap;

// Keep deriving until all possibilities exhausted, then return size
// of partition map.
int derive( PartitionMap& pm, DerivationMap& dm )
{
    PartitionMap::iterator pmi;
    DerivationMap::reverse_iterator dmi;
    vector< Partition >::iterator vpi;
    Partition::iterator pi;

    for( dmi = dm.rbegin(); dmi != dm.rend(); ++dmi )
    {
        cout << "Considering derivations of " << dmi->first << endl;
        int count = pm.size();
        cout << count << " elements in partition map." << endl;
        for( vpi = (dmi->second).begin(); vpi!= (dmi->second).end(); ++vpi )
        {
            PartitionMap tmp_pm;
            for( pmi = pm.begin(); pmi != pm.end(); ++pmi )
            {
                Partition p = pmi->first;
                Partition::iterator pif = p.find( dmi->first );
                if ( pif != p.end() )
                {
                    int mul = pif->second;
                    while( mul > 0 )
                    {
                        --mul;
                        if ( mul > 0 )
                        {
                            pif->second = mul;
                        }
                        else
                        {
                            p.erase( pif );
                        }
                        for( pi = vpi->begin(); pi != vpi->end(); ++pi )
                        {
                            p[ pi->first ] += pi->second;
                        }
                        ++tmp_pm[ p ];
                    }
                }
            }
            for( pmi = tmp_pm.begin(); pmi != tmp_pm.end(); ++pmi )
            {
                pm[ pmi->first ] += pmi->second;
            }
        }
        cout << endl;
    }

    return pm.size();
}

int main( int argc, char** argv )
{
    // Initialise partition map
    Partition p0;
    p0[200] = 1;
    PartitionMap pm;
    pm[p0] = 1;

    // Build derivation map
    DerivationMap dm;
    Partition p;
    p[100]=2;
    dm[200].push_back(p);
    p.clear();
    p[50]=2;
    dm[100].push_back(p);
    p.clear();
    p[20]=5;
    dm[100].push_back(p);
    p.clear();
    p[20]=2; p[10]=1;
    dm[50].push_back(p);
    p.clear();
    p[10]=2;
    dm[20].push_back(p);
    p.clear();
    p[5]=2;
    dm[10].push_back(p);
    p.clear();
    p[2]=5;
    dm[10].push_back(p);
    p.clear();
    p[2]=2; p[1]=1;
    dm[5].push_back(p);
    p.clear();
    p[1]=2;
    dm[2].push_back(p);

    // Check derivation map
    for( DerivationMap::iterator i = dm.begin(); i != dm.end(); ++i )
    {
        cout << i->first << " = ";
        for( vector<Partition>::iterator j = i->second.begin();
             j != i->second.end(); ++j )
        {
            for( Partition::iterator k = j->begin(); k != j->end(); ++k )
            {
                cout << k->second << " x " << k->first << "p ";
            }
            cout << "; ";
        }
        cout << endl;
    }

    int np = derive( pm, dm );
    for( PartitionMap::iterator i = pm.begin(); i != pm.end(); ++i )
    {
        Partition p = i->first;
        for( Partition::iterator j = p.begin(); j!= p.end(); ++j )
        {
            if (j->second > 0) cout << j->second << " x " << j->first << "p ";
        }
        cout << " (" << i->second << " times)" << endl;
    }

    cout << "Total number of partitions: " << np << endl;
}
