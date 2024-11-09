#include <iostream>
#include <vector>
#include <queue>

using namespace std;

#define INF 987654321

class Graph{
  public:
  vector<vector<int>> graph;

  int src, snk;
  vector<vector<int>> capacity;
  vector<vector<int>> flow;
  vector<int> levelOf;
  vector<int> edgeIdx;

  bool bfs(){
    fill(levelOf.begin(), levelOf.end(), -1);

    queue<int> Q;
    Q.push(src);
    levelOf[src] = 0;

    while(!Q.empty()){
      int cur = Q.front();
      Q.pop();

      for(auto e: graph[cur]){
        if(levelOf[e] != -1) continue;
        if(capacity[cur][e] <= flow[cur][e]) continue;
        Q.push(e);
        levelOf[e] = levelOf[cur] + 1;
      }
    }

    return levelOf[snk] != -1;
  }

  int dfs(int cur, int curFlow){
    if(cur == snk) return curFlow;

    for(int i = edgeIdx[cur]; i < graph[cur].size(); i++){
      int nxt = graph[cur][i];
      if(levelOf[nxt] - levelOf[cur] != 1) continue;
      if(capacity[cur][nxt] <= flow[cur][nxt]) continue;
      int nxtFlow = dfs(nxt, min(curFlow, capacity[cur][nxt] - flow[cur][nxt]));
      if(nxtFlow == 0) continue;
      flow[cur][nxt] += nxtFlow;
      flow[nxt][cur] -= nxtFlow;
      return nxtFlow;
    }

    return 0;
  }

  int dinic(){
    int totFlow = 0;

    while(bfs()){
      fill(edgeIdx.begin(), edgeIdx.end(), 0);
      while(true){
        int curFlow = dfs(src, INF);
        if(curFlow == 0) break;
        totFlow += curFlow;
      }
    }

    return totFlow;
  }

};

int dir[4][2] = {
  {-1,  0},
  { 1,  0},
  { 0, -1},
  { 0,  1},
};

void testCase(){
  int n, m;
  cin >> n >> m;

  Graph G;
  G.graph.assign(n * m + 2, {});
  G.capacity.assign(n * m + 2, vector<int>(n * m + 2, 0));
  G.flow.assign(n * m + 2, vector<int>(n * m + 2, 0));
  G.levelOf.assign(n * m + 2, -1);
  G.edgeIdx.assign(n * m + 2, -1);

  G.src = n * m;
  G.snk = n * m + 1;

  for(int i = 0; i < n; i++){
    for(int j = 0; j < m; j++){
      if((i + j) % 2 == 0){
        G.graph[G.src].push_back(m * i + j);
        G.graph[m * i + j].push_back(G.src);
        cin >> G.capacity[G.src][m * i + j];
      } else {
        G.graph[G.snk].push_back(m * i + j);
        G.graph[m * i + j].push_back(G.snk);
        cin >> G.capacity[m * i + j][G.snk];
      }
    }
  }

  for(int i = 0; i < n; i++){
    for(int j = 0; j < m; j++){
      for(int d = 0; d < 4; d++){
        if(0 <= i + dir[d][0] && i + dir[d][0] < n
        && 0 <= j + dir[d][1] && j + dir[d][1] < m){
          G.graph[m * i + j].push_back(m * (i + dir[d][0]) + j + dir[d][1]);

          if((i + j) % 2 == 0)
            G.capacity[m * i + j][m * (i + dir[d][0]) + j + dir[d][1]] = INF;
        }
      }
    }
  }

  int ans = G.dinic();

  for(int i = 0; i < n; i++){
    for(int j = 0; j < m; j++){
      if((i + j) % 2 == 0)
        ans += G.capacity[G.src][m * i + j] - G.flow[G.src][m * i + j];
      else
        ans += G.capacity[m * i + j][G.snk] - G.flow[m * i + j][G.snk];
    }
  }

  cout << ans << '\n';


}

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  int T;
  cin >> T;
  for(int t = 0; t < T; t++)
    testCase();

  return 0;
}