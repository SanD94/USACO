/*
ID: safaand1
PROG: rockers
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

ifstream fin("rockers.in");
ofstream fout("rockers.out");

int N,T,M;
int res[30][30][30];
bool done[30][30][30];
int songs[20];


int eval(int index, int left, int disk){
    if ( left < 0) return -1;
    if( disk == 0 ) return 0;
    if( index == N ) return 0;
    if(!done[index][disk][left]){
        done[index][disk][left] = 1;
        res[index][disk][left] = max (max (eval(index+1, left, disk),
                eval(index, T, disk-1)), 1+eval(index+1, left-songs[index], disk));
    }
    return res[index][disk][left];
}


int main(){

    fin >> N >> T >> M;
    for(int i=0;i<N;i++)
        fin >> songs[i];

    fout << eval(0,T,M) << endl;
    return 0;
}
