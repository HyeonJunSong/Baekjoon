#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class node{
public:
  int idx;
  int cLeft;
  int maxC;

  bool operator< (node b) const {
    return cLeft < b.cLeft;
  }
};

int main(){

  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int N, M, A, B, C;
  cin >> N >> M >> A >> B >> C;

  vector<vector<pair<int, int>>> graph(N + 1);
  for(int i = 0; i < M; i++){
    int st, ed, m;
    cin >> st >> ed >> m;

    graph[st].push_back({ed, m});
    graph[ed].push_back({st, m});
  }

  priority_queue<node> PQ;
  PQ.push({A, C, 0});

  vector<vector<bool>> visited(N + 1, vector<bool>(21, false));

  int ans = 987654321;

  while(!PQ.empty()){
    node curNode = PQ.top();
    PQ.pop();

    if(visited[curNode.idx][curNode.maxC]) continue;
      visited[curNode.idx][curNode.maxC] = true;
    
    if(curNode.idx == B){
      ans = min(ans, curNode.maxC);
      continue;
    }

    for(auto e: graph[curNode.idx]){
      if(curNode.cLeft - e.second < 0) continue;
      if(visited[e.first][max(curNode.maxC, e.second)]) continue;
      PQ.push({e.first, curNode.cLeft - e.second, max(curNode.maxC, e.second)});
    }
  }

  if(ans == 987654321){
    cout << -1;
  } else {
    cout << ans;
  }

  return 0;
}