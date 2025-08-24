#include <iostream>
#include <vector>

using namespace std;

int getGCD(int a, int b){
    while(a >= 1){
        int tmp = a;
        a = b % a;
        b = tmp;
    }
    return b;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int D1, D2;
    cin >> D1 >> D2;

    vector<vector<bool>> visited(2001, vector<bool>(2001, false));
    int ans = 0;
    for(int i = D1; i <= D2; i++){
        for(int j = 1; j <= i; j++){
            int gcd = getGCD(j, i);
            if(visited[i / gcd][j / gcd]) continue;
            visited[i / gcd][j / gcd] = true;
            ans++;
        }
    }

    cout << ans;

    return 0;
}