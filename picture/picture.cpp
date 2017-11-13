/*
ID: safaand1
PROG: picture
LANG: C++11
*/

#include<iostream>
#include<cstdio>
#include<algorithm>

using namespace std;

#define MAX_RECT 5010

struct Rectangle {
    int x_min;
    int x_max;
    int y_min;
    int y_max;
};

int N, num_rect;
Rectangle rects[MAX_RECT];

int cmp(Rectangle a, Rectangle b) {
    if (a.x_min == b.x_min) return a.x_max < b.x_max;
    return a.x_min < b.x_min;
}

void swap_val(int &a, int &b) {
    a ^= b; b ^= a; a ^= b;
}

void swap() {
    for(int i=0;i<N;i++) {
        Rectangle &cur = rects[i];
        swap_val(cur.x_min, cur.y_min);
        swap_val(cur.x_max, cur.y_max);
    }
}

int scan(int cur) {
    bool found = false;
    int count = 0;
    int pass = -100000;
    for(int i=0;i<N;i++) {
        if (rects[i].y_min > cur || rects[i].y_max <= cur) continue;

        if (pass < rects[i].x_min) count++;
        pass = max(pass, rects[i].x_max);
    }
    return 2*count;
}


int main(int argc, char const* argv[]) {
    freopen("picture.in", "r", stdin);
    freopen("picture.out", "w", stdout);
    cin >> N;
    for(int i=0;i<N;i++)
        cin >> rects[i].x_min >> rects[i].y_min
            >> rects[i].x_max >> rects[i].y_max;

    int res = 0;
    sort(rects, rects+N, cmp);
    for(int i=-10000;i<=10000;i++)
        res += scan(i);
    swap();
    sort(rects, rects+N, cmp);
    for(int i=-10000;i<=10000;i++)
        res += scan(i);

    cout << res << endl;
    return 0;
}
