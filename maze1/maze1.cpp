/*
ID: safaand1
PROG: maze1
LANG: C++11
*/


#include <iostream>
#include <fstream>
#include <queue>

using namespace std;

#define MX 100000
#define MAXH 110
#define MAXW 40
#define fi first
#define se second

typedef pair <int,int> ii;
typedef pair <ii,int> iii;
ifstream fin("maze1.in");
ofstream fout("maze1.out");

int W,H;
string maze[MAXH*2+1];
ii start[2];
int res;
queue <iii> Q;
int dir[][2] = { {1,0}, {0,1}, {-1,0}, {0,-1}};


bool check(ii next, int a){

    if(next.fi < 0 || next.fi >=H || next.se < 0 || next.se >=W) return 0;
    if(maze[next.fi*2+1+dir[a][0]][next.se*2+1+dir[a][1]] == '|') return 0;
    if(maze[next.fi*2+1+dir[a][0]][next.se*2+1+dir[a][1]] == '-') return 0;

    return 1;
}



void BFS(){
    bool mark[MAXH][MAXW] = {};
    Q.push(make_pair(start[0], 0));
    mark[start[0].fi][start[0].se] = 1;

    Q.push(make_pair(start[1], 0));
    mark[start[1].fi][start[1].se] = 1;

    while(!Q.empty()){
        iii now = Q.front(); Q.pop();
        res= now.se;
        ii loc = now.fi;
        for(int i=0;i<4;i++){
            ii tsugi = make_pair(loc.fi+dir[i][0], loc.se+dir[i][1]);
            if(check(tsugi,(i+2)%4) && !mark[tsugi.fi][tsugi.se]){
                Q.push(make_pair(tsugi,res+1));
                mark[tsugi.fi][tsugi.se] = 1;
            }
        }
    }
}

void find_exit(){
    int found = 0;
    for(int i=1;i<2*W;i+=2) if(maze[0][i] == ' ') 
        start[found++] = make_pair(0,i/2);
    for(int i=1;i<2*H;i+=2){
        if(maze[i][0] == ' ') start[found++] = make_pair(i/2,0);
        if(maze[i][2*W] == ' ') start[found++] = make_pair(i/2,W-1);
    }
    for(int i=1;i<2*W;i+=2) if(maze[2*H][i] == ' ') 
        start[found++] = make_pair(H-1,i/2);
}



int main(){
    fin >> W >> H;
    getline(fin,maze[0]);
    for(int i=0;i<2*H+1;i++)
            getline(fin, maze[i]);
    find_exit();

    BFS(); 
    
    fout << res+1 << endl;
    return 0;
}
