#include <iostream>

using namespace std;

int main(){

    int N;
    cin >> N;

    int tot = 0;
    int cur = N;
    tot += cur / 5;
    cur %= 5;

    while(cur <= N){
        if(cur % 3 == 0){
            tot += cur / 3;
            break;
        }
        tot--;
        cur += 5;
    }

    if(cur > N) cout << -1;
    else cout << tot;

    return 0;
}