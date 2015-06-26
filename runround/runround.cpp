/*
 ID: safaand1
 PROG: runround
 LANG: C++11
 */

#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

#define MX 1E10

typedef unsigned long long int uli;


ifstream fin("runround.in");
ofstream fout("runround.out");

uli M;
uli res,mn;
int x[10];
int num[11],digit;
bool mark[10];

int finddigit(int a){
    int res = 0;
    while(a) {a/=10; res++;}
    return res;
}


void found(int from,int to,int step){
    if(step == digit){
        uli number = 0;
        while(step--) {number*=10; number+=num[step+1];}
        if(number > M  && number < mn) mn = number;
       return; 
    }
    if(num[to]) return ;
    int k = ((to-from)+digit)%digit;
    for(int i=k;i<=9;i+=digit){
        if(mark[i]) continue;
        mark[i] = 1; num[to] = i;
        found(to,x[to-1],step+1);
        num[to] = 0; mark[i] = 0;
    }
}



void generate(int dig){
    for(int i=0;i<dig;i++) x[i] = i+1;
    do{
        found(1,x[0],0);
    }while(next_permutation(x,x+dig));
}



int main(){
    fin >> M;
    mn = (uli)MX;
    digit = finddigit(M);
    generate(digit);
    if(mn == MX) generate(++digit); 
    res = mn;
    fout << res << endl;
}

