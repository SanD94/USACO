/*
ID: safaand1
PROG: sort3
LANG: C++11
*/


#include <iostream>
#include <fstream>

using namespace std;

#define mn(a,b) a<b?a:b

ifstream fin("sort3.in");
ofstream fout("sort3.out");

int N;
int nos[4];
int seq[1010];
int diff[4][4];
int res;

int main(){

    fin >> N;
    for(int i=0;i<N;i++){
        fin >> seq[i];
        nos[seq[i]]++;
    }
    
    for(int i=1,k=0;i<=3;i++)
        for(int j=0;j<nos[i];j++,k++)
            if(i!=seq[k]) {diff[i][seq[k]]++; res++;}

    int a = mn(diff[1][2],diff[2][1]);
    int b = mn(diff[1][3],diff[3][1]);
    int c = mn(diff[2][3],diff[3][2]);
   
    fout << a+b+c+(res-2*(a+b+c))*2/3 << endl;
    return 0;
}
