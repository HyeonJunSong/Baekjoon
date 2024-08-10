#include <iostream>
#include <vector>

using namespace std;

int N, M;
vector<vector<int>> graph;

////도착 노드들
vector<int> matched;
vector<bool> visited;

bool tryMatch(int node){
  for(int i = 0; i < graph[node].size(); i++){
    if(visited[graph[node][i]]) continue;
    visited[graph[node][i]] = true;
    
    if(matched[graph[node][i]] == -1 || tryMatch(matched[graph[node][i]])){
      matched[graph[node][i]] = node;
      return true;
    }
  }
  return false;
}

int main(){

  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  cin >> N >> M;

  graph.assign(N + 1, {});
  for(int i = 0; i < M; i++){
    int a, b;
    cin >> a >> b;
    graph[a].push_back(b);
  }

  matched.assign(N + 1, -1);

  visited.assign(N + 1, false);

  int ans = 0;
  for(int i = 1; i <= N; i++){
    for(int j = 1; j <= N; j++)
      visited[j] = false;
    if(tryMatch(i)) ans++;
  }
  
  
  cout << ans;

  return 0;
}