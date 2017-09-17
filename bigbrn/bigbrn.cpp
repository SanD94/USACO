/*
ID: safaand1
LANG: C++11
PROG: bigbrn
*/

#include<iostream>
#include<cstdio>

using namespace std;

#define MAXN 1010

int main(int argc, char const* argv[]) {
    freopen("bigbrn.in", "r", stdin);
    freopen("bigbrn.out", "w", stdout);

    int n, t;
    cin >> n >> t;
    int dyn[MAXN][MAXN] = {};
    bool map[MAXN][MAXN] = {};
    for(int i=0;i<t;i++) {
        int x, y;
        cin >> x >> y;
        map[x][y] = true;
    }
    int res = 0;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++) {
            if (map[i][j]) continue;
            dyn[i][j] = min(min(dyn[i-1][j], dyn[i][j-1]), dyn[i-1][j-1]) + 1;
            res = max(dyn[i][j], res);
        }
    cout << res << endl;
    return 0;
}
