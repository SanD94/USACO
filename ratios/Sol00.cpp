/*
ID: safaand1
PROG: ratios
LANG: C++11
*/


#include <iostream>
#include <fstream>

using namespace std;

ifstream fin("ratios.in");
ofstream fout("ratios.out");

int gcd(int a,int b){
    return a%b ? gcd(b, a%b) : b;
}
int find_det(int M[][3]){
    int res = 0;
    for(int i=0;i<3;i++)
        for(int j=0;j<3;j++)
            for(int k=0;k<3;k++){
                if(i==j || i==k || j==k) continue;
                int cof = 0;
                if(i != 0 ) cof++;
                if(j != 1 ) cof++;
                if(k != 2 ) cof++;
                if (cof!=2) res+=M[0][i]*M[1][j]*M[2][k];
                else res-= M[0][i]*M[1][j]*M[2][k];
            }
    return res<0 ? -res : res;
}

int goal[3];
int mix[3][3];

int main(){

    fin >> goal[0] >> goal[1] >> goal[2];
    for(int i=0;i<3;i++)
        for(int j=0;j<3;j++)
            fin >> mix[j][i];

    int det = find_det(mix);
    int vals[3];

    for(int i=0;i<3;i++){
        int temp[3];
        for(int j=0;j<3;j++){
            temp[j] = mix[j][i];
            mix[j][i] = goal[j];
        }
        vals[i] = find_det(mix);
        for(int j=0;j<3;j++) mix[j][i] = temp[j];
    }
    int cof = 1000000;
    bool found = 1;
    for(int i=0;i<3;i++) {
        int g = gcd(vals[i], det);
        cof = cof < g ? cof : g;
    }
    for(int i=0;i<3;i++) {
        if (vals[i]/cof > 100) found=0;
    }
    if(found) fout << vals[0]/cof << " "
                    << vals[1]/cof<< " "
                    << vals[2]/cof<< " "
                    << det/cof << endl;
    else fout << "NONE" << endl;
    return 0;
}
