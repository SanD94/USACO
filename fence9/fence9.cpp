/*
ID: safaand1
PROG: fence9
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <algorithm>
#include <cstdlib>

using namespace std;

#define MAXX 100000

ifstream fin("fence9.in");
ofstream fout("fence9.out");

int n,m,p;
int res;
int lim;

int main(){
    fin >> n >> m >> p;
    lim = max(n, p);
    for(int i=1;i<lim;i++){
        int p_left;
        int p_right;
        if ( n == 0 ) p_left == MAXX;
        else {
            p_left = i*m/n;
            if( i*m % n == 0 ) p_left--;
        }
        if ( p == n ) p_right == MAXX;
        else {
            p_right = i*m/abs(p-n);
            if ( i*m % abs(p-n) == 0 ) p_right--;
        }
       
    }

}
