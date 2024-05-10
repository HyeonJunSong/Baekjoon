#include <iostream>
#include <vector>
#include <climits>

#define ll long long

using namespace std;

ll L;
ll G;
vector<ll> C;

vector<ll> accArr;

vector<vector<ll>> dp;

void getAns(ll g, ll st, ll ed, ll optSt, ll optEd){

  if(st > ed) return;
  if(st == ed){
    for(ll i = optSt; i <= optEd; i++){
      ll curVal = dp[g - 1][i] + (st - i) * (accArr[st] - accArr[i]);
      if(curVal < dp[g][st]){
        dp[g][st] = curVal;
      }
    }
    return;
  }

  ll opt = optSt;
  ll mid = (st + ed) / 2;
  for(ll i = optSt; i <= min(mid - 1, optEd); i++){
    ll curVal = dp[g - 1][i] + (mid - i) * (accArr[mid] - accArr[i]);
    if(curVal < dp[g][mid]){
      dp[g][mid] = curVal;
      opt = i;
    }
  }

  getAns(g, st, mid - 1, optSt, opt);
  getAns(g, mid + 1, ed, opt, optEd);
}

int main(){

  cin >> L >> G;
  C = vector<ll>(L);
  for(int i = 0; i < L; i++)
    cin >> C[i];

  accArr = C;
  for(int i = 1; i < L; i++)
    accArr[i] += accArr[i - 1];
  
  dp = vector<vector<ll>>(G + 1, vector<ll>(L, LLONG_MAX));
  for(ll i = 0; i < L; i++)
    dp[1][i] = (i + 1) * accArr[i];
  
  for(ll g = 2; g <= min(L, G); g++)
    getAns(g, 0, L - 1, g - 2, L - 2);
  
  cout << dp[min(L, G)][L - 1];

  return 0;
}