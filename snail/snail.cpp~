/*
ID: safaand1
PROG:
LANG: C++11
*/

#include <cstdio>
#include <cstring>

using namespace std;

int N;
int B;
int map[150][150];
int dir[4][2] = { {1,0}, {0,1}, {-1,0}, {0,-1}};
char c,n;

int main(){
    //freopen("snail.in", "r", stdin);
    //freopen("snail.out", "w", stdout);
    scanf("%d %d", &N, &B);
    for(int i=0;i<B;i++){
	scanf(" %c%c ",&c,&n);
	c-='A'; n-='1';
	map[n][c] = 1;
    }
    for(int i=0;i<N;i++){
	for(int j=0;j<N;j++)
	    printf("%d ", map[i][j]);
	printf("\n");
    }
    return 0;
}

