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
ii cor[12];
int mark[20];
int next[20];
int res;

void findtsugi(int a){
    int num = 0;
    int tmp = (int)MAX;
    for(int i=0;i<N;i++){
        if(cor[i].se == cor[a].se && 
                cor[i].fi < tmp &&
                cor[i].fi > cor[a].fi){
           num = i;
           tmp = cor[i].fi;
        } 
    }
    next[a] = num;
    return;
}

void eval(int k,int cnt){
    if(cnt == N/2) {
        loop();
        return;
    }
    for(int i=1;i<=N;i++)
        if(i!=k && !mark[i]){
            mark[i] = k;
            mark[k] = i;
            eval(i,cnt+1);
            mark[i] = mark[k] = 0;
        }

}


int main(){
    fin >> N;
    for(int i=0;i<N;i++) fin >> cor[i].fi >> cor[i].se; 
    for(int i=0;i<N;i++) findtsugi(i);
    eval(1,0);
    return 0;
}
