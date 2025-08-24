#include <iostream>
#include <vector>

using namespace std;

#define ll long long

int main(){

    while(true){
        ll n, m;
        cin >> n >> m;
        if(n == 0 && m == 0) break;

        if(n > m) swap(n, m);

        ll ans = 1;
        vector<bool> visited(n + 1, false);
        for(ll i = m + 1; i <= (n + m); i++) {
            ans *= i;
            for(ll i = 1; i <= n; i++) {
                if(ans % i) continue;
                if(visited[i]) continue;
                visited[i] = true;
                ans /= i;
            }
        }

        cout << ans << '\n';
    }


    return 0;
}