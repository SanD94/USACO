/*
ID: safaand1
PROG: stamps
LANG: C++11
*/


#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

#define min(a,b) a<b?a:b


ifstream fin("stamps.in");
ofstream fout("stamps.out");

int N,K;
int mark[2000001];
int nums[200];


int main(){
    fin >> K >> N;
    for(int i=1;i<=2000000;i++) mark[i] = 300;
    for(int i=0;i<N;i++) {
        fin >> nums[i];
        mark[nums[i]] = 1;
    }

    int res;
    for(res=1;;res++){
        for(int i=0;i<N;i++){
            if(res-nums[i] < 0) continue;
            if(!mark[res-nums[i]] || mark[res-nums[i]]==K) continue;
            mark[res] = min(mark[res], mark[res-nums[i]]+1);
        }

        if(mark[res]==300) break;
    }
    fout << res-1 << endl;
    return 0;
}
