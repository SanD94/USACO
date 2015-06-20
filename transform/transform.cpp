/*
ID: safaand1
PROG: transform
LANG: C++11
*/

#include <iostream>
#include <fstream>

using namespace std;

#define MAXN 12

ifstream fin ("transform.in");
ofstream fout ("transform.out");

char map[MAXN][MAXN];
char target[MAXN][MAXN];
char *map1,*target1;
int N;


void onedim(){
    map1 = new char [N*N];
    target1 = new char [N*N];
    for(int i=0; i<N; i++)
        for(int j=0; j<N; j++)
            map1[i*N+j] = map[i][j];
    for(int i=0; i<N; i++)
        for(int j=0; j<N; j++)
            target1[i*N+j] = target[i][j];
}

bool check(char *x){
    for(int i=0;i<N*N;i++)
        if(x[i]!=target1[i]) return 0;
    return 1;
}

char *t90(char *x){
    char *nope = new char [N*N];
    for(int i=0;i<N;i++)
        for(int j=0;j<N;j++)
            nope[j*N+N-1-i] = x[i*N+j];
    return nope;
}

char *reflect(char *x){
    char *nope = new char [N*N];
    for(int i=0;i<N;i++)
        for(int j=0;j<N;j++)
            nope[i*N+N-1-j] = x[i*N+j];
    return nope;
}

bool comb(char *x){
    char *nope = reflect(x);
    if(check(t90(nope))) return 1;
    if(check(t90(t90(nope)))) return 1;
    if(check(t90(t90(t90(nope))))) return 1;
    return 0;
}

void eval(){
    if(check(t90(map1))) {fout << 1 << endl; return;}
    if(check(t90(t90(map1)))) {fout << 2 << endl; return;}
    if(check(t90(t90(t90(map1))))) {fout << 3 << endl; return;}
    if(check(reflect(map1))) {fout << 4 << endl; return;}
    if(comb(map1)) {fout << 5 << endl; return;}
    if(check(map1)) {fout << 6 << endl; return;}
    fout << 7 << endl;
    return;
}



int main(){

    fin >> N;
    for(int i=0; i<N; i++)
       fin >> map[i];
    for(int i=0; i<N; i++)
       fin >> target[i]; 
    onedim();
    eval();
    return 0;

}
