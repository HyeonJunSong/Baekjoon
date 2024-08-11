#include <iostream>
#include <vector>

using namespace std;

int N, M;
vector<vector<int>> graph;
vector<int> matched;
vector<bool> visited;
bool tryMatch(int person){

  for(int i = 0; i < graph[person].size(); i++){
    if(visited[graph[person][i]]) continue;
    visited[graph[person][i]] = true;

    if(matched[graph[person][i]] == -1 || tryMatch(matched[graph[person][i]])){
      matched[graph[person][i]] = person;
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
  graph.assign(N, {});
  for(int i = 0; i < N; i++){
    int workNum;
    cin >> workNum;
    graph[i].assign(workNum, 0);
    for(int j = 0; j < workNum; j++)
      cin >> graph[i][j];
  }
  matched.assign(M + 1, -1);

  for(int i = 0; i < N; i++){
    visited.assign(M + 1, false);
    tryMatch(i);
    visited.assign(M + 1, false);
    tryMatch(i);
  }

  int ans = 0;
  for(int i = 1; i <= M; i++)
    if(matched[i] != -1) ans++;
  
  cout << ans;

  return 0;
}