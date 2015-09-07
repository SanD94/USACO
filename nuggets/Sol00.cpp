/*
ID: safaand1
PROG: nuggets
LANG: C++11
*/

#include <iostream>
#include <fstream>

using namespace std;


ifstream fin("nuggets.in");
ofstream fout("nuggets.out");

int lim = 1 << 16;
int N;
int nuggets[10];

int gcd(int a,int b){
    return a%b ? gcd(b, a%b) : b;
}

int evalgcd(){
    int res = nuggets[0];
    for(int i=1;i<N;i++)
        res = gcd(res,nuggets[i]);
    return res;
}

int eval(){
    bool done[256] = {};
    done[0] = 1;
    int res = 0, cnt = 0;
    while(cnt < lim){
        int mod = cnt % 256;
        if(done[mod]){
            done[mod] = 0;
            for(int i=0;i<N;i++) done[(mod+nuggets[i])%256] = 1;
        }
        else res = cnt;
        if(cnt - res > 256) return res;
        cnt ++;
    }
    return 0;
}

int main(){
    fin >> N;
    for(int i=0;i<N;i++) fin >> nuggets[i];
    if(evalgcd() != 1) fout << 0 << endl;
    else fout << eval() << endl;

    return 0;
}
