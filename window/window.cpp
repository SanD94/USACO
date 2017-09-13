/*
ID: safaand1
LANG: C++11
PROG: window
*/

#include<iostream>
#include<cstdlib>
#include<cmath>
#include<iomanip>

using namespace std;

#define MAXWINDOW 150

struct Window {
    int x_min, x_max, y_min, y_max;
    int layer;
    bool added;
    int area();
} windows[MAXWINDOW];

int Window::area() {
    return (y_max-y_min) * (x_max-x_min);
}

int top, bottom;


float eval(Window current) {
    if ( current.x_min >= current.x_max || current.y_min >= current.y_max )
        return 0;
    for(int i=0;i<MAXWINDOW;i++)
        if (windows[i].added && windows[i].layer > current.layer) {
            Window top = windows[i];
            if (!(top.y_max <= current.y_min || current.y_max <= top.y_min
                        || top.x_max <= current.x_min || current.x_max <= top.x_min)) {
                Window a = { current.x_min, top.x_min, 
                    current.y_min, current.y_max, current.layer, true};
                Window b = { top.x_max, current.x_max,
                    current.y_min, current.y_max, current.layer, true};
                Window c = { max(top.x_min, current.x_min), min(current.x_max, top.x_max),
                    current.y_min, top.y_min, current.layer, true};
                Window d = { max(top.x_min, current.x_min), min(current.x_max, top.x_max),
                    top.y_max, current.y_max, current.layer, true};
                return eval(a) + eval(b) + eval(c) + eval(d);
            }
        }
    return current.area();
}


int main(int argc, char const* argv[]) {
    freopen("window.in", "r", stdin);
    freopen("window.out", "w", stdout);
    char command, dummy, location;
    int x1, x2, y1, y2;
    cout << fixed;
    while(cin >> command) {
        switch (command) {
            case 'w':
                cin >> dummy >> location
                    >> dummy >> x1 >> dummy >> y1
                    >> dummy >> x2 >> dummy >> y2 >> dummy;
                windows[location] = {
                    min(x1,x2), max(x1,x2), min(y1,y2), max(y1,y2),
                    top++, true
                };
                break;
            case 't':
                cin >> dummy >> location >> dummy;
                windows[location].layer = top++;
                break;
            case 'b':
                cin >> dummy >> location >> dummy;
                windows[location].layer = --bottom;
                break;
            case 'd':
                cin >> dummy >> location >> dummy;
                windows[location].added = false;
                break;
            case 's':
                cin >> dummy >> location >> dummy;
                int window_area = windows[location].area();
                cout << setprecision(3) << eval(windows[location])/window_area*100 << endl;
                break;
        }
    }
    return 0;
}
