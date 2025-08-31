#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#define ll long long

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N;
    cin >> N;

    vector<ll> C((N * (N - 1)) / 2); 

    for(int i = 0; i < C.size(); i++) cin >> C[i];

    sort(C.begin(), C.end());

    ll mCst = 0;
    for(int i = 0; i < N - 1; i++) mCst += C[i];

    ll lCst = C[0];
    for(int i = 2; i <= N - 1; i++) lCst += C[(i * (i - 1)) / 2];

    cout << mCst << ' ' << lCst;

    return 0;
}