/*
ID: safaand1
PROG: crypt1
LANG: C++11
*/

#include <iostream>
#include <fstream>

using namespace std;


ifstream fin("crypt1.in");
ofstream fout("crypt1.out");

int N;
bool digits[10];
int res;

bool check(int k,bool x){
    if(!x && k>=1000) return 0;
    if(x && k>=10000) return 0;
    while(k){
        if(!digits[k%10]) return 0;
        k/=10;
    }
    return 1;
}

void eval(int a,int num){
    if(a==5){
        int x = num%100;
        int y = num/100;
        if(check((x%10)*y,0) && check((x/10)*y,0) && check(x*y,1)) res++;
        return;
    }
    for(int i=1;i<=9;i++)
        if(digits[i])
            eval(a+1,num*10+i);
}


int main(){
    int tmp;
    fin >> N;
    for(int i=0;i<N;i++){
        fin >> tmp;
        digits[tmp]=1;
    }
    eval(0,0);
    fout << res << endl;
    return 0;
}
