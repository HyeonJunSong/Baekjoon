#include <iostream>

using namespace std;

#define ll long long

int main(){
    ll N;
    cin >> N;
    ll A, B, C, D, E, F;
    cin >> A >> B >> C >> D >> E >> F;

    ll X = 0;
    for(ll i = (N / F) * F + 1; i <= N; i++){
        if(!(i % A)) X += i;
        if(!(i % B)) X %= i;
        if(!(i % C)) X &= i;
        if(!(i % D)) X ^= i;
        if(!(i % E)) X |= i;
    }
    cout << X;

    return 0;
}