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

int L;
stringstream ss;
string s;

int main(int argc, char const* argv[]) {
    freopen("hidden.in", "r", stdin);
    freopen("hidden.out", "w", stdout);
    cin >> L;
    string line;
    while(getline(cin, line)) ss << line;
    s = ss.str();
    int res = 0;
    int current = 0;
    while(s[res] == s[current] && current < L) current++;
    
    while(current < L) {
        int counter = 0;
        while ( s[(res + counter) % L] == s[(current + counter) % L]
                && counter < L) counter++;
        if ( s[(res + counter) % L] > s[(current + counter) % L]) res = current;
        current += counter; current++;
    }
    cout << res << endl;

    return 0;
}
