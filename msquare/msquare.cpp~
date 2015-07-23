/*
ID: safaand1
PROG: msquare
LANG: C++11
*/


#include <iostream>
#include <fstream>
#include <queue>
using namespace std;

#define fi first
#define se second

ifstream fin("msquare.in");
ofstream fout("msquare.out");


int target[8];
bool mark[50000];
pair<int,char> dad[50000];
char way[5] = "ABC";
int per[8];
queue<int> Q;

void init(){
    per[1]=per[0]=1;
    for(int i=2;i<8;i++) per[i] = i*per[i-1];
}

void swap(int &a,int &b){
    a^=b; b^=a; a^=b;
}

int hash_perm(int *perm){
    int left[9];
    for(int i=1;i<=8;i++) left[i] = i-1;

    int res = 0;
    for(int i=0,sze=7;i<8;i++,sze--){
        res += per[sze] * left[perm[i]];
        for(int j=perm[i]+1; j<=8;j++) left[j]--;        
    }
    return res;
}

int *origin(int a){
    int *res = new int[8];
    bool mark[9]={};
    for(int i=7;i>0;i--){
        int lim = a/per[i];
        int j=1; while(mark[j]) j++;
        for(int k=0;k<lim;j++) if(!mark[j]) k++;
        while(mark[j]) j++;
        res[7-i] = j; mark[j] = 1;
        a%=per[i];
    }
    int i=1; while(mark[i]) i++;
    res[7] = i;
    return res;
}

int eval(int *perm,int w){
    int temp[8];
    for(int i=0;i<8;i++) temp[i] = perm[i];
    if(w == 0){
        for(int i=0;i<4;i++)
            swap(temp[i],temp[7-i]);
        
    }
    if(w==1){
       for(int i=1;i<4;i++){
          swap(temp[0],temp[i]);
          swap(temp[4],temp[8-i]);
       }
    }
    if(w==2){
        swap(temp[1], temp[2]);
        swap(temp[1], temp[5]);
        swap(temp[1], temp[6]);
    }
  

    return hash_perm(temp);
}

void write(int w,int step){

    if(w == dad[w].fi){
        fout << step << endl;
        return;
    }
    
    write(dad[w].fi,step+1);
    fout << dad[w].se;
}

void BFS(){
    Q.push(0);
    mark[0] = 1;
    
    int fini = hash_perm(target);
    dad[0] = make_pair(0, '\0');
    while(!Q.empty()){
        int now = Q.front(); Q.pop();
        if(now == fini) {
            write(fini,0); 
            fout << endl;
            return;
        }
        int *now_perm = origin(now);
        for(int i=0;i<3;i++){
           int nxt = eval(now_perm, i); 
           if(!mark[nxt]){
               dad[nxt] = make_pair(now,way[i]);
               mark[nxt] = 1;
               Q.push(nxt);
           }
        }
        delete[] now_perm;
    }
}


int main(){
    init();
    for(int i=0;i<8;i++) fin >> target[i];
    BFS();
    return 0;
}
