/*
ID: safaand1
PROG: inflate
LANG: C++11
*/


#include <iostream>
#include <fstream>

using namespace std;

#define MAXN 10001
#define max(a,b) (a)>(b)?(a):(b)

ifstream fin("inflate.in");
ofstream fout("inflate.out");

int N,M;
long long int total[MAXN];
long long int points[MAXN];

void fill(){
    for(int i=1;i<MAXN;i++)
        total[i] = -1;
}


int main(){
    int a,b;
    fin >> M >> N;
    for(int i=0;i<N;i++){
        fin >> a >> b;
        points[b] = max(points[b],a);
    }
    fill();
    for(int i=1;i<MAXN;i++){
        if(!points[i]) continue;
        for(int j=i;j<MAXN;j++){
            if(total[j-i]!=-1) total[j] = max(total[j], points[i]+total[j-i]);
        }
    }

    long long int res=0;
    for(int i=1;i<=M;i++) res = max(total[i],res);
    fout << res << endl;
    return 0;
}
