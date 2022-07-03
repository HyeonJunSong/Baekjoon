#include <iostream>

using namespace std;

int main(){
    int x, y, w, h;
    cin >> x >> y >> w >> h;

    int min = 987654321;
    if(min > x - 0) min = x - 0;
    if(min > y - 0) min = y - 0;
    if(min > w - x) min = w - x;
    if(min > h - y) min = h - y;

    cout << min;

    return 0;

}