#include <iostream>
#include <vector>
#include <queue>
#include <cmath>

using namespace std;

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int N, M;
  cin >> N >> M;

  vector<vector<vector<int>>> graph(N + 1);
  for(int i = 0, A, B, T, W; i < M; i++){
    cin >> A >> B >> T >> W;
    graph[A].push_back({B, T, W});
  }

  vector<int> visited(N + 1, 987654321);
  priority_queue<pair<int, int>> PQ;
  PQ.push({0, 1});

  while(!PQ.empty()){
    pair<int, int> curNode = PQ.top();
    PQ.pop();

    if(visited[curNode.second] <= -curNode.first) continue;
    visited[curNode.second] = -curNode.first;

    for(auto e: graph[curNode.second]){
      int nxtTime = (int)ceil((float)(-curNode.first) / e[2]) * e[2] + e[1];
      if(visited[e[0]] <= nxtTime) continue;
      PQ.push({-nxtTime, e[0]});
    }
  }

  cout << visited[N];

  return 0;
}