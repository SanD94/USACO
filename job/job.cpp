/*
ID: safaand1
PROG: job
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

#define fi first
#define se second
#define mp make_pair

typedef pair<int,int> ii;
typedef pair<int, ii> iii;

ifstream fin("job.in");
ofstream fout("job.out");

int N,A,B;
ii m1[30];
ii m2[30];
int work[1000];

int control(int mind,int wt){
   return m2[mind].se.fi + m2[mind].fi - 
       min(m2[mind].se.se - work[wt], m2[mind].fi);
}

int second(int mind,int wt){
    m2[mind].se.fi = control(mind, wt);
    m2[mind].se.se = work[wt];
    return m2[mind].se.fi;
}

int main(){
    int m;
    fin >> N >> A >> B;
    for(int i=0;i<A;i++) {
        fin >> m;
        m1[i] = mp(m,0);
    }
    for(int i=0;i<B;i++) {
        fin >> m;
        m2[i] = mp(m,mp(0,100000));
    }

    for(int i=0;i<N;i++){
        int mn = 100000;
        int ind = -1;
        for(int j=0;j<A;j++) {
            if(mn > m1[j].se+m1[j].fi){
                ind = j;
                mn = m1[j].se+m1[j].fi;
            }
        }
        work[i] = m1[ind].se += m1[ind].fi;
    }
    int res = 0;
    for(int i=N-1;i>=0;i--){
        int mn = 100000;
        int ind = -1;
        for(int j=0;j<B;j++) {
            if(mn > control(j,i)){
                mn = control(j,i);
                ind = j;
            }
        }
        res = max(res, second(ind,i));
    }
    fout << res << endl;
    
    return 0;
}
