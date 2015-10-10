/*
ID: safaand1
PROG: buylow
LANG: C++11
*/

#include <iostream>
#include <string>
#include <fstream>
using namespace std;

#define max(a,b) a>b?a:b
#define min(a,b) a<b?a:b

ifstream fin("buylow.in");
ofstream fout("buylow.out");

string sum(string a, string b){
    string res = "";
    int a_len = a.length();
    int b_len = b.length();
    int mx = max(a_len, b_len);
    char ext = 0;
    for(int i=0;i<mx;i++){
	char x = (min(i, a_len)) < a_len ? (a[i]-'0') : 0;
	char y = (min(i, b_len)) < b_len ? (b[i]-'0') : 0;
	res += ((x+y+ext) % 10) + '0';
	ext = (x+y+ext)/10;
    }
    if(ext == 1) res += ext + '0';
    return res;
}

string inv(string a){
    string res;
    for(int i = a.length() - 1; i>=0; i--)
	res += a[i];
    return res;
}

int N;
int prices[5000];
int seq[5000];
string num[5000];

int main(){
    fin >> N;
    for(int i=0;i<N;i++){
	fin >> prices[i];
	seq[i] = 1;
	num[i] += "1";
    }
    for(int i=1;i<N;i++)
	for(int j=0;j<i;j++){
	    if(prices[i] == prices[j]){
		seq[j] = -1;
		num[j] = "";
	    }
	    else if(prices[i] < prices[j]){
		if (seq[j] >= seq[i]){
		    seq[i] = seq[j] + 1;
    		    num[i] = num[j];
		}
		else if(seq[j] + 1 == seq[i])
		    num[i] = sum(num[i], num[j]);
		
	    }
	}
    int len=0;
    string sq="";
    for(int i=0;i<N;i++){
	if(len < seq[i]) {
	    len = seq[i];
	    sq = num[i];
	}
	else if (len == seq[i])
	    sq = sum(sq, num[i]);
    }
    fout << len << " " << inv(sq) << endl;
    return 0;
}

