/*
ID: safaand1
PROG: namenum
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <map>
#include <string>
using namespace std;

ifstream fin("namenum.in");
ifstream dict("dict.txt");
ofstream fout("namenum.out");

map < string, string > M;


string hsh(string a){
    string h(a);
    int sze = a.length();
    for(int i=0;i<sze;i++) if(a[i]=='Q' || a[i] == 'Z') return h;
    for(int i=0;i<sze;i++)
       if(a[i]>'Q') h[i] = '0'+(a[i]-'B')/3+2;
       else h[i] = '0'+(a[i]-'A')/3+2;
    return h;
}

void find(string a){
    bool t = 0;
    for(map <string,string>::iterator it=M.begin(); it!=M.end(); it++)
        if(!a.compare(it->second)) {fout << it->first << endl; t=1;}
    if(!t) fout << "NONE" << endl;
}

int main(){
    string temp;
    string h;
    string nope;
    while(dict.good()){
        dict >> temp;
        h = hsh(temp);
        M[temp] = h;
    }
    fin >> nope;
    find(nope);
    return 0;
}
