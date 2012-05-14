#include <iostream>
#include <map>
using namespace std;

/*
 * The most naive way of computing n^15 requires fourteen multiplications:
 * n * n * ... * n = n^15
 * Using a "binary" method you can compute in six multiplications:
 * n * n = n^2
 * n^2*n^2 = n^4
 * n^4*n^4 = n^8
 * n^8*n^4 = n^12
 * n^12*n^2 = n^14
 * n^14*n = n^15
 *
 * However it is yet possible to compute it in only five multiplications:
 * n*n = n^2
 * n^2*n = n^3
 * n^3*n^3 = n^6
 * n^6*n^6 = n^12
 * n^12*n^3 = n^15
 *
 * We shall define m(k) to be the minimum number of multiplications to
 * compute n^k; for example, m(15) = 5.
 *
 * For 1 <= k <= 200; find sum of m(k).
 */

// Building a tree

struct Node {
    Node(Node* p, int v) : parent(p), next(0), value(v) { };
    Node* parent;
    Node* next;
    int value;
};

int main(int argc, char** argv)
{
    int m[201];
    for(int i = 1; i <= 200; ++i) m[i] = 0;

    map<int, Node*> level;
    level[0] = new Node(0, 1);
    level[1] = new Node(level[0], 2);

    int count = 1;
    int depth = 1;
    int nodes = 2;

    Node* n = level[depth];
    while (count < 200) {
        int val = n->value;
        if ((val <= 200) && (0 == m[val])) {
            ++count;
            m[val] = depth;
            int zm = 0;
            for(int i = 2; (0 == zm) && (i <= 200); ++i) {
                if (m[i] == 0) zm = i;
            }
/*
            cout << "m(" << val << ") = " << depth 
                 << " count(" << count << ") "
                 << " nodes(" << nodes << ") "
                 << " missing(" << zm << ")" << endl;
*/
        }
        // Calculate children
        for(Node* p = n; p != 0; p = p->parent) {
            int pv = val + p->value;
            if ((pv <= 200) && (m[pv] == 0)) {
                Node* c = new Node(n, pv);
                ++nodes;
                if (level[depth+1]) c->next = level[depth+1];
                level[depth+1] = c;
            }
        }

        // Go to next node at same depth, else go deeper
        if (n->next) {
            n = n->next;
        } else {
            ++depth;
            n = level[depth];
        }
    }
    int sum = 0;
    for(int i = 1; i <= 200; ++i) sum += m[i];
    cout << "sum(k=1..200) m(k) = " << sum << endl;
}
