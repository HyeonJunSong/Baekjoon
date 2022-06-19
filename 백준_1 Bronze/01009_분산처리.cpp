#include <iostream>

using namespace std;

int main(){
    int T;
    cin >> T;

    for(int i = 0; i < T; i++){
        int a, b;
        cin >> a >> b;
        int res = a % 10;
        for(int j = 1; j < b; j++){
            res *= a;
            res %= 10;
        }
        if(res == 0)
            cout << 10 << endl;
        else
            cout << res << endl;
    }
}