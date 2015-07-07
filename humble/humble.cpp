/*
ID: safaand1
PROG: humble
LANG: C++11
*/


#include <iostream>
#include <fstream>

using namespace std;

#define MAXN 100001
#define MAXK 100

ifstream fin("humble.in");
ofstream fout("humble.out");


int N,K;
int numbers[MAXN];
int primes[MAXK];
int where[MAXK];

int main(){
    fin >> K >> N;
    for(int i=0;i<K;i++)
        fin >> primes[i];

    int cnt = 1;
    numbers[0] = 1;
    while(cnt<=N){
        int index = 0;
        int mn = 0x7FFFFFFF;
        for(int i=0;i<K;i++){
            while(numbers[cnt-1] >= numbers[where[i]]*primes[i]) where[i]++;
            if(mn > numbers[where[i]]*primes[i]){
                index = i;
                mn = numbers[where[i]]*primes[i];
            }

        }
        where[index]++;
        numbers[cnt++] = mn;
        
    }
    fout << numbers[N] << endl;

    return 0;
}
