/*
ID: safaand1
PROG: fact4
LANG: C++11
*/

#include <iostream>
#include <fstream>

using namespace std;


ifstream fin("fact4.in");
ofstream fout("fact4.out");

int N;

int find(){
    int num = 1;
    for(int i=1;i<=N;i++){
        int coef = i;
        while(coef%10==0) coef/=10;
        num*=coef;
        while(num%10==0) num/=10;
        num%=1000;
    }
    return num%10;
}

int main(){
    fin >> N;
    
    fout << find() << endl;

    return 0;
}
