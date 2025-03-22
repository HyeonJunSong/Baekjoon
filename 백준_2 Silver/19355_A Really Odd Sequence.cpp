#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

#define ll long long

void testCase(){
    int n;
    cin >> n;
    vector<ll> arr(n);
    for(int i = 0; i < n; i++) cin >> arr[i];
    for(int i = 1; i < n; i++) arr[i] += arr[i - 1];

    ll oddMin = LLONG_MAX;
    ll evenMin = LLONG_MAX;
    ll ans = LLONG_MIN;

    oddMin = 0;

    for(int i = 0; i < n; i++){
        if(i % 2){
            ans = max(ans, arr[i] - evenMin);
            oddMin = min(oddMin, arr[i]);
        } else {
            ans = max(ans, arr[i] - oddMin);
            evenMin = min(evenMin, arr[i]);
        }
    }

    cout << ans << '\n';
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int t; cin >> t;
    while(t--) testCase();

    return 0;
}