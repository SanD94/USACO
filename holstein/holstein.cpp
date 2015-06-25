/*
ID: safaand1
PROG: holstein
LANG: C++11
*/

#include <iostream>
#include <fstream>

using namespace std;

ifstream fin("holstein.in");
ofstream fout("holstein.out");


int V,G;
int res = (1<<16)-1, sm=15;
int req[30];
int scoop[15][30];

int finduse(int a){
    int num=0;
    for(int i=0;i<G;i++) if((a>>i)&1) num++;
    return num;
}


void check(int *en,int sc){
    for(int i=0;i<V;i++) if(en[i]<req[i]) return;
    int used = finduse(sc);
    if(used < sm){
        sm = used;
        res = sc;
    }
    else if(used == sm){
        for(int i=0;i<G;i++){
            if(((sc>>i)&1) && !((res>>i)&1)) {res = sc; return;}
            if(!((sc>>i)&1) && ((res>>i)&1)) return;
        }
    }
}



int main(){
    fin >> V;
    for(int i=0;i<V;i++)
        fin >> req[i];
    fin >> G;
    for(int i=0;i<G;i++)
        for(int j=0;j<V;j++)
            fin >> scoop[i][j];
    int lim = 1 << G;

    for(int i=1;i<lim;i++){
        int enough[30] = {};
        for(int j=0;j<G;j++)
            if((i>>j)&1)
                for(int k=0;k<V;k++)
                    enough[k]+=scoop[j][k];
        check(enough,i);
    }
    fout << sm;
    for(int i=0;i<G;i++)
        if((res>>i)&1) fout << " " << i+1;
    fout << endl;
    return 0;
}
