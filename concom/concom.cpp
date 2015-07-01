/*
ID: safaand1
PROG: concom
LANG: C++11
*/


#include <iostream>
#include <fstream>
#include <queue>

using namespace std;

ifstream fin("concom.in");
ofstream fout("concom.out");

int n;
int i,j,p;
int owns[110][110];
queue<int> Q;

void checkall(int a){
    bool mark[110] = {};
    mark[a] = 1;
    for(int i=1;i<=100;i++){
        if(a == i) continue;
        if(owns[a][i]>50) { mark[i] = 1; Q.push(i); }
    }

    while(!Q.empty()){
        int owned = Q.front(); Q.pop();
        for(int i=1;i<=100;i++){
            if(owned==i || mark[i]) continue;
            owns[a][i] += owns[owned][i] ;
            if(owns[a][i]>50) {
                mark[i] = 1;
                Q.push(i);
            }
        }
    }
}

int main(){
    fin >> n;
    for(int k=1;k<=n;k++){
        fin >> i >> j >> p;
        owns[i][j]+=p;
    }
    for(int i=1;i<=100;i++) checkall(i);
    for(int i=1;i<=100;i++)
        for(int j=1;j<=100;j++){
            if(i==j) continue;
            if(owns[i][j]>50) fout << i << " " <<  j << endl;
        }
    return 0;
}
