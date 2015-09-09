#include <cstdio>
#include <cstring>
#include <fstream>

using namespace std;

#define MAXC 200 //max number of cows
#define MAXS 200 //max number of stalls

ifstream fin("stall4.in");
ofstream fout("stall4.out");

bool likes[MAXC][MAXS];
int ncow; //number of cows
int nstall; //number of stall

int stall[MAXC]; // which stall is cow i assigned to?
int cow[MAXS]; // which cow is assigned to stall j

int mark[MAXC+MAXS];

/* find_cow, find_stall perform a flood fill to determine if there
 * is a path in the graph from the super source to the super sink
 * (see max matching algotihm)
 */

// find_cow tries to find a cow to go to with a stall
// find_stall tries to find a stall to go with a cow

int find_stall(int);

int find_cow(int stall){
    if(mark[stall+MAXC]) return 0;
    mark[stall+MAXC] = 1;

    if(cow[stall] == -1) return 1;
    else return find_stall(cow[stall]);
}

int find_stall(int cnum){

    if(mark[cnum]) return 0;
    mark[cnum]=1;
    
    for(int i=0;i<nstall;i++)
        if(likes[cnum][i] && find_cow(i)){
            stall[cnum] = i;
            cow[i] = cnum;
            return 1;
        }

    return 0;
}

int find_path(){
    memset(mark, 0, sizeof(mark));

    for(int i=0;i<ncow;i++)
        if(stall[i] == -1 && find_stall(i)) return 1;
    return 0;
}

int main(){
    int cnt,st;

    fin >> ncow >> nstall;
    for(int i=0;i<ncow;i++){
        fin >> cnt;
        while(cnt--){
            fin >> st; likes[i][st-1] = 1;
        }
        stall[i] = -1;
    }

    for(int i=0;i<nstall;i++) cow[i] = -1;

    for(cnt = 0; find_path(); cnt++);
    fout << cnt << endl;
    
    return 0;
}
