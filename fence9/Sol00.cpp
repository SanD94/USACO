/*
ID: safaand1
PROG: fence9
LANG: C++11
*/


#include <iostream>
#include <fstream>

using namespace std;

ifstream fin("fence9.in");
ofstream fout("fence9.out");

int n,m,p;

int gcd(int a,int b){
    return (a%b) ? gcd(b, a%b) : b;
}

int main(){
    fin >> n >> m >> p;
    int a2, b, i;
    a2 = m*p;
    b = ( (n > 0) ? gcd(n,m) : m) + p +
        ( (n == p) ? m : gcd ( ((n<p) ? (p-n) : (n-p)), m));
    i = (a2 - b + 2) / 2;
    fout << i << endl;
    return 0;
}
