#include <cstdio>
#include <cstdlib>

using namespace std;

#define MAXQ 20005
#define MAXP 105
#define INF 0x7fffffff


int Q, P;
int pails[MAXP];
int min_pails[MAXQ], last_pail[MAXQ], n_last[MAXQ];
int res[MAXP], nres;

int compare (const void *a, const void *b) {
    return *(int *) b - *(int *) a;
}

bool better(int a, int b) {
    while (a && b) {
        if(last_pail[a] < last_pail[b]) return 1;
        if(last_pail[a] > last_pail[b]) return 0;

        a -= n_last[a] * last_pail[a];
        b -= n_last[b] * last_pail[b];
    }

    if (a) return 0;
    return 1;
}

void backtrack() {
    int c = Q;
    nres = min_pails[Q];

    for(int j=0;j<nres;j++) {
        res[j] = last_pail[c];
        c -= last_pail[c] * n_last[c];
    }
}

void findPails() {
    for(int i=0;i<=Q;i++) {
        last_pail[i] = -1;
        min_pails[i] = INF;
        n_last[i] = -1;
    }
    min_pails[0] = 0;
    for(int i=0;i<P;i++) {
        int temp_mp[MAXQ], temp_lp[MAXQ], temp_nl[MAXQ];
        for(int j=0;j<=Q;j++) {
            temp_mp[j] = min_pails[j];
            temp_lp[j] = last_pail[j];
            temp_nl[j] = n_last[j];
        }
        for(int j=pails[i];j<=Q;j++) {
            int prev = j - pails[i];

            if(temp_mp[prev] < INF) {
                if(temp_lp[prev] == pails[i]) {
                    temp_lp[j] = pails[i];
                    temp_mp[j] = temp_mp[prev];
                    temp_nl[j] = temp_nl[prev] + 1;
                }

                if(temp_lp[prev] != pails[i]) {
                    temp_lp[j] = pails[i];
                    temp_mp[j] = temp_mp[prev]+1;
                    temp_nl[j] = 1;
                }

                if(min_pails[prev] < INF &&
                        (min_pails[prev]+1<temp_mp[j] ||
                         (min_pails[prev]+1 == temp_mp[j] &&
                          better(prev, j - temp_nl[j] * pails[i])))) {
                    printf("Number... %d\n", pails[i]);
                    printf("Geldim... %d %d\n", prev, j - temp_nl[j] * pails[i]);
                    temp_lp[j] = pails[i];
                    temp_mp[j] = min_pails[prev] + 1;
                    temp_nl[j] = 1;
                }
            }
        }
        for(int j=pails[i];j<=Q;j++)
            if (temp_mp[j] <= min_pails[j]) {
                min_pails[j] = temp_mp[j];
                last_pail[j] = temp_lp[j];
                n_last[j] = temp_nl[j];
            }
    }
}

int main(int argc, char const* argv[]) {
    // freopen("milk4.in", "r", stdin);
    // freopen("milk4.out", "w", stdout);

    scanf("%d %d", &Q, &P);
    for(int i=0;i<P;i++) scanf("%d", &pails[i]);
    qsort(pails, P, sizeof(pails[0]), compare);

    findPails();
    backtrack();

    printf("%d", nres);
    for(int i=0;i<nres;i++) printf(" %d", res[i]);
    printf("\n");
    return 0;
}
