/*
ID: safaand1
PROG: nocows
LANG: C++11
*/


#include <iostream>
#include <fstream>

using namespace std;

ifstream fin("nocows.in");
ofstream fout("nocows.out");

int N,K;
int res[210][110];

void fill(){
    for(int i=0;i<=N;i++)
        for(int j=0;j<=K;j++)
            res[i][j] = -1;
}

int find(int a,int b){
    if(res[a][b] != -1) return res[a][b];
    res[a][b] = 0 ;
    for(int i=1;i<a;i+=2){
        for(int j=1;j<b;j++){
            res[a][b]+=find(i,j)*find(a-i-1,b-1);
            res[a][b]+=find(i,b-1)*find(a-i-1,j);
            res[a][b]%=9901;
        }
        res[a][b] += 9901;
        res[a][b] -= find(i,b-1)*find(a-i-1,b-1);
        res[a][b] %= 9901;
    }
    return res[a][b];
}

int main(){
    fin >> N >> K;
    fill();
    res[1][1] = 1;
    fout << find(N,K) << endl;
   
    return 0;
}
