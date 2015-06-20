/*
ID: safaand1
PROG: dualpal
LANG: C++11
*/


#include <iostream>
#include <fstream>
#include <string>

using namespace std;

ifstream fin("dualpal.in");
ofstream fout("dualpal.out");

int N,S;
char nums[] = "0123456789";

bool pal(string a){
    int sze = a.length();
    for(int i=0;i<sze;i++)
        if(a[i]!=a[sze-i-1]) return 0;
    return 1;
}


string bas(int num, int b){
    string res;
    while(num){
        res += nums[num%b];
        num/=b;
    }
    return res;
}

int check(int a){
    int res = 0;
    for(int i=2;i<=10;i++)
        if(pal(bas(a,i))) res++;
    return res;
}

void eval(){
    int num = S;
    while(N){
        num++;
        if(check(num)>=2){
            N--;
            fout << num << endl;
        }
    }
}


int main(){
    fin >> N >> S;
    eval();
    return 0;
}
