#include <iostream>
#include <vector>

using namespace std;

#define ll long long

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int d;
    cin >> d;
    vector<ll> p(d);
    for(int i = 0; i < d; i++) cin >> p[i];

    ll stock = 0;
    ll cash = 100;

    for(int i = 1; i < d; i++){
        if(p[i - 1] < p[i]){
            stock = min(100000LL, cash / p[i - 1]);
            cash -= stock * p[i - 1];
        }
        cash += stock * p[i];
        stock = 0;
    }
    cout << cash;

    return 0;
}