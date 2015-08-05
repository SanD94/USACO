/*
ID: safaand1
PROG: shopping
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

ifstream fin("shopping.in");
ofstream fout("shopping.out");

typedef struct offer {
    int n;      //#offered product
    int k[5];   //#items
    int c[5];   //codes
    int p;      //price
}offer;

typedef struct product{
    int price;
    int number;
    int code;
}product;

offer off[100];
product pro[5];
int dynhash[1000];
int res[10000];
int s; //#offers
int b; //#different product

int fixpow(int exp){
    if(!exp) return 1;
    return fixpow(exp-1)*6;
}

void fillres(int step,int hash,int price){
    if(step == b){
        res[hash] = price;
        return;
    }
    int coef = fixpow(step);
    for(int i=0;i<=pro[step].number;i++)
        fillres(step+1,hash+coef*i,price+pro[step].price*i);
        
}

bool needed(int offindex){
    for(int i=0;i<off[offindex].n;i++){
        int indpro = dynhash[off[offindex].c[i]];
        if(indpro == -1) return 0;
    }
    return 1;
}

void init(){
    for(int i=0;i<1000;i++) dynhash[i] = -1;
}


int printres(){
    int hash = 0;
    for(int i=0;i<b;i++) hash += fixpow(i)*pro[i].number;
    return res[hash];
}
        
void eval(int index,int step,int hashb,int hashf){
    if(b == step){
        res[hashf] = min(res[hashf], res[hashb]+off[index].p);
        return;
    }
    int plus = 0;
    for(int i=0;i<off[index].n;i++) 
        if(dynhash[off[index].c[i]] == step)
            plus = off[index].k[i];

    for(int i=0;i + plus <= pro[step].number; i++){
        int addb = i*fixpow(step);
        int addf = (i+plus)*fixpow(step);
        eval(index,step+1,addb+hashb,addf+hashf);
    }
}

int main(){

    init();
    fin >> s;
    for(int i=0;i<s;i++){
        fin >> off[i].n;
        for(int j=0;j<off[i].n;j++){
            fin >> off[i].c[j];
            fin >> off[i].k[j]; 
        }
        fin >> off[i].p;
    }
    fin >> b;
    for(int i=0;i<b;i++){
        fin >> pro[i].code;
        fin >> pro[i].number >> pro[i].price;
        dynhash[pro[i].code] = i;
    }
    fillres(0,0,0);
    for(int i=0;i<s;i++)
        if(needed(i)) eval(i,0,0,0);


    fout << printres() << endl;

    return 0;
}
