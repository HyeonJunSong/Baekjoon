#include <iostream>
#include <vector>

using namespace std;

int main(){

  int N;
  cin >> N;
  int M;
  cin >> M;

  vector<vector<int>> graph(N + 1);
  for(int i = 0; i < M; i++){
    int st, ed;
    cin >> st >> ed;
    graph[st].push_back(ed);
    graph[ed].push_back(st);
  }

  int ans = 0;
  vector<bool> visited(N + 1, false);
  vector<int> stack;
  stack.push_back(1);

  while(!stack.empty()){
    int cur = stack.back();
    stack.pop_back();
    if(visited[cur]) continue;
    visited[cur] = true;
    ans++;
    for(int i = 0; i < graph[cur].size(); i++)
      stack.push_back(graph[cur][i]);
  }

  cout << ans - 1 << endl;

  return 0;
}