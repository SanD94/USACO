/*
ID: safaand1
PROG: butter
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <set>
#include <vector>

using namespace std;

#define fi first
#define se second
#define MAXP 810
#define MXX 200000
#define mp(a,b) make_pair(a,b)
#define pb(a) push_back(a)

typedef pair<int,int> ii;

ifstream fin("butter.in");
ofstream fout("butter.out");

int N,P,C;
vector<ii> paths[MAXP];
int dist[MAXP];
int cows[MAXP];
int res = MXX*MAXP;
set<ii> S;

void eval(int start){
    dist[start] = 0;
    S.insert(mp(dist[start],start));
    while(!S.empty()){
        ii now = *S.begin(); S.erase(S.begin());
        int path = now.fi;
        int from = now.se;
        for(int i = 0;i<(int)paths[from].size();i++){
            int to = paths[from][i].fi;
            path = paths[from][i].se; 
            if( dist[to] > dist[from] + path ){
                S.erase(mp(dist[to],to));
                dist[to] = dist[from] + path;
                S.insert(mp(dist[to],to));
            }
        }
    }	
    int mn = 0;
    for(int i=1;i<=P; i++) mn += dist[i]*cows[i];
    res = mn < res ? mn : res;
}

int main(){
    fin >> N >> P >> C;
    int temp;
    for(int i=0;i<N;i++){
        fin >> temp;
        cows[temp]++;
    }
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
