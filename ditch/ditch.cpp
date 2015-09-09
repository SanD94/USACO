/*
ID: safaand1
PROG: ditch
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define MAXX 100000000

typedef pair<int,int> ii;

ifstream fin("ditch.in");
ofstream fout("ditch.out");

int N,M;
int S,E,C;
int prevnode[201];
int flow[201];
int capacity[201][201];
bool mark[201];
int res;


void network_flow(int s, int d){
    if(s==d) {
        res = MAXX;
        return;
    }
    int maxloc, maxflow;
    while(1){
        for(int i=1;i<=M;i++){
            prevnode[i] = 0;
            flow[i] = 0;
            mark[i] = 0;
        }
        flow[s] = MAXX;
        while(1){
            maxflow = 0;
            maxloc = 0;
            for(int i=1;i<=M;i++)
                if(flow[i] > maxflow && !mark[i]){
                    maxflow = flow[i];
                    maxloc = i;
                }
            if(maxloc == 0) break;
            if(maxloc == d) break;
            mark[maxloc] = 1;
            for(int i=1;i<=M;i++){
                int nxt = i;
                int c = capacity[maxloc][nxt];
                if(c && flow[nxt] < min(maxflow, c)){
                    prevnode[nxt] = maxloc;
                    flow[nxt] = min(maxflow, c);
                }

            }
        }
        if(maxloc == 0) break; 
        res += flow[d];
        int curnode = d;
        while (curnode!=s){
            int nnode = prevnode[curnode];
            capacity[nnode][curnode] -= flow[d]; 
            capacity[curnode][nnode] += flow[d];
            curnode = nnode;
        }

    }
    
}


int main(){

    fin >> N >> M;
    for(int i=0;i<N;i++){
        fin >> S >> E >> C;
        capacity[S][E] += C;
    }
    network_flow(1,M);
    fout << res << endl;

    return 0;
}
