/*
ID: safaand1
LANG: C++11
PROG: twofive
*/


#include <cstdio>
#include <iostream>

using namespace std;

#define MAXL 25

int count(bool used[], int x[], int y[]) {
    int dp[6][6][6][6][6] = {};
    int s[6];
    dp[5][5][5][5][5] = 1;
    s[0] = 5;
    for(s[1] = 5; s[1] >= 0; s[1]--)
    for(s[2] = 5; s[2] >= 0; s[2]--)
    for(s[3] = 5; s[3] >= 0; s[3]--)
    for(s[4] = 5; s[4] >= 0; s[4]--)
    for(s[5] = 5; s[5] >= 0; s[5]--) {
        int ch = s[1]+s[2]+s[3]+s[4]+s[5];
        int &val = dp[s[1]][s[2]][s[3]][s[4]][s[5]];
        if (used[ch]) {
            if(s[x[ch]] < s[x[ch]-1] && s[x[ch]] + 1 == y[ch]) {
                s[x[ch]]++;
                val = dp[s[1]][s[2]][s[3]][s[4]][s[5]];
                s[x[ch]]--;
            }
        } else
            for (int i = 1; i <= 5; i++)
                if (s[i] < s[i - 1]) {
                    s[i]++;
                    val += dp[s[1]][s[2]][s[3]][s[4]][s[5]];
                    s[i]--;
                }
    }

    return dp[0][0][0][0][0];
}

int find(string sequence) {
    int res = 0;
    bool used[MAXL] = {};
    int x[MAXL] = {}, y[MAXL] = {};
    for(int i=1;i<6;i++)
    for(int j=1;j<6;j++)
    for(int k=0;k<25;k++) {
        if (used[k]) continue;
        used[k] = true;
        x[k] = i; y[k] = j;
        if (sequence[(i-1)*5+j-1] == k + 'A') break;
        res += count(used, x, y);
        used[k] = false;
    }
    return res + 1;
}

string find(int num) {
    string res(25, 'A');
    bool used[MAXL] = {};
    int x[MAXL] = {}, y[MAXL] = {};
    for(int i=1;i<6;i++)
    for(int j=1;j<6;j++)
    for(int k=0;k<25;k++) {
        if (used[k]) continue;
        used[k] = true;
        x[k] = i, y[k] = j;
        int cnt = count(used,x,y);
        if (cnt > num) {
            res[(i-1)*5+j-1] = k + 'A';
            break;
        }
        num -= cnt;
        used[k] = false;
    }
    return res;
}


int main() {
    freopen("twofive.in", "r", stdin);
    freopen("twofive.out", "w", stdout);
    char type;
    string sequence;
    int num;
    cin >> type;
    if (type == 'N') { cin >> num; cout << find(num-1) << endl; }
    else { cin >> sequence; cout << find(sequence) << endl; }
    
    return 0;
}