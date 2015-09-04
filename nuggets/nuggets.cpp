/*
ID: safaand1
PROG: nuggets
LANG: C++11
*/


#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

typedef long long int lli;

ifstream fin("nuggets.in");
ofstream fout("nuggets.out");

int N;
int bags[10];
int mnbag = 300;
lli path[256][256];
lli sum[256];
lli res = (1 << 31) - 1;

void init(){
    for( int i=0; i< 256;i++){
        for(int j=0; j<256; j++) path[i][j] = res;
        path[i][i] = 0;
        sum[i] = res;
    }
}

int start(int k){
    bool mark[256] = {};
    sum[k] = 0;
    int chosen = k;
    while(chosen != -1){
        int found = chosen;
        lli mn = (1 << 31) -1;
        mark[found] = 1;
        chosen = -1;
        for(int i=0;i<mnbag;i++){
            sum[i] = min(sum[i], sum[found]+path[found][i]);
            if(!mark[i] && sum[i] < mn){
                chosen = i;
                mn = sum[i];
            }
        }
    }
    res = 0;
    for(int i=0;i<mnbag;i++) res = max(res, sum[i]);
    if( res == ((1<<31)-1) || res == 0) res = mnbag;
    return res-mnbag;
    
}


int main(){
    init();
    fin >> N;
    for(int i=0;i<N;i++){
        fin >> bags[i];
        mnbag = min(bags[i], mnbag);
    }

    for(int i=0;i<N;i++){
        int mod = bags[i] % mnbag;
        for(int j=0;j<mnbag;j++)
            path[j][(j+mod)%mnbag] = min(path[j][(j+mod)%mnbag],
                    lli(bags[i]));
    }


    fout << start(0) << endl;
    

    return 0;
}
