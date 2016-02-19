/*
ID: safaand1
PROG: milk6
LANG: C++11
*/

#include <iostream>
#include <cstdio>
#include <climits>
#include <algorithm>
#include <cstring>

using namespace std;

#define MAXM 40
#define fi first
#define se second

typedef pair<int,int> ii;

int N,M;
int cost[MAXM][MAXM];
ii paths[1010];
ii keeper[1010];
vector<int> tracks;
int res;

int max_flow(){
    int curcost[MAXM][MAXM];
    int res = 0;
    for(int i=1;i<=N;i++)
        for(int j=1;j<=N;j++) curcost[i][j] = cost[i][j];

    while(1){
        int flow[MAXM];
        bool mark[MAXM];
        int dad[MAXM];
        int maxloc, maxflow;

        memset(flow, 0, sizeof(flow));
        memset(mark, 0, sizeof(mark));
        memset(dad, -1, sizeof(dad));
        flow[1] = LONG_MAX;

        while(1){
            maxloc = -1; maxflow = 0;
            for(int i=1;i<=N;i++)
                if(maxflow < flow[i] && !mark[i]){
                    maxloc = i;
                    maxflow = flow[i];
                }
            if(maxloc == -1 || maxloc == N) break;
            mark[maxloc] = 1;
            for(int i=1;i<=N;i++)
                if(flow[i] < min(curcost[maxloc][i], maxflow)){
                    dad[i] = maxloc;
                    flow[i] = min(curcost[maxloc][i], maxflow);
                }
        }
        if(maxloc == -1) break;
        int curpath = flow[N];
        res += curpath;

        int curnode = N;
        while(curnode!=1){
            int nextnode = dad[curnode];
            curcost[nextnode][curnode] -= curpath;
            curcost[curnode][nextnode] += curpath;
            curnode = nextnode;
        }
    }

    return res;
}



void min_cut(){
    int flow = max_flow();
    sort(keeper, keeper+M);
    for(int i=M-1;i>=0;i--){
        int cur = -keeper[i].se;
        cost[paths[cur].fi][paths[cur].se]-= keeper[i].fi;
        int cur_flow = max_flow();
        if(flow - cur_flow == keeper[i].fi){
            tracks.push_back(cur);
            res += keeper[i].fi;
            flow = cur_flow;
            continue;
        }
        cost[paths[cur].fi][paths[cur].se] += keeper[i].fi;
    }
}

int main(){
    freopen("milk6.in", "r", stdin);
    freopen("milk6.out", "w", stdout);
    cin >> N >> M;
    int a,b,c;
    for(int i=0;i<M;i++){
        cin >> a >> b >> c;
        cost[a][b] += c;
        paths[i] = make_pair(a,b);
        keeper[i] = make_pair(c, -i);
    }
    min_cut();

    sort(tracks.begin(), tracks.end());
    cout << res << " " << tracks.size() << endl;
    for(int i=0;i<tracks.size();i++)
        cout << tracks[i]+1 << endl;
    return 0;
}
