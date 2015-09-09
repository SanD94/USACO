/*
ID: safaand1
PROG: stall4
LANG: C++11
*/

#include <iostream>
#include <fstream>

using namespace std;

#define MAXX 10000

ifstream fin("stall4.in");
ofstream fout("stall4.out");

int N,M;
int path[404][404];

int network_flow(int source, int sink){
    int flow[404] = {};
    bool mark[404] = {};
    int dad[404] = {};
    int maxflow, maxloc;
    flow[source] = MAXX;
    while(1){
        maxflow = 0;
        maxloc = -1;
        for(int i=0;i<=N+M+1;i++)
            if(flow[i] > maxflow && !mark[i]){
                maxflow = flow[i];
                maxloc = i;
            }
        if(maxloc == -1) break;
        if(maxloc == sink) break;
        mark[maxloc] = 1;
        for(int i=0;i<=N+M+1;i++){
            int c = path[maxloc][i];
            if(c && flow[i] < min(maxflow, c)){
                dad[i] = maxloc;
                flow[i]= min(maxflow,c);
            }         
        }
    }
    if(maxloc == -1) return 0;
    int curnode = sink;
    while(curnode!=source){
        int nnode = dad[curnode];
        path[nnode][curnode] -= flow[sink];
        path[curnode][nnode] += flow[sink];
        curnode = nnode;
    }
    return flow[sink];
}

int main(){
    fin >> N >> M;

    for(int i=1;i<=N;i++)
        path[0][i] = 1;
    for(int i=1;i<=M;i++)
        path[N+i][N+M+1] = 1;
    for(int i=1;i<=N;i++){
        int cnt,k;
        fin >> cnt;
        for(int j=0;j<cnt;j++){
            fin >> k; path[i][k+N] = 1;
        }
    }
    int f,res = 0;
    while((f= network_flow(0, N+M+1)))
        res += f;
    fout << res << endl;


    return 0;
}
