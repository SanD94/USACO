/*
ID: safaand1
PROG: hamming
LANG: C++11
*/


#include <iostream>
#include <fstream>

using namespace std;

ifstream fin("hamming.in");
ofstream fout("hamming.out");

int N,B,H;
int res[80];
bool found;
int lim;

bool hamcheck(int a,int b){
    int x = a^b;
    int dist = 0;
    for(int i=0;i<B;i++) if((x>>i)&1) dist++;
    return dist >= H;
}



bool checkall(int st, int a){
    if(!st) return 1;
    for(int i=0;i<st;i++)
        if(!hamcheck(res[i], a)) return 0;
    return 1;
}


void fill(int step,int where){
    if(step == N) {found = 1; return;}
    for(int i=where;i<lim && !found;i++)
        if(checkall(step,i)){
            res[step] = i;
            fill(step+1,i+1);
        }
}


int main(){
    fin >> N >> B >> H;
    lim = 1<<B;
    fill(0,0);
    for(int i=0;i<N-1;i++){
        fout << res[i];
        if((i+1)%10==0) fout << endl;
        else fout << " ";
    }
    fout << res[N-1] << endl;
    return 0;
}
