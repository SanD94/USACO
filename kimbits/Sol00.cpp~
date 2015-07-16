/*
ID: safaand1
PROG: kimbits
LANG: C++11
*/

#include <iostream>
#include <fstream>

using namespace std;

typedef long long int lli;

lli vals[33][33],I;
int N,L;

ifstream fin("kimbits.in");
ofstream fout("kimbits.out");

void eval(){
    for(int j=0;j<33;j++)
	vals[0][j] = 1;
    for(int i=1;i<33;i++)
	for(int j=0;j<33;j++){
	    if(j == 0) vals[i][j] = 1;
	    else vals[i][j] = vals[i-1][j-1] + vals[i-1][j];
	}
}

void find(int nbit,int none,lli index){
    if(nbit == 0) return;

    lli s = vals[nbit-1][none];
    if(s <= index){
	fout << 1;
	find(nbit-1,none-1,index-s);
    }
    else{
	fout << 0;
	find(nbit-1,none,index);
    }
}

int main(){
    eval();
    fin >> N >> L >> I;
    find(N,L,I-1);
    fout << endl;

    return 0;
}
