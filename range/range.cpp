/*
ID: safaand1
PROG: range
LANG: C++11
*/


#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;


ifstream fin("range.in");
ofstream fout("range.out");

int N;
int nums[300];
unsigned char field[300][300];


int main(){
    fin >> N;
    for(int i=0;i<N;i++){
        fin >> field[i];
        for(int j=0;j<N;j++){
            field[i][j] -= '0';
            if(j==0 || i==0) continue;
            if(field[i][j])
                field[i][j] = min(min(field[i-1][j-1], field[i-1][j]),
                        field[i][j-1]) + 1 ;
            nums[field[i][j]]++;
        }
    }

    for(int i=N-1;i>=2;i--) nums[i] += nums[i+1];

    int res=2;
    while(nums[res]){
        fout << res << " " << nums[res] << endl;
        res++;
    }
    return 0;
}
