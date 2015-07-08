#include <iostream>
#include <fstream>

using namespace std;

ifstream fin("fact4.in");
ofstream fout("fact4.out");

int N;
int n2,n5,num=1;

int main(){
    fin >> N;
    for(int i=1;i<=N;i++){
        int coef = i;
        while(coef%2 == 0) { coef/=2; n2++;}
        while(coef%5 == 0) { coef/=5; n5++;}

        num = num * coef % 10;
    }
    for(int i=0;i<n2-n5;i++)
        num = num * 2 % 10;
    fout << num << endl;
    return 0;
}
