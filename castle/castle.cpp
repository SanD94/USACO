/*
ID: safaand1
PROG: castle
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <queue>

using namespace std;

#define fi first
#define se second

ifstream fin("castle.in");
ofstream fout("castle.out");

int N,M;
int wall[51][51];
int dir[][2] = { {0, -1}, {-1, 0}, {0, 1}, {1, 0} };
char cor[] = "WNES";
bool mark[51][51];
typedef pair<int,int> ii;
queue<ii> Q;
int nor,lroom;
ii coor;
char d;

bool checkbound(int a,int b){
    return (0<=a) && (a<M) && (0<=b) && (b<N);
}

int BFS(int a,int b){
    Q.push(make_pair(a,b));
    mark[a][b] = 1;
    ii now;
    int sze = 0;
    while(!Q.empty()){
        now = Q.front(); Q.pop();
        sze++;
        for(int i=0;i<4;i++){
            //cout << now.fi+dir[i][0] << " " << now.se+dir[i][1] << endl;
            if(!checkbound(now.fi+dir[i][0], now.se+dir[i][1]) ||
                    (wall[now.fi][now.se] & (1<<i)) || 
                    mark[now.fi+dir[i][0]][now.se+dir[i][1]]) {
                continue;
            }
            //cout << "Done" << endl;
            Q.push(make_pair(now.fi+dir[i][0],now.se+dir[i][1]));
            mark[now.fi+dir[i][0]][now.se+dir[i][1]] = 1;
        }
    }
    return sze;
}

void zeros(){
    for(int i=0;i<M;i++)
        for(int j=0;j<N;j++)
            mark[i][j] = 0;
}


int main(){
    int temp;
    fin >> N >> M;
    for(int i=0;i<M;i++)
        for(int j=0;j<N;j++)
            fin >> wall[i][j];

    for(int i=0;i<M;i++)
        for(int j=0;j<N;j++)
            if(!mark[i][j]) {
                temp = BFS(i,j);
                nor++;
                if(temp>lroom) lroom=temp;
            }
   
   fout << nor << endl;
   fout << lroom << endl;

   for(int i=0;i<N;i++)
       for(int j=M-1;j>=0;j--)
           for(int k=1;k<3;k++){
               if(wall[j][i] & (1<<k)){
                   zeros();
                   wall[j][i]-=1<<k;
                   temp = BFS(j,i);
                   if(temp > lroom) {
                       lroom = temp;
                       coor = make_pair(j+1,i+1);
                       d = cor[k];
                   }
                   wall[j][i]+=1<<k;
               }
           }
   fout << lroom << endl;
   fout << coor.fi << " " << coor.se << " " << d << endl;
   return 0;
}
