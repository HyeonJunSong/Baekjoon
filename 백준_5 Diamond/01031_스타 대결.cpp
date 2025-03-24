#include <iostream>
#include <vector>
#include <queue>

using namespace std;

#define INF 987654321
#define VNUM 110

int cap[VNUM][VNUM];
int flw[VNUM][VNUM];
vector<int> graph[VNUM];
int src, snk;

int edgeIdx[VNUM];
int levelOf[VNUM];

int dfs(int v, int flow){
  if(v == snk) return flow;

  while(edgeIdx[v] < graph[v].size()){
    int nxt = graph[v][edgeIdx[v]++];

    if(levelOf[nxt] - levelOf[v] != 1) continue;
    if(flw[v][nxt] >= cap[v][nxt]) continue;

    int nxtFlow = dfs(nxt, min(flow, cap[v][nxt] - flw[v][nxt]));
    if(nxtFlow == 0) continue;

    flw[v][nxt] += nxtFlow;
    flw[nxt][v] -= nxtFlow;

    return nxtFlow;
  }

  return 0;
}

bool bfs(){

  queue<int> Q; Q.push(src);
  for(int i = 0; i < VNUM; i++) levelOf[i] = -1;
  levelOf[src] = 0;

  while(!Q.empty()){
    int cur = Q.front(); Q.pop();
    for(auto nxt: graph[cur]){
      if(levelOf[nxt] != -1) continue;
      if(flw[cur][nxt] >= cap[cur][nxt]) continue;
      levelOf[nxt] = levelOf[cur] + 1;
      Q.push(nxt);
    }
  }

  return levelOf[snk] != -1;
}

int dinic(){
  int maxFlow = 0;
  while(bfs()){
    for(int i = 0; i < VNUM; i++) edgeIdx[i] = 0;
    while(int curFlow = dfs(src, INF)) maxFlow += curFlow;
  }
  return maxFlow;
}

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);
  
  int N, M;
  cin >> N >> M;
  
  src = N + M;
  snk = N + M + 1;
  
  for(int i = 0; i < N; i++){
    cin >> cap[src][i];
    graph[src].push_back(i);
  }
  
  for(int i = 0; i < M; i++){
    cin >> cap[N + i][snk];
    graph[N + i].push_back(snk);
  }
  
  for(int i = 0; i < N; i++){
    for(int j = 0; j < M; j++){
      cap[i][N + j] = 1;
      graph[i].push_back(N + j);
      graph[N + j].push_back(i);
    }
  }


  dinic();

  for(int i = 0; i < N; i++){
    if(flw[src][i] == cap[src][i]) continue;
    cout << -1;
    return 0;
  }
  for(int i = 0; i < M; i++){
    if(flw[N + i][snk] == cap[N + i][snk]) continue;
    cout << -1;
    return 0;
  }

  for(int i = 0; i < N; i++){
    for(int j = 0; j < M; j++){
      cap[i][N + j] = 0;
      if(flw[i][N + j] == 0) continue;
      for(int k = 0; k < VNUM; k++) edgeIdx[k] = 0;

      src = i; snk = N + j;
      bfs();
      int curFlow = dfs(src, INF);
      if(curFlow) flw[i][N + j] -= 1;
    }
  }

  for(int i = 0; i < N; i++){
    for(int j = 0; j < M; j++){
      if(flw[i][N + j]) cout << '1';
      else cout << '0';
    }
    cout << '\n';
  }


  return 0;
}