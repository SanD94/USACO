/*
ID: safaand1
PROG: snail
LANG: C++11
*/

#include <cstdio>
#include <cstring>
#include <iostream>

using namespace std;

int N,n;
int B, res;
int map[150][150];
int dir[4][2] = {{0,1}, {1,0}, {0,-1}, {-1,0}};
char c;


bool is_good(int x, int y) {
    return (x >= 0 && x < N) && (y >= 0 && y < N);
}

int DFS(int x, int y, int d, int step) {
    int nx = x + dir[d][0];
    int ny = y + dir[d][1];
    int cur_step = 0;

    while(is_good(nx, ny) && !map[nx][ny]) {
        cur_step++;
        map[nx][ny] = 2;
        x = nx; nx += dir[d][0];
        y = ny; ny += dir[d][1];
    }

    if (cur_step && (!is_good(nx,ny) || map[nx][ny] == 1)) {
        DFS(x, y, (d+1)%4, step+cur_step);
        DFS(x, y, (d+3)%4, step+cur_step);
    } else res = max(res, step+cur_step);

    d = (d+2)%4;
    nx = x; ny = y;
    while(cur_step--) {
        map[nx][ny] = 0;
        nx += dir[d][0]; ny += dir[d][1];
    }
}

int main(){
    freopen("snail.in", "r", stdin);
    freopen("snail.out", "w", stdout);
    scanf("%d %d", &N, &B);
    for(int i=0;i<B;i++){
        scanf(" %c%d ",&c,&n);
        c-='A'; n--;
        map[n][c] = 1;
    }
    map[0][0] = 2;
    DFS(0,0,0,1);
    DFS(0,0,1,1);
    printf("%d\n", res);
    return 0;
}

