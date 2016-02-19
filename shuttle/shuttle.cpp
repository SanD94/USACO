/*
ID: safaand1
PROG: shuttle
LANG: C++11
*/

#include <iostream>
#include <cstdio>

using namespace std;

int N;
char map[30];
int res[5000];
int cnt;
int level;

bool check(){
    for(int i=0;i<N;i++) if(map[i]!='B' || map[i+N+1]!='W') return 0;
    return 1;
}

void swap(char &a, char &b){
    a^=b;    b^=a;    a^=b;
}

bool DFS(int space){
    if(check()) return 1;
    if(space && map[space-1]=='W') {
        swap(map[space-1], map[space]);
        if(DFS(space-1)) {res[cnt++] = space; return 1;}
        swap(map[space-1], map[space]);
    }
    if(map[space+1]=='B'){
        swap(map[space], map[space+1]);
        if(DFS(space+1)) {res[cnt++] = space+2; return 1;}
        swap(map[space], map[space+1]);
    }
    if(map[space+1]=='W' && map[space+2]=='B'){
        swap(map[space], map[space+2]);
        if(DFS(space+2)) {res[cnt++] = space+3; return 1;}
        swap(map[space], map[space+2]);
    }
    if(space>=2 && map[space-1]=='B' && map[space-2]=='W'){
        swap(map[space], map[space-2]);
        if(DFS(space-2)) {res[cnt++]= space-1; return 1;}
        swap(map[space], map[space-2]);
    }

    return 0;
}


int main(){
    freopen("shuttle.in", "r", stdin);
    freopen("shuttle.out", "w", stdout);

    cin >> N;
    for(int i=0;i<N;i++) {map[i]='W'; map[i+N+1]='B';}
    map[N]=' ';
    swap(map[N], map[N-1]);
    DFS(N-1);
    res[cnt++] = N;
    for(int i=0,j=1;i<cnt-1;i++,j++) {
        cout << res[cnt-i-1];
        if(j!=20) cout << " ";
        else {cout << endl; j=0;}
    }
    cout << res[0] << endl;
    return 0;
}
