#include <iostream>
#include <string>
#include <queue>

using namespace std;

void testCase(){
    int l, m;
    cin >> l >> m;

    l *= 100;

    queue<int> L, R;

    for(int i = 0; i < m; i++){
        int length;
        string pos;
        cin >> length >> pos;
        if(pos[0] == 'l') L.push(length);
        else R.push(length);
    }

    int ans = 0;

    int curPos = 0;
    while(L.size() > 0 || R.size() > 0){
        if(curPos == 0 && L.size() > 0){
            int curSum = 0;
            while(L.size() > 0 && curSum + L.front() <= l){
                curSum += L.front();
                L.pop();
            }
        }
        if(curPos == 1 && R.size() > 0){
            int curSum = 0;
            while(R.size() > 0 && curSum + R.front() <= l){
                curSum += R.front();
                R.pop();
            }
        }
        ans++;
        curPos ^= 1;
    }

    cout << ans << '\n';
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int c;
    cin >> c;
    while(c-- >0) testCase();

    return 0;
}