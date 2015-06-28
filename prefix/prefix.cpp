/*
ID: safaand1
PROG: prefix
LANG: C++11
*/

#include <cstdio>
#include <cstring>
using namespace std;

FILE *fin;
FILE *fout;
int cnt;
char temp[256],P[201][15],S[200010];
int res;
bool arrived[200010];

bool equal(const char* a,const char* b){
    while(*a && *b) if(*a++!= *b++) return 0;
    if(!(*a) && *b) return 0; //For safety reasons
    return 1;
}


int main(){
    fin = fopen("prefix.in", "r");
    fout = fopen("prefix.out", "w");

    fscanf(fin, "%s", temp);
    while(!equal(temp,".")){
        strcpy(P[cnt++], temp);
        fscanf(fin, "%s", temp);
    }

    //for(int i=0;i<cnt; i++) printf("%s ",P[i]);
    //printf("\n");
    arrived[0] = 1;
    S[0] = ' ' ;
    while(fscanf(fin,"%s",temp) != EOF)
        strcat(S,temp);
    //printf("%s\n",S);
    fclose(fin); 

    for(int i=1;S[i];i++){
        for(int j=0;j<cnt && !arrived[i];j++){
            int len = strlen(P[j]);
            arrived[i] = (len<=i) && arrived[i-len] &&
                equal(S+i-len+1,P[j]);
        }
        if(arrived[i]) res = i;
    }
    fprintf(fout,"%d\n",res);
    fclose(fout);

    return 0;
}
