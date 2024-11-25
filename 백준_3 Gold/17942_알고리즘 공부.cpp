#include <iostream>
#include <vector>
#include <queue>

using namespace std;

#define ll long long

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int N, M;
  cin >> N >> M;

  priority_queue<pair<ll, int>> PQ;
  vector<int> efforts(N + 1);
  for(int i = 1, effort; i <= N; i++){
    cin >> effort;
    efforts[i] = effort;
    PQ.push({-effort, i});
  }

  int R;
  cin >> R;
  vector<vector<pair<int, ll>>> graph(N + 1);
  for(int i = 0, A, B, D; i < R; i++){
    cin >> A >> B >> D;
    graph[A].push_back({B, (ll)D});
  }

  ll ans = 0;
  vector<bool> visited(N + 1, false);
  while(true){
    pair<ll, int> curNode = PQ.top();
    PQ.pop();

    if(visited[curNode.second]) continue;
    visited[curNode.second] = true;

    M--;
    ans = max(ans, -curNode.first);
    if(M == 0) break;

    for(auto e: graph[curNode.second]){
      if(visited[e.first]) continue;
      efforts[e.first] -= e.second;
      PQ.push({-efforts[e.first], e.first});
    }
  }

  cout << ans;

  return 0;
}