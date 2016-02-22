/*
ID: safaand1
PROG: starry
LANG: C++11
*/

#include <cstdlib>
#include <cstdio>
#include <queue>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;


struct point {
    int x,y;
};

void eval(int,int);
vector<int> BFS(int,int,int);
bool is_good(point);

char sky[110][110];
char color[110][110];
bool mark[100][100];
bool markx[160][160];
char curchar = 'a';
int W, H;

struct cluster {
    int row, column;
    point start;
    point topleft;
    bool operator == (const cluster &c) const{
	bool found = 0;
	point change = {start.x-topleft.x, start.y-topleft.y};
	if((row == c.row && column == c.column) ||
		(row == c.column && column == c.row)){
	    int rot[8][2] = { {0,0},{row, column},{0, column},{row, 0},
		{0,0},{column,row},{column,0},{0,row}};
	    for(int i=0;i<8 && !found;i++){
		memset(markx, 0, row*160);
		found = DFS(change, c.topleft, rot[i], markx, i>=4);
	    }
	}
	return found;
    }
    bool DFS(point cur, const point &nope, int *rot, bool mark[][160], bool t) const{
	mark[cur.x][cur.y] = 1;
	bool found = 1;
	point next, changed;
	if(t) {cur.x ^=cur.y;cur.y^=cur.x;cur.x^=cur.y;}
	changed.x = rot[0] ? rot[0]-cur.x-1 : cur.x;
	changed.y = rot[1] ? rot[1]-cur.y-1 : cur.y;
	if(sky[changed.x+nope.x][changed.y+nope.y] != '1') return 0;
	if(t) {cur.x ^=cur.y;cur.y^=cur.x;cur.x^=cur.y;}
	for(int i=-1;i<2;i++)
	    for(int j=-1;j<2;j++){
		next.x = cur.x+i;
		next.y = cur.y+j;
		if(nice(next) && !mark[next.x][next.y] && 
			sky[topleft.x+next.x][topleft.y+next.y] != '0' && found){
		    found = DFS(next, nope, rot, mark, t);
		}
	    }
	return found;
    }
    bool nice(point p) const{
	if(p.x < 0 || p.x >= row || p.y < 0 || p.y >= column) return 0;
	return 1;
    }
};

vector<cluster> similar[160];

int main(){
    freopen("starry.in", "r", stdin);
    freopen("starry.out", "w", stdout);
    scanf("%d %d", &W, &H);
    for(int i=0;i<H;i++)
	scanf("%s", sky[i]);
    

    for(int i=0;i<H;i++)
	for(int j=0;j<W;j++)
	    if(sky[i][j] == '1'){
		eval(i,j);
		BFS(1,i,j);
	    }

    for(int i=0;i<H;i++)
	printf("%s\n", sky[i]);

    return 0;
}


bool is_good(point a) {
    if(a.x<0 || a.x>=H || a.y<0 || a.y>=W) return 0;
    return 1;
}

void eval(int x, int y){
    vector <int> vars = BFS(0, x,y);
    int count = vars[0];
    int top = vars[1], bottom = vars[2];
    int right = vars[3], left = vars[4];
    int row = bottom - top + 1;
    int column = right - left + 1;
    point topleft = {top, left};
    point start = {x, y};
    cluster c = {row, column, start, topleft};
    bool found = 0;
    for(cluster p : similar[count])
	if( p == c ){
	    found = 1;
	    color[c.start.x][c.start.y] = color[p.start.x][p.start.y];
	    break;
	}
    if(!found) {
	similar[count].push_back(c);
	color[start.x][start.y] = curchar++;
    }
}


vector<int> BFS(int choice, int x, int y){
    int top=x, left=y, right=y, bottom=x;
    int count = 0;
    mark[x][y] = 1;
    queue<point> Q;
    point cur = {x,y};
    point next;
    if(choice) sky[cur.x][cur.y] = color[x][y];
    Q.push(cur);
    while(!Q.empty()){
	cur = Q.front(); Q.pop();
	for(int i=-1;i<2;i++)
	    for(int j=-1;j<2;j++){
		next.x = i+cur.x;
		next.y = j+cur.y;
		if(choice && is_good(next) && sky[next.x][next.y]=='1'){
		    sky[next.x][next.y] = color[x][y];
		    Q.push(next);
		    continue;
		}
		if(is_good(next) && sky[next.x][next.y]=='1' && 
			!mark[next.x][next.y] ){
		    Q.push(next);
		    mark[next.x][next.y] = 1;
		    left = min(left, next.y);
		    bottom = max(bottom, next.x);
		    right = max(right, next.y);
		    count ++;
		}
	    }
    }
    vector<int> vars = {count, top, bottom, right, left};
    return vars;
}
