#include <iostream>
#include <vector>

#define ll long long

using namespace std;

vector<ll> fact(4000001, -1);
vector<ll> fact_div(4000001, -1);

ll p = 1000000007;
ll getInvolution(ll a){
  ll ans = 1;
  ll curInv = a;
  ll invNum = p - 2;
  
  while(invNum > 0){
    if (invNum % 2 == 1)
      ans = (ans * curInv) % p;
    
    curInv = (curInv * curInv) % p;
    invNum >>= 1;
  }
    
  return ans;
}
  
int factSize = 2;
int factDivSize = 2;

int forCnt = 0;
ll nCm(ll n, ll m){
  if (factSize <= n){
    for(ll i = factSize; i < n + 1; i++)
      fact[i] = ((fact[i - 1] * i) % p);
    factSize = n + 1;
  }
  ll ans = fact[n];
  
  if(factDivSize <= max(m, n - m)){
    for(ll i = factDivSize; i < max(m, n - m) + 1; i++)
      fact_div[i] = ((fact_div[i - 1] * getInvolution(i)) % p);
    factDivSize = max(m, n - m) + 1;
  }
  
  ans = (ans * fact_div[m]) % p;
  ans = (ans * fact_div[n - m]) % p;
  
  return ans;
}

int main(){
  
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  ll T;

  cin >> T;

  fact[0] = 1;
  fact[1] = 1;
  fact_div[0] = 1;
  fact_div[1] = 1;

  for(int i = 0; i < T; i++){
    ll N, K;
    cin >> N >> K;
    cout << nCm(N, K) << "\n";
  }

  return 0;
}