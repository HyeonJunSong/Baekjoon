#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  int N, M, st;
  cin >> N >> M >> st;
  st--;
  vector<vector<int>> graph(N);
  int u, v;
  for(int i = 0; i < M; i++){
    cin >> u >> v;
    u--; v--;
    graph[u].push_back(v);
    graph[v].push_back(u);
  }

  vector<int> levelOf(N, -1);
  queue<int> Q;
  Q.push(st);
  levelOf[st] = 0;
  while(!Q.empty()){
    int curNode = Q.front();
    Q.pop();

    for(int i = 0; i < graph[curNode].size(); i++){
      if(levelOf[graph[curNode][i]] != -1) continue;
      levelOf[graph[curNode][i]] = levelOf[curNode] + 1;
      Q.push(graph[curNode][i]);
    }
  }

  for(auto e: levelOf)
    cout << e << "\n";


  return 0;
}