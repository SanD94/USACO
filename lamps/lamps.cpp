/*
ID: safaand1
PROG: lamps
LANG: C++11
*/


#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;


typedef __uint128_t lli;

#define def(a) lli (1 << (127-(a)))


ifstream fin("lamps.in");
ofstream fout("lamps.out");


int N,C;
lli state[2];
lli lamps,aux;
lli all[16];

int main(){
    fin >> N;
    fin >> C;
    int lamp;

    for(int i=0;i<2;i++){ 
        fin >> lamp;
        while(lamp!=-1){
            state[i] |= def(lamp-1);            
            fin >> lamp;
        }
    }
    for(int i=0;i<16;i++){
        for(int i=0;i<N;i++) lamps |= def(i);
        if((i>>0)&1) lamps = 0;
        if((i>>1)&1) for(int i=1;i<N;i+=2) lamps ^= def(i);
        if((i>>2)&1) for(int i=0;i<N;i+=2) lamps ^= def(i);
        if((i>>3)&1) for(int i=1;i<N;i+=3) lamps ^= def(i);
    }
    

    return 0;
}
