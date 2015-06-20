/*
ID: safaand1
PROG: barn1
LANG: C++11
*/


#include <iostream>
#include <fstream>

using namespace std;

ifstream fin("barn1.in");
ofstream fout("barn1.out");

int M,S,C;
bool stall[210];
int interval[200];

int main(){
    int res;
    fin >> M >> S >> C;
    int a;
    for(int i=0;i<C;i++){
        fin >> a;
        stall[a] = 1;
    }
    int front = 1, end = S;
    while(!stall[front]) front++;
    while(!stall[end]) end--;
    res =  end-front+1;
    for(int i = front; i<=end; ){
        front++;
        while(!stall[front] && front<end) front++;
        interval[front-i-1]++;
        i = front;
    }
    M--;
    for(int i=S;i>=1 && M;i--)
        while(M && interval[i]) {
            interval[i]--;
            res-=i;
            M--;
        }
    fout << res << endl;
    return 0;
}
