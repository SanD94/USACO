/*
ID: safaand1
PROG: ride
LANG: C++11
*/

#include <fstream>
#include <string>
#include <iostream>
using namespace std;

ifstream fin ("ride.in");
ofstream fout ("ride.out");

int main(){
    string group;
    string comet;
    int g=1,c=1;
    
    fin >> group >> comet; 
    int c_size = (int) comet.length();
    int g_size = (int) group.length();

    for(int i=0;i<c_size;i++) c*=comet[i]-'A'+1; c%=47;
    for(int i=0;i<g_size;i++) g*=group[i]-'A'+1; g%=47;

    if(g == c) fout << "GO" << endl;
    else fout << "STAY" << endl;
    return 0;
}
