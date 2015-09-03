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


int simple(int k){
    int r_point;
    int l_point;
    if ( n == 0 ) r_point = MAXX;
    else {
        r_point = m*k/n;
        if( m*k % n == 0) r_point --;
    }
    if ( n == p ) l_point = MAXX;
    else {
        l_point = m*(p-k)/(p-n);
        if (m*(p-k)%(p-n) == 0 ) l_point--;
    }
    return min(r_point, l_point);
}

int obtuse(int k){
    int r_point;
    int l_point;
    
    r_point = m*k/n;
    if( m*k % n == 0 ) r_point --;
    if ( k <= p )   return r_point;
    l_point = m*(k-p)/(n-p);
    return r_point - l_point;
}

int main(){
    fin >> n >> m >> p;
    lim = max(n, p);
    for(int i=1;i<lim;i++){
        if( n <= p ) res += simple(i);
        else res += obtuse(i);
       
    }

    fout << res << endl;
    return 0;
}
