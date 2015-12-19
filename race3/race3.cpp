/*
ID: safaand1
PROG: race3
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

#define pb push_back

ifstream fin("race3.in");
ofstream fout("race3.out");

vector<int> road[51];
vector<int> unavoid;
vector<int> splitter;
int N;
bool split;

void read(){
    int nums = 0;
    int where = 0;
    while(nums!=-1){
	fin >> nums;
	while(nums!=-2 && nums!=-1){
	    road[where].pb(nums);
	    fin >> nums;
	}
	where++;
    }
    N = where - 2;
}

void DFS(int k, int mark[], bool step){
    int marker = step?2:1;
    for(int i=0;i<road[k].size();i++){
	if(!mark[road[k][i]]){
	    mark[road[k][i]] = marker;
	    DFS(road[k][i], mark, step);
	}
	if(marker != mark[road[k][i]]) split = 0;
    }

}

void eval(){
   for(int i=1;i<N;i++){
	int mark[51] = {};
	mark[i] = 1; mark[0] = 1;
	DFS(0, mark,0);
	if(!mark[N]) {
	    unavoid.pb(i);
	    mark[i] = 2; split = 1;
	    DFS(i, mark,1);
	    if(split) splitter.pb(i);
	}
   }
}

void write(){
    fout << unavoid.size();
    for(int i=0;i<unavoid.size();i++) fout << " " << unavoid[i];
    fout << endl;
    fout << splitter.size();
    for(int i=0;i<splitter.size();i++) fout << " " << splitter[i];
    fout << endl;
}

int main(){
    read();
    eval();
    write();
    return 0;
}

