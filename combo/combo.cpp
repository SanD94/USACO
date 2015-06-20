/*
ID: safaand1
PROG: combo
LANG: C++11
*/


#include <iostream>
#include <fstream>

using namespace std;

ifstream fin("combo.in");
ofstream fout("combo.out");
int fa,fb,fc;
int ma,mb,mc;
int N;

int eval(int a,int b){
    int t = a>b?a-b:b-a;
    if(N<=5) return N;
    t = (t>N-5)?N-t:t;
    if(5-t<0) return 0;
    else return 5-t;
}


int main(){
    fin >> N;
    fin >> fa >> fb >> fc;
    fin >> ma >> mb >> mc;
    int res = N>5?250:N*N*N*2;
    res -= eval(fa,ma)*eval(fb,mb)*eval(fc,mc);
    fout << res << endl;
    return 0;
}
