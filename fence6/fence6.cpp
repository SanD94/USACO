/*
ID: safaand1
PROG: fence6
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
#define MAXX 1000000

typedef pair<int,int> ii;

ifstream fin("fence6.in");
ofstream fout("fence6.out");
vector <ii> path[110];
int edge[110][2];
int size[110];
int node;
int N;

int eval(int start, int end){
    int res = 0;
    int dist[110];
    bool mark[110] = {};
    for(int i = 0; i<=node;i++) dist[i] = MAXX;
    dist[start] = 0; mark[start] = 1;
    for(int i=0;i<(int)path[start].size();i++)
        if(path[start][i].fi == end){
            res = path[start][i].se;
            break;
        }
    int cur = start;
    while(cur!=end){
        int tmp = MAXX;
        for(int i=0;i<(int)path[cur].size();i++){
            int next = path[cur][i].fi;
            int len = path[cur][i].se;
            if(cur == start && next == end) continue;
            dist[next] = min(dist[next], dist[cur]+len);
        }
        for(int i=1;i<=node;i++)
            if(!mark[i] && dist[i] <= tmp){
                cur = i;
                tmp = dist[i];   
            }
        for(int i=1;i<=node;i++) cout << dist[i] << " ";
        cout << endl;
        mark[cur] = 1;
    }
    return res+dist[end];
}

void join(int b, int a){
    if(size[b] == 2) return;
    if(edge[b][0] == 0) edge[b][size[b]++] = edge[a][ 
}

int main(){
    int index, len, n1, n2, side;
    fin >> N;
    for(int i=0;i<N;i++){
        fin >> index >> len >> n1 >> n2;
        while(size[index] < 2) edge[index][size[index]++] = ++node;
        cout << index << " " << edge[index][0] << " " << edge[index][1] << endl;
        path[edge[index][0]].pb(mp(edge[index][1],len));
        path[edge[index][1]].pb(mp(edge[index][0],len));
        for(int j=0;j<n1;j++){
            fin >> side;
            join(side, index);
        }
        for(int j=0;j<n2;j++){
            fin >> side;
            join(side,index);
        }
    }

    int res = MAXX;
    for(int i=1;i<=N;i++)
        res = min(res, eval(edge[i][0], edge[i][1]));

    fout << res << endl;

    return 0;
}
