/*
ID: safaand1
PROG: milk3
LANG: C++11
*/


#include <iostream>
#include <fstream>
#include <queue>
using namespace std;

ifstream fin("milk3.in");
ofstream fout("milk3.out");

int lim[3];
int buc[3];
bool mark[9270];
int nope[3],res;
bool c[21];
queue <int> Q;



void add(int val0,int val1,int b0,int b1,int b2){
    int rval = val0*nope[b0] + val1*nope[b1] + buc[b2]*nope[b2];
    if(!mark[rval]){
        mark[rval] = 1;
        Q.push(rval);
    }
}


void fill(int a,int b){
    if(a==b) return;
    int na,nb;
    if(buc[a]+buc[b] > lim[b]){
        nb = lim[b];
        na = buc[a]+buc[b] - lim[b];
    }
    else{
        nb = buc[a]+buc[b];
        na = 0;
    }
    add(na,nb,a,b,3-a-b);
}



void bfs(){
    Q.push(lim[2]);
    mark[lim[2]] = 1;
    while(!Q.empty()){
        int fi = Q.front();
        Q.pop();
        buc[2] = fi%21; fi/=21;
        buc[1] = fi%21; fi/=21;
        buc[0] = fi;
        if(!buc[0] && !c[buc[2]]) { res++;  c[buc[2]] = 1;}
        for(int i=0;i<3;i++)
            for(int j=0;j<3;j++)
                fill(i,j);
    }
}


void write(){
    for(int i=0;i<=lim[2];i++)
        if(c[i]){
            fout << i; 
            if(--res) fout << " ";
        }
    fout << endl;
}

int main(){
    fin >> lim[0] >> lim[1] >> lim[2]; 
    nope[0] = 21*21; nope[1] = 21; nope[2] = 1;
    bfs();
    write();
    return 0;
}
