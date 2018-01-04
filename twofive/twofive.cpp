/*
ID: safaand1
PROG: twofive
LANG: C++11
*/

#include <iostream>
#include <cstdio>

using namespace std;


int count;
int dyn[6][6][6][6][6];

bool check(int a, int b, int c, int d, int e) {
    if(a>5 || b>5 || c>5 || d>5 || e>5) return false;
    if(a >= b && b >= c && c >= d && d >= e) return true;
    return false;
}

int eval(int a, int b, int c, int d, int e) {
    if(!check(a,b,c,d,e)) return 0;
    if(dyn[a][b][c][d][e]) return dyn[a][b][c][d][e];
    dyn[a][b][c][d][e] = eval(a+1, b, c, d, e) + eval(a, b+1, c, d, e) +
        eval(a, b, c+1, d, e) + eval(a, b, c, d+1, e) + eval(a, b, c, d, e+1);
    return dyn[a][b][c][d][e];
}

string find(int num) {
    string res(25,'A');
    int arr[5] = {};
    for(int i=0;i<25;i++)
        for(int j=0;j<5;j++) {
            arr[j]++;
            if(check(arr[0], arr[1], arr[2], arr[3], arr[4])) {
                int cur = dyn[arr[0]][arr[1]][arr[2]][arr[3]][arr[4]];
                if (cur > num) { res[j*5+(arr[j]-1)] = 'A'+i; break; }
                cout << cur << endl;
                num -= cur;
            }
            arr[j]--;
        }

    return res;
}


int find(string s) {
    char cur = 'A';
    int res = 0;
    int arr[5] = { };
    for(int i=0;i<25;i++)
        for(int j=0;j<5;j++) {
            arr[j]++;
            if(check(arr[0], arr[1], arr[2], arr[3], arr[4])) {
                if (s[j*5+arr[j]-1] == 'A'+i) break;
                res += dyn[arr[0]][arr[1]][arr[2]][arr[3]][arr[4]];
            }
            arr[j]--;
        }
    return res + 1;
}

int main(int argc, char const* argv[]) {
    //freopen("twofive.in", "r", stdin);
    //freopen("twofive.out", "w", stdout);
    char type;
    string seq;
    int num;

    dyn[5][5][5][5][5] = 1;
    eval(0,0,0,0,0);

    cin >> type;
    if (type == 'N') { cin >> num; cout << find(num-1) << endl; }
    else { cin >> seq; cout << find(seq) << endl; }
    return 0;
}
