/*
ID: safaand1
PROG: butter
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>

using namespace std;

#define MAXN 500
#define MAXP 800
#define MAXX 1450*225
#define fi first
#define se second
#define mp make_pair
#define pb push_back

ifstream fin("butter.in");
ofstream fout("butter.out");

typedef pair<int,int> ii;

int N,P,C;
vector<ii> path[MAXP];
int cows[MAXN];
int dist[MAXN][MAXP];
int look_up[MAXP], sze;
ii heap[MAXP];


void swap(int a,int b){
    ii temp = heap[look_up[a]];
    heap[look_up[a]] = heap[look_up[b]];
    heap[look_up[b]] = temp;
    look_up[a] ^= look_up[b];
    look_up[b] ^= look_up[a];
    look_up[a] ^= look_up[b];
}

void decrease_key(int node){
    int lookup = look_up[node];
    if(lookup == 0) return;
    int parent = (lookup-1)/2;
    if(heap[parent].fi > heap[lookup].fi) {
        swap(node, heap[parent].se);
        decrease_key(node);
    }
}

void heap_down(int node){
    int lookup = look_up[node];
    int left = lookup*2 + 1;
    int right = lookup*2 + 2;

    if(right < sze){
        if(heap[right].fi < heap[left].fi 
                && heap[right].fi < heap[lookup].fi){
            swap(node, heap[right].se);
            heap_down(node);
            return;
        }
    }
    if(left < sze && heap[left].fi < heap[lookup].fi){
        swap(node,heap[left].se);
        heap_down(node);
    }

}

void heap_pop(){
    swap(heap[0].se, heap[sze-1].se);
    sze --;
    heap_down(heap[0].se);
}

void eval(int index){
    int start = cows[index];
    int *now_dist = dist[index];
    for(int i=0;i<P;i++) {
        look_up[i] = i;
        heap[i] = mp(MAXX, i);
    }
    sze = P;
    heap[look_up[start]].fi = 0;
    decrease_key(start);
    while(sze){
        int now_node = heap[0].se;
        int shortest = heap[0].fi;
        now_dist[now_node] = shortest;
        heap_pop();
        for(int i=0;i<(int)path[now_node].size();i++){
            int next = path[now_node][i].fi;
            int lookup = look_up[next];
            if(lookup >= sze) continue;
            heap[lookup].fi = min(heap[lookup].fi, 
                    now_dist[now_node] + path[now_node][i].se);
            decrease_key(next);
        }
    }
}

int main(){
    int a,b,c;
    fin >> N >> P >> C;
    for(int i=0;i<N;i++) {
        fin >> a; a--;
        cows[i] = a;
    }
    for(int i=0;i<C;i++){
        fin >> a >> b >> c;
        a--; b--;
        path[a].pb(mp(b,c));
        path[b].pb(mp(a,c));
    }
    for(int i=0;i<N;i++) eval(i);    
    int mn = MAXX;
    for(int i=0;i<P;i++){
        int temp = 0;
        for(int j=0;j<N;j++) temp+=dist[j][i];
        mn = min(temp,mn);
    }

    fout << mn << endl;
}
