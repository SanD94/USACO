/*
ID: safaand1
PROG: game1
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

ifstream fin("game1.in");
ofstream fout("game1.out");

int N,sum;
int seq[100];
int res[100][100];


int eval(int a,int b){
    if(b < a) return 0;
    if(a==b){
        res[a][b] = seq[a];
        return seq[a];
    }
    if(!res[a][b])
        res[a][b] = max( seq[a] + min(eval(a+2, b), eval(a+1, b-1)),
                seq[b] + min(eval(a, b-2), eval(a+1, b-1)));
    return res[a][b];
}


int main(){

    fin >> N;
    for(int i=0;i<N;i++) {
        fin >> seq[i];
        sum += seq[i];
    }

    eval(0, N-1);
    fout << res[0][N-1] << " " << sum-res[0][N-1] << endl;
    return 0;
}
