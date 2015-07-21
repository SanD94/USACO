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


int arr[100][100][100][3];

int wanted[3];
int ratios[3][3];

int sum(int *arr){
    int res = 0;
    for(int i=0;i<3;i++) res += arr[i];
    return res;
}

void find(int a,int b,int c){
    int vals[3];
    int rmods[3];
    for(int i=0;i<3;i++){
        vals[i] = ratios[0][i] * a + ratios[1][i] * b + ratios[2][i] * c; 
        rmods[i] = vals[i] % wanted[i];
    }
    int *x = arr[rmods[0]][rmods[1]][rmods[2]];
    if((!x[0] && !x[1] && !x[2]) ||
            a+b+c < sum(x)){
       x[0] = a; x[1] = b; x[2] = c;
       find(a+1,b,c); find(a,b+1,c); find(a,b,c+1);
    }

}


int main(){
    for(int i=0;i<3;i++) fin >> wanted[i];
    for(int i=0;i<3;i++)
        for(int j=0;j<3;j++) fin >> ratios[i][j];

    find(0,0,0);
    if(!arr[0][0][0][0] && !arr[0][0][0][1] && !arr[0][0][0][2])
        fout << "NONE" << endl;
    else{
        int a = arr[0][0][0][0];
        int b = arr[0][0][0][1];
        int c = arr[0][0][0][2];

        int r = (a*ratios[0][0] + b*ratios[1][0] + 
                c*ratios[2][0]) / wanted[0];
        fout << a << " " << b << " " << c << " " << r << endl;
    }
    return 0;
}
