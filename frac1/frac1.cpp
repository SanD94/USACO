/*
ID: safaand1
PROG: frac1
LANG: C++11
*/

#include <iostream>
#include <fstream>

using namespace std;

#define EPS 1E-05

ifstream fin("frac1.in");
ofstream fout("frac1.out");

int N;
int arr[200];
float limmn = -1;

int main(){
    int found = 0;
    float mn;
    fin >> N;
    while(found!=-1){
        found = -1;
        mn = 1+EPS;
        for(int i=1;i<=N;i++){
            if(float (arr[i])/i < mn){
                mn = float (arr[i])/i;
                found = i;
            }
        }
        if(found!=-1){
            if(!(limmn + EPS > mn && limmn-EPS < mn))  fout << arr[found] << "/" << found << endl;
            arr[found]++;
            limmn = mn;
        }
    }
}
