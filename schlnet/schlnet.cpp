/*
ID: safaand1
LANG: C++11
PROG: schlnet
*/

#include<iostream>
#include<cstdio>

using namespace std;

#define MAXN 105

int n;
bool path[MAXN][MAXN];
int order[MAXN], top;
bool mark[MAXN];
bool as_root[MAXN];


void DFS(int current, bool push_stack) {
    mark[current] = true;
    for(int i=1;i<=n;i++)
        if(path[current][i]) {
            if(!mark[i]) DFS(i, push_stack);
            as_root[current] |= as_root[i];
        }
    if(push_stack) order[top++] = current;
}

void reverse_path() {
    for(int i=1;i<=n;i++)
        for(int j=i+1;j<=n;j++) {
            bool temp = path[i][j];
            path[i][j] = path[j][i];
            path[j][i] = temp;
        }
}

bool control() {
    for(int i=1;i<=n;i++) {
        for(int j=1;j<=n;j++) mark[j] =  false;
        DFS(i, false);
        for(int j=1;j<=n;j++) if (!mark[j]) return false;
    }
    return true;
}

int find_root() {
    for(int i=1;i<=n;i++) {
        mark[i]=false;
        as_root[i]=false;
    }
    int count_root = 0;
    for(int i=1;i<=n;i++)
        if(!mark[i]) DFS(i, true);
    for(int i=1;i<=n;i++) mark[i] = false;
    while(top) {
        int current = order[--top];
        if(!mark[current]) {
            as_root[current] = true;
            count_root++;
            DFS(current, false);
        }
    }
    return count_root;
}


int main() {
    //freopen("schlnet.in", "r", stdin);
    //freopen("schlnet.out", "w", stdout);

    cin >> n;
    for(int i=0;i<n;i++) {
        int a = -1;
        while(a) {
            cin >> a;
            path[i+1][a] = true;
        }
    }
    int count_root = find_root();
    cout << count_root << endl;
    reverse_path();
    int count_leaves = find_root();
    int res = control() ? 0 : max(count_leaves, count_root);
    cout << res << endl;
    return 0;
}
