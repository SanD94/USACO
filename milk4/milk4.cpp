/*
ID: safaand1
PROG: milk4
LANG: C++11
*/

#include <cstdio>
#include <algorithm>

using namespace std;

#define MAXX 9

int Q, P, pail[100];
int *seq[20001];
int *cand[20001];

int *copy(int *a){
    if(!a) return NULL;
    int *arr = new int[MAXX];
    arr[0] = a[0];
    for(int i=1;i<=a[0];i++) arr[i] = a[i];
    return arr;
}

int *find_seq(int *a, int *b, int cur, int pail) {
    if (a[0] > b[0]) { delete a; return b; }
    else if (a[0] < b[0]) { delete b; return a; }
    else for(int i=1;i<=a[0];i++)
        if(a[i] > b[i]) { delete a; return b; }
        else if (a[i] < b[i]) { delete b; return a;}
    delete b;
    return a;
}


int *select_seq(int cur, int pail) {
    int *cur_seq = copy(seq[cur-pail]);
    int *cand_seq = copy(cand[cur-pail]);
    int *res;
    if(cur_seq[cur_seq[0]] != pail) cur_seq[++cur_seq[0]] = pail;
    if(cand_seq) {
        res = find_seq(cur_seq, cand_seq, cur, pail);
        delete cand[cur-pail];
        cand[cur-pail] = NULL;
    } else res = cur_seq;

    return res;
}

void add(int cur, int pail) {
    int *arr = select_seq(cur, pail);
    if(!seq[cur]) {
        seq[cur] = arr;
        return;
    }
    int *cur_seq = seq[cur];
    if(arr[0] < cur_seq[0]) {
        delete cur_seq; cur_seq = NULL;
        seq[cur] = arr;
    } else if (arr[0] > cur_seq[0] + 1)  { delete arr; arr = NULL; }
    else if (arr[0] == cur_seq[0] + 1) cand[cur] = arr;
    else {
        for(int i=1;i<=arr[0];i++)
            if(arr[i] < cur_seq[i]) { delete cur_seq; seq[cur] = arr; break; }
            else if (arr[i] > cur_seq[i]) { cand[cur] = arr; break; }
    }
}


int main(int argc, char const* argv[]) {
    freopen("milk4.in", "r", stdin);
    freopen("milk4.out", "w", stdout);
    scanf("%d %d", &Q, &P);
    for(int i=0;i<P;i++)
        scanf("%d", &pail[i]);
    sort(pail, pail+P);
    seq[0] = new int[1]; seq[0][0] = 0;

    for(int i=0;i<P;i++) {
        for(int j=pail[i];j<=Q;j++) {
            if(seq[j-pail[i]]) add(j, pail[i]);
        }
    }
    for(int i=0;i<seq[Q][0];i++) printf("%d ", seq[Q][i]);
    printf("%d\n", seq[Q][seq[Q][0]]);
    return 0;
}
