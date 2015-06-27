/*
ID: safaand1
PROG: lamps
LANG: C++11
*/


#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

ifstream fin("lamps.in");
ofstream fout("lamps.out");

#define def(a) ( 1 << (7 - (a))) 

int N,C,cnt;
unsigned char state[2];
unsigned char lamps;
unsigned char all[16];
bool done;

bool check(int a,int ind){
    return a & def(ind);
}

int main(){
    fin >> N;
    fin >> C;
    int lamp;

    for(int i=0;i<2;i++){ 
        fin >> lamp;
        while(lamp!=-1){
            state[i] |= def((lamp+5)%6);            
            fin >> lamp;
        }
    }
   
    for(int i=0;i<6;i++) if(check(state[0],i) && check(state[1],i)){
        fout << "IMPOSSIBLE" << endl;
        return 0;
    }

    for(int i=0;i<16;i++){
        lamps = (1<<8)-1;
        int used = 0;
        if(i>>0 & 1) {lamps = 0; used++;}
        if(i>>1 & 1) {for(int j=0;j<6;j+=2) lamps ^= def(j); used++;}
        if(i>>2 & 1) {for(int j=1;j<6;j+=2) lamps ^= def(j); used++;}
        if(i>>3 & 1) {for(int j=0;j<6;j+=3) lamps ^= def(j); used++;}
        if(used > C || (C-used)%2 ) continue;
        all[cnt++] = lamps;
    }
    sort(all,all+cnt);
    for(int i=0;i<cnt;i++){
        bool found = 1;
        for(int j=0;j<6;j++) if(check(state[0],j) && !check(all[i],j))
            found = 0;
        for(int j=0;j<6;j++) if(check(state[1],j) && check(all[i],j))
            found = 0;
        if(found){
            done = 1;
            for(int j=0;j<N;j++) fout << check(all[i],j%6);
            fout << endl;
        }
    }

    if(!done){
        fout << "IMPOSSIBLE" << endl;
        return 0;
    }
    return 0;
}
