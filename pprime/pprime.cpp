/*
ID: safaand1
PROG: pprime
LANG: C++11
*/


#include <iostream>
#include <fstream>
#include <algorithm>
#include <cmath>
using namespace std;

ifstream fin("pprime.in");
ofstream fout("pprime.out");

int a,b;
int vals[10000],cnt;


bool prime(int k){
    int sq = (int) sqrt(k);
    for(int i=2;i<=sq;i++) if(!(k%i)) return 0;
    return 1;
}

int nop(int a){
    int cnt=0;
    while(a>0) {a/=10; cnt++;}
    return cnt;
}

int pal(int a){
    int num=0;
    while(a>0){
        num*=10;
        num+=a%10;
        a/=10;
    }
    return num;
}

void generate(int num){
    for(int i=0;i<1000;i++){
        int np = nop(i);
        int nm = (int) pow(10,np)*num + pal(i) + pow(10,np+1)*i;
        if(prime(nm))  vals[cnt++] = nm;
    }
}


void write(){
    int start=0;
    while(vals[start++]<a); start--;
    while(start<cnt && vals[start]<=b) fout << vals[start++] << endl;
}

int main(){
    for(int i=0; i<=9;i++) generate(i);
    vals[cnt++] = 11;
    fin >> a >> b;
    sort(vals,vals+cnt);
    //for(int i=0;i<100;i++) cout << vals[i] << " ";
    //cout << endl;
    write();
    return 0;
}
