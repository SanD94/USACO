/*
ID: safaand1
PROG: camelot
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <algorithm>
using namespace std;

#define MAXC 26
#define MAXR 30
#define fi first
#define se second
#define mp make_pair
#define MAXX 10000000
#define FOR(i,n) for(int (i)=0;(i)<(int)(n);(i)++)


typedef pair<int,int> ii;

ifstream fin("camelot.in");
ofstream fout("camelot.out");

int r,c,n_size;
ii the_king;
ii knights[MAXC*MAXR];
int row;
char column;
int steps[MAXR][MAXC][MAXR][MAXC];
int kings_move[MAXR][MAXC];
int sums[MAXR][MAXC];
int woknight[MAXR][MAXC];
int bestrec[MAXR][MAXC];
int res = MAXX;
int moves[8][2] = { {-2, -1}, {-2, 1}, {2, 1}, {2, -1},
    {1, 2}, {1, -2}, {-1, -2}, {-1, 2} };

bool check(ii p){
    if(p.fi < 0 || p.fi >= r) return 0;
    if(p.se < 0 || p.se >= c) return 0;
    return 1;
}

int main(){
    fin >> r >> c;
    FOR(i,r) FOR(j,c) FOR(k,r) FOR(l,c) steps[i][j][k][l] = MAXX;

    FOR(i,r) FOR(j,c){
        steps[i][j][i][j] = 0;
        bool set = 1;
        while(set){
            set = false;
            FOR(k,r) FOR(l,c){
                if(steps[i][j][k][l] != MAXX){
                    FOR(m, 8){
                        ii next = mp(k+moves[m][0], l+moves[m][1]);
                        if(!check(next)) continue;
                        if(steps[i][j][next.fi][next.se]!=MAXX &&
                                steps[i][j][next.fi][next.se] <= steps[i][j][k][l]+1)
                            continue;
                        set = 1;
                        steps[i][j][next.fi][next.se] = steps[i][j][k][l] + 1;
                    }
                }
            }
        }
    }

    fin >> column >> row;
    the_king = mp(row-1, column-'A');
    FOR(i,r) FOR(j,c)
        sums[i][j] = kings_move[i][j] = max(abs(i-the_king.fi), abs(j-the_king.se));
    
    while(fin >> column >> row){
        knights[n_size] = mp(row-1, column-'A');
        FOR(i,r) FOR(j,c) 
            sums[i][j] += steps[i][j][knights[n_size].fi][knights[n_size].se];
        n_size++;
    }
    
    FOR(i,r) FOR(j,c) res = min(res, sums[i][j]);

    FOR(k, n_size){
        ii nowk = knights[k];
        FOR(i, r) FOR(j, c)
            woknight[i][j] = sums[i][j] - steps[nowk.fi][nowk.se][i][j] -
            kings_move[i][j];
        int resc = MAXX;
        FOR(i, r) FOR(j, c) {
            bestrec[i][j] = steps[nowk.fi][nowk.se][i][j] + kings_move[i][j];
            resc = min(bestrec[i][j], resc);
        }

        FOR(i, r) FOR(j, c){
            if(bestrec[i][j] == resc){
                FOR(k, r) FOR(l, c)
                    res = min(res, woknight[k][l] + steps[i][j][k][l] + resc);
            }
        }
    }

    fout << res << endl;

    return 0;
}
