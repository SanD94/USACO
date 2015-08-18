/*
ID: safaand1
PROG: camelot
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <queue>
#include <vector>

using namespace std;

#define mp make_pair
#define pb push_back
#define fi first
#define se second
#define MAXX 1000000
#define to_num(x) (x-'A')
#define max(a,b) (a)>(b)?(a):(b)
#define min(a,b) (a)<(b)?(a):(b)
#define abs(x) (x)>0?(x):-(x)
typedef pair<int,int> ii;
typedef pair<ii, int> iii;

ifstream fin("camelot.in");
ofstream fout("camelot.out");

int c,r;
int sum_move[30][30];
bool knights[30][30];
vector<ii> n_places;
ii theking;
int steps[30][30][30][30];
char column;
int row;
int res;
ii moves[8] = { mp(2,1), mp(2,-1), mp(-2,1), mp(-2,-1),
    mp(1,2), mp(1,-2), mp(-1,2), mp(-1,-2) };
ii k_moves[8] = { mp(1,0), mp(0,1), mp(-1,0), mp(0,-1),
    mp(-1,-1), mp(-1,1), mp(1,1), mp(1,-1) };
queue<iii> Q;

bool boundary_check(ii p){
    if(p.fi < 0 || p.fi >= c) return 0;
    if(p.se < 0 || p.se >= r) return 0;
    return 1;
}


void eval_sum(ii start){
    bool mark[30][30] = {};
    mark[start.fi][start.se] = 1;
    Q.push(mp(start,0));
    while(!Q.empty()){
        ii now = Q.front().fi;
        int step = Q.front().se;
        Q.pop();
        if(knights[now.fi][now.se]){
            if(sum_move[start.fi][start.se] == MAXX) 
                sum_move[start.fi][start.se] = 0; 
            sum_move[start.fi][start.se] += step;
        }
        steps[start.fi][start.se][now.fi][now.se] = step;
        for(int i=0;i<8;i++){
            ii next = mp(now.fi + moves[i].fi, now.se + moves[i].se);
            if(boundary_check(next) && !mark[next.fi][next.se]){
                mark[next.fi][next.se] = 1;
                Q.push(mp(next,step+1));
            }
        }
    }
}

int go_alone(ii dest){
   return max(abs(dest.fi-theking.fi), abs(dest.se-theking.se));
}

void eval_kings_move(ii dest){
    if(sum_move[dest.fi][dest.se] >= res) return;
    int mx_move = go_alone(dest);
    bool mark[30][30] = {};
    int dec_step = MAXX;
    mark[theking.fi][theking.se] = 1;
    Q.push(mp(theking,0));
    
    while(!Q.empty()){
        ii now = Q.front().fi;
        int step = Q.front().se;
        Q.pop();
        if(step > mx_move) continue;
        for(int i=0;i<(int)n_places.size();i++){
            ii n_place = n_places[i];
            dec_step = min(steps[n_place.fi][n_place.se][now.fi][now.se] +
                steps[now.fi][now.se][dest.fi][dest.se] + step -
                steps[n_place.fi][n_place.se][dest.fi][dest.se], dec_step);
            res = min(res, dec_step+sum_move[dest.fi][dest.se]);
        }
        for(int i=0;i<8;i++){
            ii next = mp( now.fi + k_moves[i].fi, now.se + k_moves[i].se);
            if( boundary_check(next) && !mark[next.fi][next.se]){
                Q.push(mp(next,step+1));
                mark[next.fi][next.se] = 1;
            }
        }
	
    }
}

void init(){
    for(int i=0;i<30;i++)
        for(int j=0;j<30;j++)
            sum_move[i][j] = MAXX;
    for(int i=0;i<30;i++)
        for(int j=0;j<30;j++)
            for(int k=0;k<30;k++)
                for(int l=0;l<30;l++)
                    steps[i][j][k][l] = MAXX;
    res = MAXX;
}

int main(){
    init();
    fin >> r >> c;
    fin >> column >> row;
    theking = mp(to_num(column),row-1);
    while(fin.good()){
        fin >> column >> row;
        knights[to_num(column)][row-1] = 1;
        n_places.pb(mp(to_num(column), row-1));
    }
    for(int i=0;i<c;i++)
        for(int j=0;j<r;j++)
            eval_sum(mp(i,j));

    for(int i=0;i<c;i++)
        for(int j=0;j<r;j++)
            eval_kings_move(mp(i,j));
    fout << res << endl;
    return 0;
}

