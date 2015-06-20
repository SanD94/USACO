/*
ID: safaand1
PROG: palsquare
LANG: C++11
*/

#include <fstream>
#include <iostream>
#include <string>
using namespace std;

ifstream fin ("palsquare.in");
ofstream fout ("palsquare.out");

int base;
char nums[] = "0123456789ABCDEFGHIJ";

string bas(int a){
    string num;
    while(a){
        num+=nums[a%base];
        a/=base;
    }
    int sze = num.length();
    string rnum;
    for(int i=0; i<sze;i++) rnum+=num[sze-i-1];
    return rnum;
}

bool pal(string a){
    int sze = a.length();
    for(int i=0;i<sze;i++)
        if(a[i] != a[sze-i-1]) return 0;
    return 1;
}

void findall(){
    for(int i=1;i<=300;i++){
        string s = bas(i);
        string ss = bas(i*i);
        if(pal(ss)) fout << s << " " << ss << endl;
    }
}


int main(){
    fin >> base;
    findall();
    return 0;
}
