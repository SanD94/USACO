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
#include <set>

using namespace std;

typedef long long int lli;
typedef short int si;

map < pair<lli, si>, vector<string> > keeper;
set <string> res;
string shuffled;
bool mark[7];
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
        if(x > 20) nd += 1 << ( (x-21) * 3 );
        else st += (lli) 1 << ( x*3 );
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
        for(int i=0;i<now.size();i++) res.insert(now[i]);
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

void doublecheck(string last, string former){
    pair <lli, si> hashf = change(former);
    pair <lli, si> hashl = change(last);
    vector<string> a0 = keeper[hashf];
    vector<string> a1 = keeper[hashl];
    if(!a0.size() || !a1.size()) return;
    int point = calc_point(last) + calc_point(former);
    if(point > totpoint) res.clear();
    if(point >= totpoint){
	//cout << former << " " << last << endl;
        totpoint = point;
        for(auto const& i:a0)
            for(auto const& j:a1){
                if(i.compare(j) > 0) res.insert(j+" "+i);
                else res.insert(i+" "+j);
		//cout << i << " " << j << endl;
            }
	//cout << "DONE" << endl << endl;
    }
}

bool twice;
string former;

void findcomb(int n, int k, int start, string filler){
    if(!k) {
        if(twice){
            doublecheck(filler, former);
            return;
        }
        checknice(filler);
        if(n - filler.length() >= 3){
            former = filler;
            twice = 1;
            findcomb(n,3,0,"");
            twice = 0;
        }
        return;
    }
    for(int i=start;i<=n-k;i++){
        if(mark[i]) continue;
        filler.push_back(shuffled[i]);
        mark[i] = 1;
        findcomb(n,k-1,i,filler);
        filler.pop_back();
        mark[i] = 0;
    }
}

void eval(){
    for(int i=3;i<=shuffled.length();i++)
        findcomb(shuffled.length(), i, 0, "");
}

void write(){
    fout << totpoint << endl;
    for(auto const& x : res) fout << x << endl;
    fout.close();
}

int main(){
    fin >> shuffled;
    fin.close();
    readdict();
    //cout << "Done reading..." << endl;
    eval();
    write();
    return 0;
}
