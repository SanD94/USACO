/*
ID: safaand1
PROG: telecow
LANG: C++11
*/

#include<iostream>
#include<cstring>
#include<cstdio>
#include<queue>

using namespace std;

int N,M;
bool path[110][110];
int removed[110], eliminate[110];
int start, finish;

bool find_path() {
    bool mark[110] = {};
    int prev[110] = {};
    int cur;
    queue<int> Q;
    mark[start] = true;
    Q.push(start);
    while(!Q.empty()) {
        cur = Q.front(); Q.pop();
        if (cur == finish) break;
        for(int i=1;i<=N;i++)
            if(path[cur][i] && removed[i] && !mark[i]) {
                mark[i] = true;
                prev[i] = cur;
                Q.push(i);
            }
    }
    if (cur == finish) {
        cur = prev[cur];
        while(cur != start) {
            removed[cur] = 0;
            cur = prev[cur];
        }
        return true;
    }
    return false;
}


int main(int argc, char const* argv[]) {
    freopen("telecow.in", "r", stdin);
    freopen("telecow.out", "w", stdout);
    
    cin >> N >> M >> start >> finish;
    for(int i=0;i<M;i++) {
        int a,b;
        cin >> a >> b;
        path[a][b] = path[b][a] = true;
    }
    memset(removed,-1,sizeof(removed));
    int count = 0;
    while(find_path()) count ++;
    cout << count << endl;
    
    for(int i=1;i<=N && count;i++) {
        if(i == start || i == finish) continue;
        bool back_up[110] = {};
        for(int j=1;j<=N;j++) {
            back_up[j] = path[i][j];
            path[i][j] = path[j][i] = 0;
        }
        memset(removed,-1,sizeof(removed));
        int cur_count = 0;
        while(find_path()) cur_count++;
        if (cur_count < count) {
            count --;
            eliminate[i] = 1;
            cout << i;
            if (count) cout << " ";
            else cout << endl;
        } else {
            for(int j=1;j<=N;j++) {
                if(eliminate[j]) continue;
                path[i][j] = path[j][i] = back_up[j];
            }
        }
    }
    
    return 0;
}
