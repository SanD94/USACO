/*
ID: safaand1
PROG: charrec
LANG: C++11
*/

#include<iostream>
#include<cstdio>
#include<queue>

using namespace std;

#define MIN_SELECT 19
#define CHAR_SIZE 27
#define MAX_CORRUPT 60*400

int chars[CHAR_SIZE][20];
char min_chars[1200][3];
int lines[1200];
bool mark[1200];
int sum_corrupt[1200];
int res[1200];
int min_chars_res[1200][3];
int N;

int get_corrupt(int num) {
    int res = 0;
    while(num) {
        if (num & 1) res ++;
        num >>= 1;
    }
    return res;
}

void get_characters() {
    cin >> N;
    string cur;
    getline(cin, cur);
    for(int i=0;i<N/20;i++)
        for(int j=0;j<20;j++) {
            getline(cin, cur);
            for(int k=0;k<20;k++) {
                chars[i][j] <<= 1;
                chars[i][j] |= cur[k]-'0';
            }
        }
}

void get_code() {
    cin >> N;
    string cur;
    getline(cin, cur);
    for(int i=0;i<N;i++) {
        getline(cin, cur);
        for(int j=0;j<20;j++) {
            lines[i] <<= 1;
            lines[i] |= cur[j] - '0';
        }
    }
}

int eval_min_char(int cur_char, int start, int select) {
    int min_res = 0;
    int diff_count = 0;
    for(int i=0;i<min(select,1)+MIN_SELECT;i++)
        diff_count += get_corrupt(lines[start+i]^chars[cur_char][i]);
    min_res = diff_count;
    if ( select == 0 )
        for(int i=MIN_SELECT-1;i>=0;i--) {
            diff_count -= get_corrupt(lines[start+i]^chars[cur_char][i]);
            diff_count += get_corrupt(lines[start+i]^chars[cur_char][i+1]);
            min_res = min(min_res, diff_count);
        }
    else if ( select == 2 ) {
        min_res = MAX_CORRUPT;
        for(int i=MIN_SELECT;i>=0;i--) {
            diff_count += get_corrupt(lines[start+i+1]^chars[cur_char][i]);
            min_res = min(min_res, diff_count);
            diff_count -= get_corrupt(lines[start+i]^chars[cur_char][i]);
        }
    }
    return min_res;
}

void eval_min(int start, int select) {
    int count[CHAR_SIZE];
    for(int i=0;i<CHAR_SIZE;i++)
        count[i] = eval_min_char(i, start, select);

    char res = ' ';
    int min_count = MAX_CORRUPT;
    for(int i=0;i<CHAR_SIZE;i++) {
        if ( min_count == count[i] ) res = '?';
        else if ( min_count > count[i] ) {
            min_count = count[i];
            if ( i == 0 ) res = ' ';
            else res = 'a'+i-1;
        }
    }
    if (min_count >= 120) min_count = MAX_CORRUPT;
    min_chars[start][select] = res;
    min_chars_res[start][select] = min_count;
}

void eval() {
    queue<int> Q;
    mark[0] = true;
    Q.push(0);
    while (!Q.empty()) {
        int cur = Q.front(); Q.pop();
        for(int i=0;i<3;i++) {
            if (MIN_SELECT + i + cur > N ) continue;
            eval_min(cur, i);
            if (!mark[cur + i + MIN_SELECT]) {
                mark[cur+i+MIN_SELECT] = true;
                Q.push(cur+i+MIN_SELECT);
            }
        }
    }
}

int find_min(int current) {
    if (current > N ) return MAX_CORRUPT;
    if (current == N) return 0;
    if (sum_corrupt[current] != -1)
        return sum_corrupt[current];
    int corrupt_count = MAX_CORRUPT;
    int index = -1;
    for(int i=0;i<3;i++) {
        int cur_count = find_min(current+i+MIN_SELECT)+min_chars_res[current][i];
        if (corrupt_count > cur_count) {
            index = i;
            corrupt_count = cur_count;
        }
    }
    res[current] = index;
    sum_corrupt[current] = corrupt_count;
    return sum_corrupt[current];
}

string print_code() {
    string res_string = "";
    int index = 0;
    while(index < N) {
        res_string += min_chars[index][res[index]];
        index += MIN_SELECT + res[index];
    }
    return res_string;
}



int main(int argc, char const* argv[]) {
    freopen("font.in", "r", stdin);
    get_characters();

    freopen("charrec.in", "r", stdin);
    freopen("charrec.out", "w", stdout);
    get_code();
    eval();
    for(int i=0;i<1200;i++) sum_corrupt[i] = -1;
    find_min(0);
    cout << print_code() << endl;
    return 0;
}
