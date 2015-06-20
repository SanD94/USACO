/*
ID: safaand1
PROG: gift1
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <string>

using namespace std;
#define MAXN 15

int index(string);

string giver[MAXN];
int total[MAXN],N;

ifstream fin ("gift1.in");
ofstream fout ("gift1.out");

int main(){
    int k,give,receive,money;
    string name;
    fin >> N;

    for(int i=0; i<N;i++) fin >> giver[i];    

    while(fin.good()){
        fin >> name >> money >> k;
        if(!money && !k) continue;
        give = index(name);
        total[give]-=money-money%k;
        for(int j=0;j<k;j++){
            fin >> name;
            receive = index(name);
            total[receive] += money/k; 
        }
    }
    for(int i=0;i<N;i++) fout << giver[i] << " " << total[i] << endl;
    return 0;
}

int index(string a){
    for(int i=0;i<N;i++) if(!a.compare(giver[i])) return i;
    return -1;
}
