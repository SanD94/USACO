/*
ID: safaand1
PROG: skidesign
LANG: C++11
*/

#include <iostream>
#include <fstream>

using namespace std;

#define MAXN 120
#define MAX 1E07
ifstream fin("skidesign.in");
ofstream fout("skidesign.out");

int N;
int hills[MAXN];
int res = MAX;

void eval(){
    for(int i=0;i<=100;i++){
        int upper = i+17;
        int tmp = 0;
        for(int j=0;j<=i;j++) tmp+= hills[j]*(j-i)*(j-i);
        for(int j=upper; j<=100; j++) tmp += hills[j]*(upper-j)*(upper-j);
        if(tmp < res ) res = tmp;
    }
}


int main(){
    fin >> N;
    int tmp;
    for(int i=0;i<N;i++) { fin >> tmp; hills[tmp]++;}
    eval();
    fout << res << endl;
    return 0;
}
