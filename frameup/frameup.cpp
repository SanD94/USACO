/*
ID: safaand1
PROG: frameup
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>

using namespace std;

char map[40][40];
int W,H;
struct boundaries{
    int top;
    int bottom;
    int left;
    int right;
};
struct boundaries letters[26];
bool ishere[26];
bool connect[26][26];
char res[30];
int over[30];
int cnt;

ifstream fin("frameup.in");
ofstream fout("frameup.out");

void make_graph(){
   for(int i=0;i<26;i++)
       if(ishere[i]){
	   cnt++;
	   int top = letters[i].top;
	   int left = letters[i].left;
	   int right = letters[i].right;
	   int bottom = letters[i].bottom;
	   for(int j=left;j<=right;j++){
	       if(map[top][j] != 'A'+i &&
		       !connect[i][map[top][j]-'A']){
		   connect[i][map[top][j]-'A']=1;
		   over[map[top][j]-'A']++;
	       }
	       if(map[bottom][j] != 'A'+i && 
		       !connect[i][map[bottom][j]-'A']){
		   connect[i][map[bottom][j]-'A']=1;
		   over[map[bottom][j]-'A']++;
	       }
	   }
	   for(int j=top;j<=bottom;j++){
	       if(map[j][left] != 'A'+i && 
		       !connect[i][map[j][left]-'A']){
		   connect[i][map[j][left]-'A']=1;
		   over[map[j][left]-'A']++;
	       }
	       if(map[j][right] != 'A'+i &&
		       !connect[i][map[j][right]-'A']){
		   connect[i][map[j][right]-'A']=1;
		   over[map[j][right]-'A']++;
	       }
	   }
       }
}

void find_sol(int left){
    if(left == cnt){
	fout << res << endl;
	return;
    }
    for(int i=0;i<26;i++){
	if(ishere[i] && !over[i]){
	    ishere[i] = 0;
	    res[left] = 'A'+i;
	    for(int j=0;j<26;j++)
		if(connect[i][j]) over[j]--;
	    find_sol(left+1);
	    for(int j=0;j<26;j++)
		if(connect[i][j]) over[j]++;
	    ishere[i] = 1;
	    res[left] = 0;
	}
    }
    
}

int main(){
    fin >> H >> W;
    for(int i=0;i<H;i++)
	fin >> map[i];
    for(int i=0;i<26;i++){
	letters[i].top = H-1;
	letters[i].bottom = 0;
	letters[i].right = 0;
	letters[i].left = W-1;
	for(int j=0;j<H;j++)
	    for(int k=0;k<W;k++)
		if(map[j][k] == i+'A'){
		    ishere[i] = 1;
		    letters[i].top = min(letters[i].top, j);
		    letters[i].bottom = max(letters[i].bottom, j);
		    letters[i].right = max(letters[i].right, k);
		    letters[i].left = min(letters[i].left, k);
		}
    }
    make_graph();
    find_sol(0);
    return 0;
}

