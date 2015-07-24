/*
ID: safaand1
PROG: spin
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstring>

using namespace std;

#define MOD 360

ifstream fin("spin.in");
ofstream fout("spin.out");

struct wheel{
    int pos = 0;
    int speed;
    int no;
    int wedge[5];
    int extend[5];
}wheels[5];

int light[360];
int res;


bool found(){
    for(int i=0;i<5;i++){
        for(int j=0;j<wheels[i].no;j++){
            int angle = (wheels[i].pos + wheels[i].wedge[j]) % MOD;
            for(int k=0;k<=wheels[i].extend[j];k++) 
                light[(angle+k)%MOD] |= 1 << i;
        }
    }
    for(int i=0;i<MOD;i++) if (light[i] == 31) return 1;
    return 0;
}

int main(){
    for(int i=0;i<5;i++){
        fin >> wheels[i].speed >> wheels[i].no;
        for(int j=0;j<wheels[i].no;j++)
            fin >> wheels[i].wedge[j] >> wheels[i].extend[j];
    }

   
    while(res < MOD){
        
        memset(light, 0, sizeof(light));
        if(found()) break;
        for(int i=0;i<5;i++)
            wheels[i].pos =  (wheels[i].pos + wheels[i].speed) % MOD;
        res++;
    }
    if(res < 360) fout << res << endl;
    else    fout << "none" << endl;
    return 0;
}
