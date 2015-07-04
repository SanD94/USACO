/*
ID: safaand1
PROG: fracdec
LANG: C++11
*/


#include <iostream>
#include <fstream>

using namespace std;


ifstream fin("fracdec.in");
ofstream fout("fracdec.out");

int nxt[100001];
int a,b;

int field(int k){
    if(k==0) return 1;
    int res=0;
    while(k) {res++; k/=10;}
    return res;
}

int main(){

    fin >> a >> b;
    fout << a/b << ".";
    int cnt = field(a/b) +1;
    int init = a %= b;
    if(init == 0 ) {
        fout << 0 << endl;
        return 0;
    }
    while(!nxt[a] && a){
        nxt[a] = (a*10)%b;
        a = (a*10)%b;
    }
    while(init!=a) {
        fout << (init*10)/b;
        cnt++; if(cnt == 76) {fout << endl; cnt = 0;}
        init = nxt[init];
    }
    if(!a) {
        fout << endl;
        return 0;
    }
    fout << "(";
    cnt++; if(cnt == 76) {fout << endl; cnt = 0;}
    fout << init*10/b;
    cnt++; if(cnt == 76) {fout << endl; cnt = 0;}
    init = nxt[init];
    while(init!=a) {
        fout << init*10/b;
        cnt++; if(cnt == 76) {fout << endl; cnt = 0;}
        init = nxt[init];
    }
    fout << ")" << endl; 
    return 0;
}
