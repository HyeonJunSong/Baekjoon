#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <climits>

using namespace std;

#define ll long long

vector<ll> minDisSum;
vector<ll> minAccumSum;
vector<vector<ll>> dp;

void getAns(ll g, ll st, ll ed, ll optSt, ll optEd){

  if(st > ed) return;
  if(st == ed){
    for(ll i = optSt; i <= optEd; i++){
      ll curVal = dp[g - 1][i] + (st - i - 1) * (minAccumSum[st] - minAccumSum[i]);
      if(curVal < dp[g][st]){
        dp[g][st] = curVal;
      }
    }
    return;
  }

  ll opt = optSt;
  ll mid = (st + ed) / 2;
  for(ll i = optSt; i <= min(mid - 1, optEd); i++){
    ll curVal = dp[g - 1][i] + (mid - i - 1) * (minAccumSum[mid] - minAccumSum[i]);
    if(curVal < dp[g][mid]){
      dp[g][mid] = curVal;
      opt = i;
    }
  }

  getAns(g, st, mid - 1, optSt, opt);
  getAns(g, mid + 1, ed, opt, optEd);
}

int main(){

  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  int n, b, s, r;
  cin >> n >> b >> s >> r;

  vector<vector<pair<int, ll>>> graph(n + 1);
  vector<vector<pair<int, ll>>> graphRev(n + 1);

  for(int i = 0; i < r; i++){
    int u, v;
    ll l;
    cin >> u >> v >> l;
    graph[u].emplace_back(v, l);
    graphRev[v].emplace_back(u, l);
  }

  vector<ll> minDis(b + 1);
  vector<ll> minDisRev(b + 1);

  priority_queue<pair<ll, int>> PQ;
  vector<bool> visited;

  PQ.push({0, b + 1});
  visited = vector<bool>(n + 1, false);
  while(!PQ.empty()){
    pair<ll, int> curNode = PQ.top();
    PQ.pop();

    if(visited[curNode.second]) continue;
    visited[curNode.second] = true;

    if(curNode.second <= b)
      minDis[curNode.second] = -1 * curNode.first;

    for(auto e: graph[curNode.second]){
      if(visited[e.first]) continue;
      PQ.push({curNode.first - e.second, e.first});
    }
  }

  PQ.push({0, b + 1});
  visited = vector<bool>(n + 1, false);
  while(!PQ.empty()){
    pair<ll, int> curNode = PQ.top();
    PQ.pop();

    if(visited[curNode.second]) continue;
    visited[curNode.second] = true;

    if(curNode.second <= b)
      minDisRev[curNode.second] = -1 * curNode.first;

    for(auto e: graphRev[curNode.second]){
      if(visited[e.first]) continue;
      PQ.push({curNode.first - e.second, e.first});
    }
  }

  for(int i = 1; i <= b; i++)
    minDisSum.emplace_back(minDis[i] + minDisRev[i]);
  sort(minDisSum.begin(), minDisSum.end());
  
  minAccumSum = minDisSum;
  for(int i = 1; i < minDisSum.size(); i++)
    minAccumSum[i] += minAccumSum[i - 1];
  

  dp = vector<vector<ll>>(s + 1, vector<ll>(minDisSum.size(), LLONG_MAX));

  for(int i = 0; i < minDisSum.size(); i++)
    dp[1][i] = minAccumSum[i] * i;
  
  for(int i = 2; i <= s; i++)
    getAns(i, 0, minDisSum.size() - 1, i - 2, minDisSum.size() - 2);


  cout << dp[s][minDisSum.size() - 1];

  return 0;
}