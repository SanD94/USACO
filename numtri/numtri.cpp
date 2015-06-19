/*
ID: safaand1
PROG: numtri
LANG: C++11
*/

#include <iostream>
#include <fstream>

using namespace std;

ifstream fin("numtri.in");
ofstream fout("numtri.out");

int res[1001];
int temp[1001];
int N;

int main(){
    fin >> N;
    for(int i=1;i<=N;i++){
        for(int j=1;j<=i;j++)
            fin >> temp[j];
        for(int j=i;j>0;j--)
            res[j] = res[j-1]+temp[j] > res[j]+temp[j] ? res[j-1]+temp[j] : res[j]+temp[j];
    }
    int ress = 0;
    for(int i=1;i<=N;i++) ress = ress > res[i] ? ress : res[i];
    fout << ress << endl;
    return 0;
}
