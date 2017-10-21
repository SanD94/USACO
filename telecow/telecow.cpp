/*
ID: safaand1
PROG: telecow
LANG: C++11
*/

#include<iostream>
#include<cstdio>
#include<queue>

using namespace std;

int N, M;
bool path[110][110];
int start, end;
int deg[110];
int in_degree[110];
int out_degree[110];


void find_degrees() {
    bool mark[110] = {};
    queue<int> Q;
    Q.push(start);
    mark[start] = true;
    while(!Q.empty()) {
        int cur = Q.front(); Q.pop();
        if(cur == end) continue;
        for(int i=1;i<=N;i++) if (path[cur][i] && !mark[i]) {
            mark[i] = true;
            Q.push(i);
            deg[i] = deg[cur] + 1;
        }
    }
    for(int i=1;i<=N;i++) {
        if(i==end) continue;
        for(int j=1;j<=N;j++) {
            if(j==end) continue;
            if(deg[i] == deg[j]) path[i][j] = path[j][i] = 0;
            if(path[i][j] && deg[i] + 1 == deg[j]) {
                in_degree[j]++;
                out_degree[i]++;
            }
        }
    }
    for(int i=1;i<=N;i++) if(path[i][end]) {
        in_degree[end]++;
        out_degree[i]++;
    }
}


bool can_reach(int cur) {
    bool mark[110] = {};
    queue<int> Q;
    Q.push(cur); 
    mark[cur] = true;
    while(!Q.empty()) {
        cur = Q.front(); Q.pop();
        for(int i=1;i<=N;i++)
            if(path[cur][i]) {
                if ( i == end ) return true;
                if (deg[cur] < deg[i] && !mark[i]) {
                    mark[i] = true;
                    Q.push(i);
                }
            }
    }
    return false;
}

void remove_unnecessary() {
    for(int i=1;i<=N;i++) {
        if (i == start || i == end) continue;
        if (!can_reach(i)) {
            for(int j=1;j<=N;j++) {
                if(path[i][j] && deg[j] + 1 == deg[i]) out_degree[j]--;
                path[i][j] = 0;
            }
            in_degree[i] = out_degree[i] = 0;
            deg[i] = 0;
        }
    }
}

void minimum_binding() {
    for(int i=1;i<=N;i++) {
        if(i == start || i == end) continue;
        int cur_deg = deg[i];
        for(int j=i+1;j<=N;j++) {
            if (j == start || j == end) continue;
            if(path[i][j] && cur_deg < deg[j] && in_degree[j] == 1) {
                for(int k=1;k<=100;k++) {
                    path[i][k] = path[j][k];
                    path[j][k] = 0;
                }
                out_degree[i] += out_degree[j]-1;
                out_degree[j] = in_degree[j] = 0;
                path[i][j] = 0;
                deg[j] = 0;
                j = i+1;
            }
        }
    }
}

int main(int argc, char const* argv[]) {
    //freopen("telecow.in", "r", stdin);
    //freopen("telecow.out", "w", stdout);
    cin >> N >> M >> start >> end;
    for(int i=0;i<M;i++) {
        int a, b;
        cin >> a >> b;
        path[a][b] = path[b][a] = 1;
    }
    find_degrees();
    remove_unnecessary();
    minimum_binding();
    
    return 0;
}
