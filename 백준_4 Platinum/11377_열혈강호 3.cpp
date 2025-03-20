#include <iostream>
#include <vector>

using namespace std;

#define MAX_VERTEX 2003
#define INF 987654321

int flow[MAX_VERTEX][MAX_VERTEX];
int cap[MAX_VERTEX][MAX_VERTEX];

vector<int> graph[MAX_VERTEX];
int nxtV[MAX_VERTEX];
int src, snk;

int dfs(int v, int curFlow){
  if(v == snk) return curFlow;

  while(nxtV[v] < graph[v].size()){
    int nxt = graph[v][nxtV[v]++];
    if(flow[v][nxt] == cap[v][nxt]) continue;

    int totFlow = dfs(nxt, min(curFlow, cap[v][nxt] - flow[v][nxt]));
    if(totFlow == 0) continue;

    flow[v][nxt] += totFlow;
    flow[nxt][v] -= totFlow;
    return totFlow;
  }

  return 0;
}

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  //입력 & 그래프 초기화
  int N, M, K;
  cin >> N >> M >> K;

  for(int cnt, i = 0; i < N; i++){
    cin >> cnt;
    for(int work, j = 0; j < cnt; j++){
      cin >> work; work--;
      cap[i][N + work] = 1;
      graph[i].push_back(N + work);
      graph[N + work].push_back(i);
    }
  }

  src = N + M;
  snk = N + M + 1;

  for(int i = 0; i < N; i++){
    cap[src][i] = 1;
    graph[src].push_back(i);
    graph[i].push_back(src);
  }
  for(int i = 0; i < M; i++){
    cap[N + i][snk] = 1;
    graph[N + i].push_back(snk);
    graph[snk].push_back(N + i);
  }

  //최대유량
  for(int i = 0; i < N; i++){
    for(int j = 0; j < MAX_VERTEX; j++) nxtV[j] = 0;
    dfs(i, INF);
  }
  for(int i = 0; i < K; i++){
    for(int j = 0; j < MAX_VERTEX; j++) nxtV[j] = 0;
    dfs(src, INF);
  }


  //해 구하기
  int ans = 0;
  for(int i = 0; i < M; i++) ans += flow[N + i][snk];

  cout << ans;

  return 0;
}