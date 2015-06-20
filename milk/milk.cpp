/*
ID: safaand1
PROG: milk
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

#define MAXN 5010
#define fi first
#define se second

ifstream fin("milk.in");
ofstream fout("milk.out");

typedef pair<int,int> ii;
int N,M;
ii farmes[MAXN];


int main(){
    fin >> N >> M;
    int a,b;
    for(int i=0;i<M;i++){
        fin >> a >> b;
        farmes[i] = make_pair(a,b);
    }
    sort(farmes,farmes+M);
    int res = 0,i=0;
    while(N){
        if(farmes[i].se > N) {res += N*farmes[i].fi; N=0;}
        else {res +=  farmes[i].fi*farmes[i].se; N-=farmes[i].se; i++;}
    }
    fout << res << endl;
    return 0;
}
