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

int next[100001];
int a,b;

int main(){

    fin >> a >> b;
    fout << a/b << ".";
    a %= b;

    while(!next[a]){
        next[a] = (a*10)%b;
        a = (a*10)%b;
    }

    return 0;
}
