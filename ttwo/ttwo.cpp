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

int main(){
    for(int i=0;i<10;i++){
        fin >> map[i];
        for(int j=0;j<10;j++){
            if(map[i][j] == 'C') farmer = make_pair(i,j);
            if(map[i][j] == 'F') cows = make_pair(i,j);
        }
    }



    return 0;
}
