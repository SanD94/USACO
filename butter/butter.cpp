/*
ID: safaand1
PROG: butter
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <queue>
#include <cstring>

using namespace std;

#define fi first
#define se second
#define MAXP 810
#define MXX 200000
#define mp(a,b) make_pair(a,b)
#define pb(a) push_back(a)

typedef pair<int,int> ii;
typedef pair<int,ii> iii;

ifstream fin("butter.in");
ofstream fout("butter.out");

int N,P,C;
vector<ii> paths[MAXP];
bool mark[MAXP][MAXP];
int dist[MAXP];
int cows[MAXP];
int res = MXX*MAXP;
priority_queue<iii> Q;

void eval(int start){
    dist[start] = 0;
    for(int i=1;i<=P;i++) memset(mark[i], 0, sizeof(mark[i]));
    for(int i=0;i<(int)paths[start].size();i++){
	int now =paths[start][i].fi;
	int path =paths[start][i].se;
	Q.push(mp(-path,mp(now,start)));
	mark[now][start] = mark[start][now] = 1;
    }
    while(!Q.empty()){
	iii now = Q.top(); Q.pop();
	int path = -now.fi;
	int to = now.se.fi;
	int from = now.se.se;
	dist[to] = dist[to] < dist[from] + path ? dist[to] 
	    : dist[from] + path;
	for(int i=0;i<(int)paths[to].size();i++){
	    int next =paths[to][i].fi;
	    if(mark[next][to]) continue;
	    path =paths[to][i].se;
	    Q.push(mp(-path,mp(next,to)));
	    mark[next][to] = mark[to][next] = 1;
	}
    }	
    int mn = 0;
    for(int i=0;i<C;i++) mn += dist[cows[i]];
    res = mn < res ? mn : res;
}

int main(){
    fin >> N >> P >> C;
    for(int i=0;i<N;i++) fin >> cows[i];
    int a,b,c;
    for(int i=0;i<C;i++) {
	fin >> a >> b >> c;
	paths[a].pb(mp(b,c));
	paths[b].pb(mp(a,c));
    }

    for(int i=1;i<=P;i++){
	for(int j=1;j<=P;j++) dist[j] = MXX;
	eval(i);
    }
    fout << res << endl;
    return 0;
}
