/*
ID: safaand1
PROG: theme
LANG: C++11
*/

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <map>
using namespace std;


typedef pair<int,int> ii;
int N;
int arr[5010];
int dyn[5010];


int main(){
    freopen("theme.in", "r", stdin);
    freopen("theme.out", "w", stdout);
    scanf("%d", &N);
    for(int i=0;i<N;i++) scanf("%d", arr+i); N--;
    for(int i=0;i<N;i++) arr[i] = arr[i+1] - arr[i];
    int ans = 0;
    for(int i=N-1;i>=0;i--){
	for(int j=i+2,k=0; j<N;j++,k++){
	    if(arr[i] != arr[j]) dyn[k] = 0;
	    else dyn[k] = 1 + min(dyn[k], j-i-2);
	    ans = dyn[k] > ans ? dyn[k] : ans;
	}
    
    }
    printf("%d\n", ans+1 < 5 ? 0 : ans+1);
    return 0;
}

