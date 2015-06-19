/*
ID: safaand1
PROG: ariprog
LANG: C++11
*/

#include <iostream>
#include <fstream>

using namespace std;

#define MAXB 125001

ifstream fin("ariprog.in");
ofstream fout("ariprog.out");

int N,M;
bool bisquare[MAXB];
bool none=1;

int main(){
    fin >> N >> M;
    N--;
    for(int i=0;i<=M;i++)
        for(int j=0;j<=M;j++)
            bisquare[i*i+j*j] = 1;
    int u_bound = M*M*2;
    for(int i=1;i*N<=u_bound;i++)
       for(int j=0;j+i*N<=u_bound;j++){
           bool check = 1;
           for(int k=0;k<=N;k++) if(!bisquare[j+k*i]) { check=0; break; }
           if(check) {fout << j << " " << i << endl; none=0;}
       } 
    if(none) fout << "NONE" << endl;
    return 0;
}
