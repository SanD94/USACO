/*
ID: safaand1
PROG: subset
LANG: C++11
*/


#include <iostream>
#include <fstream>

using namespace std;

ifstream fin("subset.in");
ofstream fout("subset.out");


int N;
long long int arr[800];

int main(){
    fin >> N;
    arr[0] = 1;
    int sz = N*(N+1)/2;
    for(int i=1;i<=N;i++)
        for(int j=sz;j-i>=0;j--)
            arr[j]+=arr[j-i];
    if((N-1)%4) fout << arr[sz/2]/2 << endl;
    else fout << 0 << endl;

    return 0;
}
