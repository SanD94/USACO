/*
ID: safaand1
LANG: C++11
PROG: tour
*/

#include<iostream>
#include<cstdio>

using namespace std;

int n, m;
string cities[101];
bool flights[101][101];
int dir[101];
int dyn[101][101];

int get_index(string city) {
    for(int i=0;i<n;i++)
        if (city.compare(cities[i]) == 0) return i;
    return -1;
}

int eval() {
    dyn[0][0] = 1;
    for(int i=0;i<n;i++)
        for(int j=i+1;j<n;j++)
            for(int k=0;k<j;k++)
                if (flights[k][j] && dyn[i][k]) {
                    dyn[i][j] = max(dyn[i][j], dyn[i][k]+1);
                    dyn[j][i] = dyn[i][j];
                }
    int res = 1;
    for(int i=0;i<n;i++) if (dyn[i][n-1] && flights[i][n-1]) res = max(res, dyn[i][n-1]);
    return res;
}

int main(int argc, char const* argv[]) {
    //freopen("tour.in", "r", stdin);
    //freopen("tour.out", "w", stdout);
    cin >> n >> m;
    for(int i=0;i<n;i++) cin >> cities[i];
    for(int i=0;i<m;i++) {
        string a, b;
        cin >> a >> b;
        int a_index = get_index(a);
        int b_index = get_index(b);
        flights[a_index][b_index] = flights[b_index][a_index] = true;
    }
    cout << eval() << endl;
    return 0;
}
