/*
ID: safaand1
PROG: spin
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

#define MOD 360
#define fi first
#define se second

int gcd(int a,int b){
    return a%b ? gcd(b, a%b) : b;
}

ifstream fin("spin.in");
ofstream fout("spin.out");

struct wheel {
    int speed;
    int no;
    int wedge[5];
    int extend[5];
    int period;
    int timeplace[5][360];
}wheels[5];
int res = 360;
pair<int,int> angles[5];

bool check(int a,int b){
    if(angles[a].fi <= angles[b].fi && angles[a].se >= angles[b].fi) return 1;
    if(angles[a].fi <= angles[b].se && angles[a].se >= angles[b].se) return 1;
    if(angles[b].fi <= angles[a].fi && angles[b].se >= angles[a].fi) return 1;
    if(angles[b].fi <= angles[a].se && angles[b].se >= angles[a].se) return 1;
    if(angles[a].se < angles[a].fi){
        if(angles[b].fi >= angles[a].fi || angles[b].se >= angles[a].fi) return 1;
        if(angles[b].fi <= angles[a].se || angles[b].se <= angles[a].se) return 1;
    }
    if(angles[b].se < angles[b].fi){
        if(angles[b].fi <= angles[a].fi || angles[b].fi <= angles[a].se) return 1;
        if(angles[b].se >= angles[a].se || angles[b].se >= angles[a].fi) return 1;
    }
    return 0;
}


void eval(int time,int w){
    if (w == 5){
	for(int i=0;i<5;i++)
	    for(int j=i+1;j<5;j++)
		if(!check(i,j)) return;
	    
	res = time;
	return;
    }
    for(int i=0;i<wheels[w].no;i++){
	int start = wheels[w].timeplace[i][time % wheels[w].period];
	int end = (start + wheels[w].extend[i]) % MOD;
	angles[w] = make_pair(start, end);
	eval(time, w+1);
    }
}


int main(){
    for(int i=0;i<5;i++){
        fin >> wheels[i].speed;
        fin >> wheels[i].no;
        wheels[i].period = MOD / gcd(MOD, wheels[i].speed);
        for(int j=0;j<wheels[i].no;j++){
            fin >> wheels[i].wedge[j] >> wheels[i].extend[j];
            for(int k=0;k<wheels[i].period;k++){
                wheels[i].timeplace[j][k] = wheels[i].wedge[j];
                wheels[i].wedge[j] = ( wheels[i].wedge[j] + wheels[i].speed ) % MOD;
            }
        }
    }


    for(int i=0;i<MOD && res == 360;i++)
        eval(i,0);

    if(res == 360)  fout << "none" << endl;
    else fout << res << endl;


}
