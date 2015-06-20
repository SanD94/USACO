/*
ID: safaand1
PROG: beads
LANG: C++11
*/

#include <fstream>
#include <iostream>
#include <string>

using namespace std;

ifstream fin ("beads.in");
ofstream fout ("beads.out");
string bead;
int N,res;
bool r,b;

int left(int k){
    int l = 0;
    k--;
    r = b = 1;
    while(l < N){
        k = (k+N)%N;
        if(bead[k] == 'r'){
            b = 0;
            if(!r) break;
        }
        if(bead[k] == 'b'){
            r = 0;
            if(!b) break;
        }
        k--; l++;
    }
    r = b = 1;
    return l;
}

int right(int k){
    int rr = 0;
    r = b = 1;
    while(rr < N){
        k = k%N;
        if(bead[k] == 'r'){
            b = 0;
            if(!r) break;
        }
        if(bead[k] == 'b'){
            r = 0;
            if(!b) break;
        }
        k++; rr++;
    }
    r = b = 1;
    return rr;
}

int main(){
    fin >> N >> bead;
    int temp;
    for(int i=0;i<N;i++) {
        temp = left(i) + right(i);
        res = temp>res?temp:res;
    }
    res = res>N?N:res;
    fout << res << endl;

    return 0;
}
