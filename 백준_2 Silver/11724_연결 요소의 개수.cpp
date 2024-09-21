#include <iostream>
#include <vector>

using namespace std;

int main(){
  int N, M;
  cin >> N >> M;
  vector<vector<int>> graph(N+1);

  for(int i = 0; i < M; i++){
    int st, ed;
    cin >> st >> ed;
    graph[st].push_back(ed);
    graph[ed].push_back(st);
  }

  int ans = 0;
  vector<bool> visited(N + 1, false);
  for(int i = 1; i <= N; i++){
    if(visited[i]) continue;
    ans++;

    vector<int> stack(1, i);
    while(!stack.empty()){
      int curNode = stack.back();
      stack.pop_back();

      for(auto e: graph[curNode]){
        if(visited[e]) continue;
        visited[e] = true;
        stack.push_back(e);
      }
    }
  }

  cout << ans;

  return 0;
}