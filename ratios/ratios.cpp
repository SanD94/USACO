/*
ID: safaand1
PROG: ratios
LANG: C++11
*/


#include <iostream>
#include <fstream>

using namespace std;

ifstream fin("ratios.in");
ofstream fout("ratios.out");


int goal[3];
int mixture[3][3];
int mn = 300;
int res[4];

void check(int a,int b,int c){
    int results[3];
    for(int i=0;i<3;i++) {
        results[i] = a*mixture[0][i] + b*mixture[1][i] + c*mixture[2][i];
        if( !goal[i] ) {
           if (results[i]) return;
           else continue;
        }
        if( results[i] % goal[i] ) return;
        results[i] /= goal[i];
    }
    for(int i=0;i<3;i++)
        for(int j=i+1;j<3;j++)
            if(goal[i] && goal[j] && results[i] != results[j] ) return;
    if(a+b+c && a+b+c<mn){
        mn = a+b+c;
        res[0] = a; res[1] = b; res[2] = c;
        for(int i=0;i<3;i++) if(goal[i]) res[3] = results[i];
    }
}



int main(){
    fin >> goal[0] >> goal[1] >> goal[2];
    for(int i=0;i<3;i++)
        for(int j=0;j<3;j++)
            fin >> mixture[i][j];

    for(int i=0;i<100;i++)
        for(int j=0;j<100;j++)
            for(int k=0;k<100;k++) 
                check(i,j,k);

    if(mn == 300) fout << "NONE" << endl;
    else {
        fout << res[0];
        for(int i=1;i<4;i++) fout << " " << res[i];
        fout << endl;
    }

    return 0;


}
