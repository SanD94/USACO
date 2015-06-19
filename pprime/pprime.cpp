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

void generate(int num,int k){
    if(num==5) cout << "Heeeey!!!" << k  << endl;
    if(k>=9) {
        if(prime(num)) vals[cnt++] = num;
        return;
    }
    for(int i=0;i<10;i++) {
        int quo = (int) pow(10,k-1);
        generate(quo*i+num*10+i,k+2);
    }
}


void write(){
    int start=0;
    while(vals[start++]<a);
    while(vals[start]<=b) fout << vals[start++] << endl;
}

int main(){
    for(int i=0; i<=9;i++) generate(i,1);
    fin >> a >> b;
    sort(vals,vals+cnt);
    for(int i=0;i<10;i++) cout << vals[i] << endl;
    write();
    return 0;
}
