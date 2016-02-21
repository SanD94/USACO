/*
ID: safaand1
PROG: fc
LANG: C++11
*/

#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <algorithm>

using namespace std;


struct points{
    double x;
    double y;
    
    bool operator <(const points &p) const {
	return x < p.x || (x == p.x && y < p.y);
    }
};

points spots[10010];
points hull[20010];
int N, hullpos;

double cross(points o, points a, points b){
    return (a.x - o.x) * (b.y - o.y) - (a.y - o.y) * (b.x - o.x);
}

double calc(points a, points b){
    return sqrt(pow(a.x-b.x, 2) + pow(a.y-b.y, 2));
}

int main(){
    freopen("fc.in", "r", stdin);
    freopen("fc.out", "w", stdout);
    scanf("%d", &N);
    for(int i=0;i<N;i++)
	scanf("%lf %lf", &spots[i].x, &spots[i].y);
    sort(spots, spots+N);
    for(int i=0;i<N;i++) {
	while( hullpos >= 2 &&
	       	cross(hull[hullpos-2], hull[hullpos-1], spots[i]) <= 0)
	    hullpos--;
	hull[hullpos++] = spots[i];
    }

    for(int i=N-1, t=hullpos+1; i>=0; i--){
	while (hullpos >= t &&
		cross(hull[hullpos-2], hull[hullpos-1], spots[i]) <= 0)
	    hullpos--;
	hull[hullpos++] = spots[i];
    }
    double res = 0;
    for(int i=0;i<hullpos-1;i++)
	res += calc(hull[i], hull[i+1]);
    printf("%.2lf\n", res);
    return 0;
}

