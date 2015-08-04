/*
ID: safaand1
PROG: fence
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

#define MAXN 500
#define pb push_back

ifstream fin("fence.in");
ofstream fout("fence.out");

int F;
int mark[MAXN][MAXN];
int sizes[MAXN];
vector<int> res;


void find_circuit(int now){
    if(!sizes[now]) {
        res.pb(now);
        return;
    }
    for(int i=0;i<MAXN && sizes[now];i++){
        if(mark[now][i]){
            mark[now][i]--;  mark[i][now] --;
            sizes[now] -- ; sizes[i] --;
            find_circuit(i);
        }
    }
    res.pb(now);
}


int main(){
    fin >> F;
    int a,b;
    for(int i=0;i<F;i++){
        fin >> a >> b;
        a--; b--;
        mark[a][b]++; mark[b][a]++;
    }
    int start = -1;
    for(int i=0;i<MAXN;i++){
        for(int j=0;j<MAXN;j++)  sizes[i] += mark[i][j];
        if(start == -1 && sizes[i] % 2) start = i;
    }
    if(start == -1) start = 0;
    find_circuit(start);

    for(int i=(int)res.size()-1;i>=0; i--) fout << res[i]+1 << endl;

    return 0;
}

