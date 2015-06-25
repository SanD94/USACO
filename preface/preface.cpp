/*
ID: safaand1
PROG: preface
LANG: C++11
*/


#include <iostream>
#include <fstream>

using namespace std;

ifstream fin("preface.in");
ofstream fout("preface.out");

int N;
char numbers[] = "IVXLCDM";
int uses[10],temp,start;

void add(int a,int s){
    if(a==9){ uses[s]++; uses[s+2]++; return;}
    if(a==4){ uses[s]++; uses[s+1]++; return;}
    if(a>=5){ uses[s+1]++; uses[s]+=a-5; return;}
    uses[s]+=a;
}




int main(){
    fin >> N;

    for(int i=1;i<=N;i++){
       temp = i; start=0;
       while(temp){
           add(temp%10,start);
           temp/=10; start+=2;
       }
    }
    for(int i=0;i<7;i++)
        if(uses[i])
            fout << numbers[i] << " " << uses[i] << endl;
    return 0;
}
