#include <iostream>
#include <vector>
#include <cmath>
#include <queue>
#include <cstdio>

using namespace std;

int main(){

  int n;
  cin >> n;
  
  vector<pair<float, float>> stars(n);
  for(int i = 0; i < n; i++)
    cin >> stars[i].first >> stars[i].second;
  
  vector<vector<float>> graph(n, vector<float>(n, 0));
  for(int i = 0; i < n; i++){
    for(int j = 0; j < n; j++){
      graph[i][j] = sqrt(pow(stars[i].first - stars[j].first, 2) + pow(stars[i].second - stars[j].second, 2));
      graph[j][i] = graph[i][j];
    }
  }

  priority_queue<pair<float, int>> PQ;
  PQ.push({0.0, 0});

  vector<bool> visited(n, false);

  float ans = 0.0;
  while(!PQ.empty()){
    auto curNode = PQ.top();
    PQ.pop();

    if(visited[curNode.second]) continue;
      visited[curNode.second] = true;
    
    ans -= curNode.first;

    for(int i = 0; i < n; i++){
      if(visited[i]) continue;
      PQ.push({-1 * graph[curNode.second][i], i});
    }
  }

  printf("%.5f", ans);

  return 0;
}