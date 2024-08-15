#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  int N, M;
  cin >> N >> M;
  vector<vector<int>> graph(N + 1);
  for(int i = 0; i < M; i++){
    int st, ed;
    cin >> st >> ed;
    graph[st].push_back(ed);
  }

  vector<int> parentOf(N + 1, -1);
  for(int i = 1; i <= N; i++)
    for(auto e: graph[i])
      parentOf[e] = i;
  for(int i = 1; i <= N; i++)
    if(parentOf[i] == -1)
      graph[0].push_back(i);

  vector<int> levelOf(N + 1, 0);
  queue<int> Q;
  Q.push(0);
  while(!Q.empty()){
    int curNode = Q.front();
    Q.pop();

    for(auto e: graph[curNode]){
      if(levelOf[e] > levelOf[curNode]) continue;
      levelOf[e] = levelOf[curNode] + 1;
      Q.push(e);
    }
  }

  for(int i = 1; i <= N; i++)
    cout << levelOf[i] << " ";

  return 0;
}