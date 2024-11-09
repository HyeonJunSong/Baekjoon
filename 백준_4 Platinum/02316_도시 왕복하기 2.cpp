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
  levelOf = vector<int>(2 * N + 1, -1);
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

  graph.assign(2 * N + 1, {});
  capacity.assign(2 * N + 1, vector<int>(2 * N + 1, 0));
  flow.assign(2 * N + 1, vector<int>(2 * N + 1, 0));

  for(int p = 0; p < P; p++){
    int st, ed;
    cin >> st >> ed;
    if(st != 2 && ed != 1){
      graph[N + st].push_back(ed);
      graph[ed].push_back(N + st);
      capacity[N + st][ed] = INF;
    }
    if(ed != 2 && st != 1){
      graph[N + ed].push_back(st);
      graph[st].push_back(N + ed);
      capacity[N + ed][st] = INF;
    }
  }

  for(int i = 1; i <= N; i++){
    graph[i].push_back(N + i);
    graph[N + i].push_back(i);
    capacity[i][N + i] = 1;
  }
  capacity[1][N + 1] = INF;
  capacity[2][N + 2] = INF;

  int ans = 0;
  while(bfs()){
    edgeIdx = vector<int>(2 * N + 1, 0);

    while(true){
      int curFlow = dfs(1, INF);
      if(curFlow == 0) break;
      ans += curFlow;
    }
  }

  cout << ans;

  return 0;
}