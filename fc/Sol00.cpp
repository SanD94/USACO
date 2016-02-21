/*
ID: safaand1
PROG: fc
LANG: C++11
*/

#include <cstdio>
#include <cstdlib>
#include <algorithm>

using namespace std;

struct point {
    double x,y;
    double angle;
    bool operator <(const point& p) const {
	return this->angle < p.angle;
    }	
};

int N;
point slots[10010];
int hull[10010];

double cross(point o, point a, point b){
    return (a.x - o.x) * (b.y - o.y) - (b.x - o.x) * (a.y - o.y);
}

double eval(point a, point b){
    return sqrt(pow(a.x-b.x, 2) + pow(a.y-b.y, 2));
}

void swap(point &a, point &b){
    point temp = a;
    a = b;
    b = temp;
}

int main(){
    freopen("fc.in", "r", stdin);
    freopen("fc.out", "w", stdout);
    scanf("%d", &N);
    for(int i=1;i<=N;i++)
	scanf("%lf %lf", &slots[i].x, &slots[i].y);
    for(int i=1;i<=N;i++)
	if(slots[i].y < slots[1].y )
	    swap(slots[1], slots[i]);
    for(int i=1;i<=N;i++)
	slots[i].angle = atan2(slots[i].y - slots[1].y, slots[i].x - slots[1].x);
    sort(slots+1, slots+N+1);

    slots[0] = slots[N];
    int M = 1;
    for(int i=2;i<=N;i++){
	while(cross(slots[M-1], slots[M], slots[i]) <= 0){
	    if(M > 1) M--;
	    else if(i == N) break;
	    else i++;
	}
	swap(slots[++M],slots[i]);
    }
    
    double res = 0;
    for(int i=0;i<M;i++)
	res += eval(slots[i], slots[i+1]);
    printf("%.2lf\n", res);
    return 0;
}

