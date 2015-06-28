/*
ID: safaand1
PROG: zerosum
LANG: C++11
*/

#include <iostream>
#include <fstream>

using namespace std;

ifstream fin("zerosum.in");
ofstream fout("zerosum.out");

char x[] = " +-";
char exp[30];
int N;

void check(){
    int sum = 0;
    for(int i=0;i<2*N;){
        int temp = 0;
        int sign = exp[i] == '+' ? 1 : -1;
        i+=2; temp += i/2*sign;
        while(exp[i] == ' ') { temp*=10; i+=2; temp+=i/2*sign;} 
        sum += temp;
    }
    if(!sum) fout << exp+1 << endl;
}


void eval(int a){
    if(a == N) { check(); return; }
    for(int i=0;i<3;i++){
        exp[2*a] = x[i];
        eval(a+1);
    }
}


int main(){
    fin >> N;
    exp[0] = '+';
    for(int i=1;i<=N;i++){
        exp[2*i-1] = i+'0';
        exp[2*i] = ' ';
    }
    exp[2*N] = 0;
    eval(1);
    return 0;
}
