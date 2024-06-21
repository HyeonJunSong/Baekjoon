#include <iostream>
#include <cmath>

using namespace std;

#define ll long long

int main(){

  ios_base::sync_with_stdio(false);
  cout.tie(NULL);

  ll N;
  cin >> N;

  for(ll i = 1; i < N; i++)
    cout << i * 2 << " ";
  
  for(ll i = N * (N + 1) / 2; true; i++){
    
    bool ifPrime = true;
    for(ll j = 2; j <= (ll)sqrt(i); j++){
      if(i % j == 0){
        ifPrime = false;
        break;
      }
    }

    if(ifPrime){
      cout << i * 2 - (N) * (N - 1);
      break;
    }

  }

  return 0;
}