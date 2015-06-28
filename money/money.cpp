/*
ID: safaand1
PROG: money
LANG: C++11
*/

#include <iostream>
#include <fstream>

using namespace std;

typedef long long int lli;

ifstream fin("money.in");
ofstream fout("money.out");

int V,N;
int money[25];
lli total[10010];

int main(){
    
    fin >> V >> N;
    for(int i=0;i<V;i++) fin >> money[i];
    total[0] = 1;
    for(int i=0;i<V;i++)
        for(int j=money[i];j<=N;j++) total[j] += total[j-money[i]];

    fout << total[N] << endl;
    return 0;
}
