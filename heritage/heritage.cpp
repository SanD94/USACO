/*
ID: safaand1
PROG: heritage
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

ifstream fin("heritage.in");
ofstream fout("heritage.out");

string inorder;
string preorder;

void print(string ino, string preo){
    if(ino.length() == 0) return;
    int cutp = 0;
    for( ; ino[cutp]!=preo[0]; cutp++);
    print(ino.substr(0,cutp), preo.substr(1,cutp));
    print(ino.substr(cutp+1), preo.substr(cutp+1));
    fout << preo[0];
}


int main(){

    fin >> inorder;
    fin >> preorder;
    print(inorder, preorder);
    fout << endl;

    return 0;
}
