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
        mark[cur] = 1;
    }
    return res+dist[end];
}


int find(vector<int> &a){
    int vals[110] = {};
    for(int i=0;i<(int)a.size();i++)
        for(int j=0;j<2;j++)
            vals[edge[a[i]][j]]++;
    int mx=1, ind=0;
    for(int i=1;i<=node;i++)
        if(mx < vals[i]){
            mx = vals[i];
            ind = i;
        }
    return ind;
}

void pushvex(int a,int b,vector<int> &veca, vector<int> &vecb){
    int index = veca[0];
    if(a == 0 && b == 0){
        a = edge[index][0];
        b = edge[index][1];
    }
    if(a == edge[index][0]) b = edge[index][1];
    if(b == edge[index][0]) a = edge[index][1];
    for(int i = 0; i < (int) veca.size(); i++){
        if(size[veca[i]] == 2) continue;
        if(edge[veca[i]][0] != a ) edge[veca[i]][size[veca[i]]++] = a;
    } 

    for(int i = 0; i < (int) vecb.size(); i++){
        if(size[vecb[i]] == 2) continue;
        if(edge[vecb[i]][0]!= b ) edge[vecb[i]][size[vecb[i]]++] = b;
    } 
}

int main(){
    int index, len, n1, n2, side;
    fin >> N;
    for(int i=0;i<N;i++){
        fin >> index >> len >> n1 >> n2;
        while(size[index] < 2) edge[index][size[index]++] = ++node;
//        cout << index << " " << edge[index][0] << " " << edge[index][1] << endl;
        path[edge[index][0]].pb(mp(edge[index][1],len));
        path[edge[index][1]].pb(mp(edge[index][0],len));
        vector<int> veca;
        vector<int> vecb;
        veca.pb(index); vecb.pb(index);
        for(int j=0;j<n1;j++) {
            fin >> side; 
            veca.pb(side);
        }
        for(int j=0;j<n2;j++){
            fin >> side;
            vecb.pb(side);
        }
        pushvex(find(veca), find(vecb), veca, vecb);
    }

    int res = MAXX;
    for(int i=1;i<=N;i++)
        res = min(res, eval(edge[i][0], edge[i][1]));

    fout << res << endl;

    return 0;
}
