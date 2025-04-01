#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

void solve(){
    int N, L;
    cin >> N >> L;

    vector<int> outlets;
    vector<int> devices;

    for(int i = 0; i < N; i++){
        string inp;
        cin >> inp;
        int curInp = 0;
        for(int j = 0, cur = 1; j < L; j++ & (cur <<= 1)){
            if(inp[j] == '0') continue;
            curInp += cur;
        }
        outlets.push_back(curInp);
    }

    for(int i = 0; i < N; i++){
        string inp;
        cin >> inp;
        int curInp = 0;
        for(int j = 0, cur = 1; j < L; j++ & (cur <<= 1)){
            if(inp[j] == '0') continue;
            curInp += cur;
        }
        devices.push_back(curInp);
    }

    sort(devices.begin(), devices.end());

    int ans = 987654321;

    int maxBit = 1 << L;
    for(int i = 0; i < maxBit; i++){
        vector<int> newOutlets(outlets);
        for(int j = 0; j < N; j++) newOutlets[j] ^= i;
        sort(newOutlets.begin(), newOutlets.end());

        bool ifPossible = true;
        for(int j = 0; j < N; j++){
            if(newOutlets[j] == devices[j]) continue;
            ifPossible = false;
            break;
        }

        if(!ifPossible) continue;
        int curBitCnt = 0;
        for(int j = i; j > 0; j >>= 1){
            if(j % 2 == 0) continue;
            curBitCnt++;
        }
        ans = min(ans, curBitCnt);
    }

    if(ans == 987654321) cout << "NOT POSSIBLE\n";
    else cout << ans << '\n';
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    cin >> T;

    for(int t = 0; t < T; t++){
        cout << "Case #" << t + 1 << ": ";
        solve();
    }

    return 0;
}