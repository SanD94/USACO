/*
ID: safaand1
PROG: hidden
LANG: C++11
*/

#include<iostream>
#include<sstream>
#include<string>
#include<cstdio>

using namespace std;

#define MAXL 100010*2

int L;
stringstream ss;
string s;
int start[MAXL];
int values[MAXL];

int main(int argc, char const* argv[]) {
    freopen("hidden.in", "r", stdin);
    freopen("hidden.out", "w", stdout);
    cin >> L;
    string line;
    while(getline(cin, line)) ss << line;
    ss << ss.str(); ss << char('z'+1);
    s = ss.str(); 
    L = 2*L + 1;

    for(int i=0;i<L;i++) start[i] = i;

    int res = L;

    while(res > 1) {
        int cur_res = 0;
        int most = 0;
        char min_char = 'z'+1;
        for(int i=0;i<res;i++) {
            min_char = min(min_char, s[start[i]+values[start[i]]]);
            most = max(most, values[start[i]+values[start[i]]]);
        }
        if (most > 0) {
           for(int i=0;i<res;i++)
               if(values[start[i]+values[start[i]]] == most && values[start[i]] != -1) {
                   start[cur_res++] = start[i];
                   values[start[i]+values[start[i]]] = -1;
                   values[start[i]] += most;
               }
        } else {
            for(int i=0;i<res;i++)
                if(s[start[i]+values[start[i]]] == min_char && values[start[i]] != -1) {
                    start[cur_res++] = start[i];
                    values[start[i]]++;
                }
        }
        res = cur_res;
    }

    cout << start[0] << endl;
    return 0;
}
