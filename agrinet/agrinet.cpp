/*
ID: safaand1
PROG: agrinet
LANG: C++11
*/


#include <iostream>
#include <fstream>

using namespace std;

#define MAXN 110
#define MAX 1E08
ifstream fin("agrinet.in");
ofstream fout("agrinet.out");

int N;
int tree;
int mndist[MAXN];
int path[MAXN][MAXN];
bool mark[MAXN];

void fill(){
    for(int i=0;i<N;i++)
        mndist[i] = MAX;
}

void mst(int a){
    int sze = 1;
    mark[a] = 1;
    while(sze < N){
        for(int i=0;i<N;i++){
            if(a == i || mark[i]) continue;
            mndist[i] = min(mndist[i],path[a][i]);
        }
        a = 0;
        for(int i=0;i<N;i++){
            if(mndist[a] > mndist[i] && !mark[i]) a = i;
        }
        tree += mndist[a];
        mark[a] = 1;
        sze ++;
    }
}


int main(){
    fin >> N;
    for(int i=0;i<N;i++)
        for(int j=0;j<N;j++)
            fin >> path[i][j];
    fill();
    mst(0);
    fout << tree << endl;
    return 0;
}
