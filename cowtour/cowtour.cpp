/*
ID: safaand1
PROG: cowtour
LANG: C++11
*/


#include <iostream>
#include <fstream>
#include <string>
#include <cmath>

using namespace std;

#define fi first
#define se second
#define MAXN 160
#define MAX 1E10
#define min(a,b) ((a) < (b) ? (a) : (b)) 
#define max(a,b) ((a) > (b) ? (a) : (b)) 

typedef pair<int,int> ii;


ifstream fin("cowtour.in");
ofstream fout("cowtour.out");

ii coor[MAXN];
string adj[MAXN];

int N;
double path[MAXN][MAXN];
double mxpath[MAXN];
double fieldmax[3];
double res;
int type[MAXN];


void fill(){
    for(int i=0;i<N;i++)
        for(int j=0;j<N;j++){
            path[i][j] = MAX;
            if(i == j) path[i][j] = 0;
        }
}


void calc(int a,int b){
   path[a][b] = sqrt(pow(coor[a].fi-coor[b].fi,2) + 
          pow(coor[a].se - coor[b].se,2));
}

void DFS(int a,int t){
    type[a] = t;
    for(int i=0;i<N;i++) if(!type[i] && adj[a][i]-'0') DFS(i,t);
}


int main(){
    fin >> N;

    for(int i=0;i<N;i++) fin >> coor[i].fi >> coor[i].se;
    for(int i=0;i<N;i++) fin >> adj[i];
    fill();

    for(int i=0;i<N;i++)
        for(int j=0;j<N;j++)
            if(adj[i][j]-'0') calc(i,j);

    for(int k=0;k<N;k++)
        for(int i=0;i<N;i++)
            for(int j=0;j<N;j++)
                if(path[i][j] > path[i][k]+path[k][j])
                    path[i][j] = path[i][k] + path[k][j];
            
        
    res = MAX;
    int p = 1;

    for(int i=0;i<N;i++)
        if(!type[i]) DFS(i,p++);

    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++)
            if(path[i][j] < MAX)
                mxpath[i] = max(mxpath[i], path[i][j]);
        fieldmax[type[i]] = max(mxpath[i],fieldmax[type[i]]);
    }
    for(int i=0;i<N;i++)
        for(int j=0;j<N;j++)
            if(type[i]!=type[j]){
                calc(i,j);
                res = min(path[i][j]+mxpath[i]+mxpath[j],res);
            }
            
        
    res = max(res,fieldmax[1]);
    res = max(res,fieldmax[2]);

    fout.precision(6);
    fout.setf(ios::fixed, ios::floatfield);

    fout << res << endl;
    return 0;
}
