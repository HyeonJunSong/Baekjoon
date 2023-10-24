////231024
//33m 24s

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

#define INF 987654321

int main(){
  int N;
  cin >> N;
  int A, B, C;
  cin >> A >> B >> C;

  int M;
  cin >> M;
  vector<vector<pair<int, int>>> city(N + 1);
  for(int i = 0; i < M; i++){
    int st, ed, l;
    cin >> st >> ed >> l;

    city[st].push_back({ed, l});
    city[ed].push_back({st, l});
  }

  vector<vector<int>> disFrom(3, vector<int>(N + 1, INF));

  //A로부터 다익스트라
  priority_queue<pair<int, int>> PQ;
  vector<bool> visited(N + 1, false);
  PQ.push({0, A});

  while(!PQ.empty()){
    pair<int, int> curNode = PQ.top();
    PQ.pop();

    if(visited[curNode.second]) continue;
    visited[curNode.second] = true;
    disFrom[0][curNode.second] = -1 * curNode.first;
    
    for(auto e: city[curNode.second]){
      if(visited[e.first]) continue;
      PQ.push({curNode.first - e.second, e.first});
    }
  }

  //B로부터 다익스트라
  visited = vector<bool>(N + 1, false);
  PQ.push({0, B});

  while(!PQ.empty()){
    pair<int, int> curNode = PQ.top();
    PQ.pop();

    if(visited[curNode.second]) continue;
    visited[curNode.second] = true;
    disFrom[1][curNode.second] = -1 * curNode.first;
    
    for(auto e: city[curNode.second]){
      if(visited[e.first]) continue;
      PQ.push({curNode.first - e.second, e.first});
    }
  }

  //C로부터 다익스트라
  visited = vector<bool>(N + 1, false);
  PQ.push({0, C});

  while(!PQ.empty()){
    pair<int, int> curNode = PQ.top();
    PQ.pop();

    if(visited[curNode.second]) continue;
    visited[curNode.second] = true;
    disFrom[2][curNode.second] = -1 * curNode.first;
    
    for(auto e: city[curNode.second]){
      if(visited[e.first]) continue;
      PQ.push({curNode.first - e.second, e.first});
    }
  }

  vector<int> minDisFrom(N + 1, INF);
  for(int i = 1; i <= N; i++)
    for(int j = 0; j < 3; j++)
      if(minDisFrom[i] > disFrom[j][i])
        minDisFrom[i] = disFrom[j][i];
  
  int maxDis = 0;
  for(int i = 1; i <= N; i++)
    if(maxDis < minDisFrom[i])
      maxDis = minDisFrom[i];

  for(int i = 1; i <= N; i++)
    if(maxDis == minDisFrom[i]){
      cout << i;
      break;
    }

  return 0;
}