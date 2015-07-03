/*
ID: safaand1
PROG: comehome
LANG: C++11
*/

#include <iostream>
#include <fstream>

using namespace std;

#define MAXN 60
#define MAX 1E08
#define min(a,b) ((a) < (b) ? (a) : (b))

ifstream fin("comehome.in");
ofstream fout("comehome.out");


int P;
int path[MAXN][MAXN];
char a,b;

int conv(char x){
    if(x <= 'Z') return x-'A';
    else return x-'a'+26;
}

void fill(){
    for(int i=0;i<MAXN;i++)
        for(int j=0;j<MAXN;j++)
            if(i!=j) path[i][j] = MAX;
}

int main(){
    fin >> P;
    fill();
    int x,y;
    int temp;
    for(int i=0;i<P;i++){
        fin >> a >> b >> temp;
        x = conv(a);
        y = conv(b);
        path[x][y] = path[y][x] = min(path[x][y],temp);
    }
    for(int k=0;k<MAXN;k++)
        for(int i=0;i<MAXN;i++)
            for(int j=0;j<MAXN;j++)
                path[i][j] = min(path[i][j], path[i][k]+path[k][j]);

    int res = MAX;
    char cres = 'A';
    for(int i=0;i<25;i++)
        if(res > path[i][25]) {
            res = path[i][25];
            cres = i+'A';
        }

    fout << cres << " " << res << endl;
    return 0;
}
