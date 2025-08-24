#include <iostream>
#include <vector>
#include <map>

using namespace std;

#define ll long long

ll N, P, Q, X, Y;

map<ll, ll> memo;

ll getAns(ll n){
    if(n <= 0) return 1;

    if(memo.find(n) != memo.end()) return memo[n];

    ll ans = getAns(n / P - X) + getAns(n / Q - Y);
    memo[n] = ans;

    return ans;
}

int main(){

    cin >> N >> P >> Q >> X >> Y;

    cout << getAns(N);

    return 0;
}