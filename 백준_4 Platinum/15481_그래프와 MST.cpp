#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

#define MAX_VERTEX 200000
#define LOG 20
int spTable[MAX_VERTEX + 1][LOG + 1] = {0};
int spTableMax[MAX_VERTEX + 1][LOG + 1] = {0};
int levelOf[MAX_VERTEX] = {0};

vector<vector<pair<int, int>>> graph;
void dfs(int curV, int prvV, int level){
  levelOf[curV] = level;

  for(auto e: graph[curV]){
    if(e.first == prvV) continue;

    spTable[e.first][0] = curV;
    spTableMax[e.first][0] = e.second;
    dfs(e.first, curV, level + 1);
  }

}

int lca(int a, int b){
  int curMaxEdge = 0;

  while(levelOf[a] > levelOf[b]){
    curMaxEdge = max(curMaxEdge, spTableMax[a][(int)floor(log2(levelOf[a] - levelOf[b]))]);
    a = spTable[a][(int)floor(log2(levelOf[a] - levelOf[b]))];
  }
  while(levelOf[a] < levelOf[b]){
    curMaxEdge = max(curMaxEdge, spTableMax[b][(int)floor(log2(levelOf[b] - levelOf[a]))]);
    b = spTable[b][(int)floor(log2(levelOf[b] - levelOf[a]))];
  }

  while(a != b){
    int st = 1, ed = LOG;
    while(st <= ed){
      int mid = (st + ed) / 2;
      if(spTable[a][mid] == spTable[b][mid])
        ed = mid - 1;
      else
        st = mid + 1;
    }

    curMaxEdge = max(curMaxEdge, spTableMax[a][ed]);
    curMaxEdge = max(curMaxEdge, spTableMax[b][ed]);
    a = spTable[a][ed];
    b = spTable[b][ed];
  }

  return curMaxEdge;
}

vector<int> groupOf;
int findGroup(int v){
  if(groupOf[v] == v) return v;

  int curV = v;
  while(groupOf[curV] != curV)
    curV = groupOf[curV];
  
  groupOf[v] = curV;

  return curV;
}
void unionGroup(int v, int w){
  v = findGroup(v);
  w = findGroup(w);

  if(v < w) groupOf[w] = v;
  else groupOf[v] = w;
}

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  int N, M;
  cin >> N >> M;

  vector<vector<int>> edges(M, vector<int>(4));
  for(int i = 0; i < M; i++){
    int st, ed, weight;
    cin >> st >> ed >> weight;

    edges[i][0] = weight;
    edges[i][1] = st;
    edges[i][2] = ed;
    edges[i][3] = i;
  }

  vector<bool> isMSTEdge(M, false);
  groupOf.assign(N + 1, 0);
  for(int i = 1; i <= N; i++)
    groupOf[i] = i;
  
  sort(edges.begin(), edges.end());
  graph.assign(N + 1, {});

  long long mstWeight = 0;
  for(int i = 0; i < M; i++){
    if(findGroup(edges[i][1]) == findGroup(edges[i][2])) continue;
    isMSTEdge[edges[i][3]] = true;
    graph[edges[i][1]].push_back({edges[i][2], edges[i][0]});
    graph[edges[i][2]].push_back({edges[i][1], edges[i][0]});

    unionGroup(edges[i][1], edges[i][2]);
    mstWeight += edges[i][0];
  }

  dfs(1, 1, 1);

  for(int j = 1; j <= LOG; j++){
    for(int i = 1; i <= N; i++){
      spTable[i][j] = spTable[spTable[i][j - 1]][j - 1];
      spTableMax[i][j] = max(spTableMax[i][j - 1], spTableMax[spTable[i][j - 1]][j - 1]);
    }
  }

  vector<long long> ans(M);

  for(int i = 0; i < M; i++){
    if(isMSTEdge[edges[i][3]]){
      ans[edges[i][3]] = mstWeight;
      continue;
    }

    ans[edges[i][3]] = mstWeight + edges[i][0] - lca(edges[i][1], edges[i][2]);
  }

  for(auto e: ans)
    cout << e << '\n';

  return 0;
}