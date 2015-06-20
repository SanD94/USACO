/*
ID: safaand1
PROG: milk2
LANG: C++11
*/


#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

#define MAXN 5010
#define fi first
#define se second

typedef pair<int,int> ii;
ii times[MAXN*2];
int N;

ifstream fin ("milk2.in");
ofstream fout ("milk2.out");
int lmilked;
int nomilked;

int main(){
    fin >> N;
    int lowest = 100000000;
    for(int i=0;i<2*N;i+=2){
        fin >> times[i].fi;
        lowest = lowest<times[i].fi?lowest:times[i].fi;
        times[i].se = -1;
        fin >> times[i+1].fi;
        times[i+1].se = 1;
    }
    times[2*N] = make_pair(lowest,-2);
    sort(times,times+2*N+1);
    int begin,end;

    for(int i=1;i<=2*N;i++){
        nomilked = nomilked > (times[i].fi-times[i-1].fi) ? nomilked
           : (times[i].fi-times[i-1].fi); 
        int k = times[i].se;
        begin = times[i].fi;
        while(k) k+=times[++i].se;
        end = times[i].fi;
        lmilked = lmilked>(end-begin)?lmilked:(end-begin);
    }
    fout << lmilked << " " << nomilked << endl;
    return 0;
}
