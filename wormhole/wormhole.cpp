/*
ID: safaand1
PROG: wormhole
LANG: C++11
*/

#include <iostream>
#include <fstream>
using namespace std;

#define fi first
#define se second
#define MAX 1E09+2

ifstream fin ("wormhole.in");
ofstream fout ("wormhole.out");

typedef pair <int,int> ii;

int N;
ii cor[20];
int mark[20];
int nxt[20];
int res;
bool mrk[20][2];

void findtsugi(int a){
    int num = 0;
    int tmp = (int)MAX;
    for(int i=1;i<=N;i++){
        if(cor[i].se == cor[a].se && 
                cor[i].fi < tmp &&
                cor[i].fi > cor[a].fi){
           num = i;
           tmp = cor[i].fi;
        } 
    }
    nxt[a] = num;
    return;
}

bool loop(int a,bool out){
    if(!a) return 0;
    if(mrk[a][out]) return 1;
    mrk[a][out] = 1;
    bool check = out ? loop(nxt[a],0) : loop(mark[a],1);
    mrk[a][out] = 0;
    return check;
}



void eval(int k,int cnt){
    if(cnt == N/2) {
        for(int i=1;i<=N; i++)
            if(loop(i,0)) {res++; break;}
        return;
    }
    if(mark[k]){
        eval(k+1,cnt);
        return;
    }
    for(int i=k+1;i<=N;i++)
        if(!mark[i]){
            mark[i] = k;
            mark[k] = i;
            eval(k+1,cnt+1);
            mark[i] = mark[k] = 0;
        }
}


int main(){
    fin >> N;
    for(int i=1;i<=N;i++) fin >> cor[i].fi >> cor[i].se; 
    for(int i=1;i<=N;i++) findtsugi(i);
    eval(1,0);
    fout << res << endl;
    return 0;
}
