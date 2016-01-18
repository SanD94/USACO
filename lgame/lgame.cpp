/*
ID: safaand1
PROG: lgame
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

typedef long long int lli;
typedef short int si;

map < pair<lli, si>, vector<string> > keeper;
vector<string> res;
string shuffled;
string points = "25441655176352357212466757";
int totpoint;

ifstream fin("lgame.in");
ifstream fin1("lgame.dict");
ofstream fout("lgame.out");


pair<lli,si> change(string word){
    lli st = 0;
    si nd = 0;
    int x;
    for(int i=0;i<word.length();i++){
	x = word[i] - 'a';
	if(x > 21) nd += 1 << ( (x-22) * 3 );
	else st += 1 << ( x*3 );
    }
    return make_pair(st, nd);
}

int calc_point(string word){
    int p = 0;
    for(int i=0;i<word.size();i++)
	p += points[word[i]-'a'] - '0';
    return p;
}


void checknice(string word){
    pair <lli, si> changed = change(word);
    vector <string> now = keeper[changed];
    if(!now.size()) return;
    int point = calc_point(word);
    if(point > totpoint) res.clear();
    if(point >= totpoint){
	totpoint = point;
	for(int i=0;i<now.size();i++) res.push_back(now[i]);
    }
}

void readdict(){
    string nxt;
    pair<lli, si> hashed;
    fin1 >> nxt;
    while(nxt[0] != '.'){
	hashed = change(nxt);
	keeper[hashed].push_back(nxt);
	fin1 >> nxt;
    }
    fin1.close();
}


void findcomb(int n, int k, string filler){
    if(!k) {
	checknice(filler);
	return;
    }	
    for(int i=filler.length();i<n-k;i++){
	filler.push_back(shuffled[i]);
	findcomb(n,k-1,filler);
	filler.pop_back();
    }
}

void eval(){
    string filler = "";
    for(int i=3;i<shuffled.length();i++)
	findcomb(shuffled.length(), i, filler);
}

void write(){
    sort(res.begin(), res.end());
    fout << totpoint << endl;
    for(int i=0;i<res.size();i++)
	fout << res[i] << endl;
    fout.close();
}

int main(){
    fin >> shuffled;
    fin.close();
    readdict();
    eval();
    write();
    return 0;
}

