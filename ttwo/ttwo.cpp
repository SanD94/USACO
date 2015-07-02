/*
ID: safaand1
PROG: ttwo
LANG: C++11
*/

#include <iostream>
#include <fstream>

using namespace std;

#define fi first
#define se second

typedef pair<int,int> ii;

ifstream fin("ttwo.in");
ofstream fout("ttwo.out");

ii farmer, cows;
string map[11];
int dir[4][2] = { {-1,0}, {0,1}, {1,0}, {0,-1} };
bool mark[401][401];

bool check(ii &p, int *dd){
    int x = p.fi + dd[0];
    int y = p.se + dd[1];
    if(0 <= x && x <10 &&
            0 <= y && y < 10 &&
            map[x][y] != '*') {
        p.fi += dd[0];
        p.se += dd[1];
        return 1;
    }
    else return 0;
}


int go(ii &p, int dd){
    if(check(p, dir[dd])) return dd;
    else return (dd+1)%4;
}


int solve(){
    int cdir = 0, fdir = 0;
    int cloc = (cdir * 100) + (cows.fi*10 + cows.se);
    int floc = (fdir * 100) + (farmer.fi*10 + farmer.se);
    int res = 0;
    while(!mark[floc][cloc]){
        if(farmer.fi == cows.fi &&
                farmer.se == cows.se) return res;
        mark[floc][cloc] = 1;
        cdir = go(cows,cdir);
        fdir = go(farmer,fdir);
        cloc = (cdir * 100) + (cows.fi*10 + cows.se);
        floc = (fdir * 100) + (farmer.fi*10 + farmer.se);
        res++;
    }
    return 0;
}


int main(){
    for(int i=0;i<10;i++){
        fin >> map[i];
        for(int j=0;j<10;j++){
            if(map[i][j] == 'C') farmer = make_pair(i,j);
            if(map[i][j] == 'F') cows = make_pair(i,j);
        }
    }

    fout << solve() << endl;

    return 0;
}
