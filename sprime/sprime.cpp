/*
ID: safaand1
PROG: sprime
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

ifstream fin("sprime.in");
ofstream fout("sprime.out");

int N;
int nums[] = {2,3,5,7};

bool isprime(int n){
    if(n==1) return 0;
    int sq = (int)sqrt(n);
    for(int i=2;i<=sq;i++)
        if(!(n%i)) return 0;
    return 1;
}

void gen(int num,int left){
    if(!left){
        if(isprime(num)) fout << num << endl;
        else return;
    }
    for(int i=0;i<5;i++){
        if(isprime(num*10+2*i+1))
            gen(num*10+2*i+1, left-1);
    }
}


int main(){
    fin >> N;
    for(int i=0;i<4;i++) gen(nums[i],N-1);
    return 0;
}
