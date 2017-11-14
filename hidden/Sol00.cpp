#include<cstring>
#include<iostream>
#include<cstdio>

using namespace std;

const int MAXN = 2*100000+1;

int n;
char s[MAXN];
int v[MAXN];

int k1,k2;
int L1[MAXN],L2[MAXN];
int *l1=&L1[0], *l2=&L2[0];

int main(){

    FILE *fin = fopen("hidden.in", "r");
    fscanf(fin, "%d", &n);
    for(int i = 0; i < n; i+=72){
        fscanf(fin, "%s", &s[i]);
    }
    fclose(fin);

    memcpy(&s[n], &s[0], n);
    s[2*n] = 'z'+1;
    n = 2*n+1;

    for(int i = 0; i < n; ++i) v[i] = 0;
    for(int i = 0; i < n; ++i) l1[i] = i;
    k1 = n;

    while(k1 > 1){
        char least = 'z'+1;
        int most = 0;
        for(int i = 0; i < k1; ++i){
            least = min(least, s[l1[i]+v[l1[i]]]);
            most  = max(most, v[l1[i]+v[l1[i]]]);
        }

        k2 = 0;
        if(most > 0){
            for(int i = 0; i < k1; ++i){
                if(v[l1[i]] != -1 && v[l1[i]+v[l1[i]]] == most){
                    l2[k2++] = l1[i];
                    v[l1[i]+v[l1[i]]] = -1;
                    v[l1[i]] += most;
                }
            }
        } else {
            for(int i = 0; i < k1; ++i){
                if(v[l1[i]] != -1 && s[l1[i]+v[l1[i]]] == least){
                    l2[k2++] = l1[i];
                    v[l1[i]] += 1;
                }
            }
        }

        int *ls = l1;
        l1 = l2;
        l2 = ls;
        k1 = k2;
    }

    FILE *fout = fopen("hidden.out", "w");
    fprintf(fout, "%d\n", l1[0]);
    fclose(fout);

    return(0);
}



