#include <iostream>
#include <vector>
#include <queue>

using namespace std;

#define INF 987654321

int N, P;
vector<vector<int>> graph;
vector<vector<int>> capacity;
vector<vector<int>> flow;
vector<int> levelOf;
vector<int> edgeIdx;


bool bfs(){
  levelOf = vector<int>(N + 1, -1);
  queue<int> Q;
  Q.push(1);
  levelOf[1] = 0;

  while(!Q.empty()){
    int cur = Q.front();
    Q.pop();

    for(auto e: graph[cur]){
      if(levelOf[e] != -1) continue;
      if(capacity[cur][e] - flow[cur][e] <= 0) continue;

      levelOf[e] = levelOf[cur] + 1;
      Q.push(e);
    }
  }

  return levelOf[2] != -1;
}

int dfs(int cur, int curFlow){
  if(cur == 2) return curFlow;

  for(; edgeIdx[cur] < graph[cur].size(); edgeIdx[cur]++){
    int nxt = graph[cur][edgeIdx[cur]];
    
    if(levelOf[nxt] - levelOf[cur] != 1) continue;
    if(capacity[cur][nxt] - flow[cur][nxt] <= 0) continue;

    int nxtFlow = dfs(nxt, min(curFlow, capacity[cur][nxt] - flow[cur][nxt]));
    if(nxtFlow == 0) continue;

    flow[cur][nxt] += nxtFlow;
    flow[nxt][cur] -= nxtFlow;

    return nxtFlow;
  }

  return 0;
}

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  
  cin >> N >> P;

  graph.assign(N + 1, {});
  capacity.assign(N + 1, vector<int>(N + 1, 0));
  flow.assign(N + 1, vector<int>(N + 1, 0));

  for(int p = 0; p < P; p++){
    int st, ed;
    cin >> st >> ed;
    graph[st].push_back(ed);
    graph[ed].push_back(st);
    capacity[st][ed] += 1;
  }

  int ans = 0;
  while(bfs()){
    edgeIdx = vector<int>(N + 1, 0);

    while(true){
      int curFlow = dfs(1, INF);
      if(curFlow == 0) break;
      ans += curFlow;
    }
  }

  cout << ans;

  return 0;
}