#include <iostream>
#include <cstdlib>
#include <set>
#include <map>

using namespace std;

/*
 * The minimum number of cubes to cover every visible face on a cuboid
 * measuring 3 x 2 x 1 is 22.
 *
 * If we add a second layer to this solid it would require 46 cubes to 
 * cover every visible face, the third layer would require 76 cubes, and the
 * fourth layer would require one hundred and eighteen cubes to cover every
 * visible face.
 *
 * However, the first layer on a cuboid measuring 5 x 1 x 1 also requires 22
 * cubes; similarly the first layer on cuboids measuring 5 x 3 x 1, 7 x 2 x 1,
 * and 11 x 1 x 1 all contain 46 cubes.
 *
 * We shall define C(n) to represent the number of cuboids that contain n
 * cubes in one of its layers.
 * So C(22)=2, C(46)=4, C(78)=5 and C(118)=8.
 * It turns out that 154 is the least value of n for which C(n)=10.
 * Find the least value of n for which C(n)=1000.
 */
struct Point
{
    Point(int xx, int yy, int zz) : x(xx), y(yy), z(zz) { }
    int x, y, z;
};

bool operator< (const Point& l, const Point& r)
{
    return(l.x == r.x ? l.y == r.y ? l.z < r.z : l.y < r.y : l.x < r.x);
}

// Make cuboid of dimensions a x b x c
void makeCuboid(set<Point>& cub, int a, int b, int c)
{
    cub.clear();
    for(int x = 0; x < a; ++x) {
        for(int y = 0; y < b; ++y) {
            for(int z = 0; z < c; ++z) {
                cub.insert(Point(x,y,z));
            }
        }
    }
}

// Add layer, returns number of cubes added
int addLayer(set<Point>& cub)
{
    set<Point> l;
    for(set<Point>::iterator e = cub.begin(); e != cub.end(); ++e) {
        int x = e->x;
        int y = e->y;
        int z = e->z;
        if (cub.find(Point(x-1, y, z)) == cub.end()) l.insert(Point(x-1, y, z));
        if (cub.find(Point(x+1, y, z)) == cub.end()) l.insert(Point(x+1, y, z));
        if (cub.find(Point(x, y-1, z)) == cub.end()) l.insert(Point(x, y-1, z));
        if (cub.find(Point(x, y+1, z)) == cub.end()) l.insert(Point(x, y+1, z));
        if (cub.find(Point(x, y, z-1)) == cub.end()) l.insert(Point(x, y, z-1));
        if (cub.find(Point(x, y, z+1)) == cub.end()) l.insert(Point(x, y, z+1));
    }
    for(set<Point>::iterator e = l.begin(); e != l.end(); ++e) {
        cub.insert(*e);
    }
    return l.size();
}

int main(int argc, char* argv[])
{
    int a = 1;
    if (argc > 1) a = atoi(argv[1]);
    int b = 1;
    if (argc > 2) b = atoi(argv[2]);
    int c = 1;
    if (argc > 3) c = atoi(argv[3]);
    set<Point> cub;
    makeCuboid(cub, a, b, c);
    for(int i = 0; i < 20; ++i) {
        int l = addLayer(cub);
        cout << "Layer: " << l << " Now: " << cub.size() << endl;
    }
    return 0;
}
