/*
ID: safaand1
PROG: camelot
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <queue>

using namespace std;

#define mp make_pair
#define fi first
#define se second
#define MAXX 1000000
#define to_num(x) (x-'A')
#define max(a,b) (a)>(b)?(a):(b)
#define min(a,b) (a)<(b)?(a):(b)
#define abs(x) (x)>0?(x):-(x)
typedef pair<int,int> ii;
typedef pair<ii,int> iii;

ifstream fin("camelot.in");
ofstream fout("camelot.out");

int c,r;
iii min_knight[26][30];
int sum_move[26][30];
bool knights[26][30];
ii theking;
int steps[26][30][26][30];
char column;
int row, res;
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
    bool mark[26][30] = {};
    mark[start.fi][start.se] = 1;
    Q.push(mp(start,0));
    while(!Q.empty()){
	ii now = Q.front().fi;
	int step = Q.front().se;
	Q.pop();
	if(knights[now.fi][now.se]) {
	    if(min_knight[start.fi][start.se].se == MAXX)
		min_knight[start.fi][start.se] = mp(now,step);
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
    int mx_move = go_alone(dest);
    bool mark[26][30] = {};
    mark[theking.fi][theking.se] = 1;
    Q.push(mp(theking,0));
    while(!Q.empty()){
	ii now = Q.front().fi;
	int step = Q.front().se;
	Q.pop();
	if(step > mx_move) continue;
	//eval...
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
    for(int i=0;i<26;i++)
	for(int j=0;j<30;j++)
	    min_knight[i][j].se = MAXX;
    res = MAXX;
}

int main(){
    init();
    fin >> c >> r;
    fin >> column >> row;
    theking = mp(to_num(column),row-1);
    while(fin.good()){
	fin >> column >> row;
	knights[to_num(column)][row-1] = 1;
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

