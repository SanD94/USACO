/*
ID: safaand1
PROG: friday
LANG: C++11
*/

#include <fstream>
#include <iostream>

using namespace std;

ifstream fin("friday.in");
ofstream fout("friday.out");


int thirteen[7];
int months[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
int N,init;

void check(int a){
    if(!(a%4)) months[1]++;
    if(!(a%100)) months[1]--;
    if(!(a%400)) months[1]++;
}

int main(){
    thirteen[0] = 1;
    fin >> N;
    for(int i=1900;i<1900+N;i++){
        check(i);
        for(int j=0; j<12; j++){
            init+=months[j];
            init%=7;
            thirteen[init]++;
        }
        months[1] = 28;
    }
    thirteen[init]--;
    for(int i=0;i<7;i++){
        fout << thirteen[i];
        if(i==6) fout << endl;
        else fout << " ";
    }
    return 0;
}
