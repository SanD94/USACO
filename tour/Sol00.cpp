#include<iostream>
#include<cstdio>

using namespace std;

int n, m;
bool flights[101][101];
int dyn[101][101];
string cities[101];

int find_index(string city) {
    for(int i=0;i<n;i++)
        if (city.compare(cities[i]) == 0) return i;
    return -1;
}

int eval(int a, int b) {
    if ( a > b ) { a^=b; b^=a; a^=b; }
    if (dyn[a][b]) return dyn[a][b];
    if (a == b && a == n-1) return 0;
    if (a == b && a != 0) return -100;
    for(int i=a+1;i<n;i++)
        if(flights[a][i]) dyn[a][b]  = max(dyn[a][b], 1 + eval(i, b));
    return dyn[a][b];
}

int main(int argc, char const* argv[]) {
    //freopen("tour.in", "r", stdin);
    //freopen("tour.out", "w", stdout);

    cin >> n >> m;
    for(int i=0;i<n;i++)
        cin >> cities[i];

    for(int i=0;i<m;i++) {
        string a,b;
        cin >> a >> b;
        int a_index = find_index(a);
        int b_index = find_index(b);
        flights[a_index][b_index] = flights[b_index][a_index] = true;
    }

    int res = eval(0,0);

    if (res == 2) res = 1;
    cout << res << endl;
    return 0;
}
