/*
ID: safaand1
PROG: test
LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

ifstream fin ("test.in");
ofstream fout ("test.out");

int main(){
    int a,b;
    fin >> a >> b;
    fout << a+b << endl;

    return 0;
}
