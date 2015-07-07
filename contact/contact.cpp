/*
ID: safaand1
PROG: contact
LANG: C++11
*/


#include <iostream>
#include <fstream>
#include <cstring>
#include <queue>
using namespace std;

#define MAXN 200010
#define fi first
#define se second.first
#define th second.second

ifstream fin("contact.in");
ofstream fout("contact.out");

typedef pair<int,int> ii;
typedef pair<int,ii> iii;

int A,B,N;
int parts[13][10000];
char code[MAXN];
char *p;
priority_queue<iii> Q;

int convert(int s,int len){
    int e = s+len-1;
    int res = 0;
    while(e>=s) {
        res<<=1;
        res+= code[s++]-'0';
    }
    return res;
}


void add(int start,int len){
    int num = convert(start,len);
    parts[len][num]++;
}


void itos(int num,int len){
    if(!len) return;
    itos(num/2,len-1);
    fout << num%2;
}


int main(){
    fin >> A >> B >> N;
    p = code;
    while(fin.good()) {fin >> p; p+=80;}
    int len = strlen(code);
    for(int i=0;i<len;i++)
        for(int k=A;k<=B && i-k+1 >= 0; k++)
            add(i-k+1,k);

    for(int i=A;i<=B;i++){
        int go = 1 << (i+1);
        for(int j=0;j<go;j++)
            if(parts[i][j])
                Q.push(make_pair(parts[i][j], make_pair(-i,-j)));
    }

    
    int gon = 0;
    while(gon<N && !Q.empty()){
        iii tp = Q.top(); Q.pop();
        fout << tp.fi  << endl;
        itos(-tp.th,-tp.se);
        int line = 1;
        while(!Q.empty() && Q.top().fi == tp.fi){
            if(line==6) { fout << endl; line=0;}
            else fout << " "; 

            tp = Q.top(); Q.pop();
            itos(-tp.th,-tp.se);
            line++;
        }
       
        fout << endl;
        gon++;
    }

    return 0;
}
