#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

//Graph
int V, E;
vector<vector<int>> edges;

//Union-Find
vector<int> groupOf;
int getGroup(int v){
  if(v != groupOf[v]) groupOf[v] = getGroup(groupOf[v]);
  return groupOf[v];
}
void unionGroup(int v1, int v2){
  v1 = getGroup(v1);
  v2 = getGroup(v2);

  if(v1 < v2)
    groupOf[v2] = v1;
  else
    groupOf[v1] = v2;
}

//LCA
vector<int> levelOf;
vector<vector<int>> spTable;
vector<vector<int>> spTableMax;
vector<vector<int>> spTable2ndMax;
void initSpTable(){

  for(int j = 1; j < 20; j++){
    for(int i = 0; i < V + 1; i++){
      spTable[i][j] = spTable[spTable[i][j - 1]][j - 1];

      spTableMax[i][j] = -1;
      spTable2ndMax[i][j] = -1;

      vector<int> curVals(4);
      curVals[0] = spTableMax[i][j - 1];
      curVals[1] = spTable2ndMax[i][j - 1];
      curVals[2] = spTableMax[spTable[i][j - 1]][j - 1];
      curVals[3] = spTable2ndMax[spTable[i][j - 1]][j - 1];
      sort(curVals.rbegin(), curVals.rend());

      spTableMax[i][j] = curVals[0];
      for(int k = 1; k < 4; k++){
        if(curVals[k] == curVals[0]) continue;
        spTable2ndMax[i][j] = curVals[k];
        break;
      }

    }
  }

}

int LCA(int v1, int v2){

  int curMaxEdge = -1;

  while(levelOf[v1] < levelOf[v2]){
    curMaxEdge = max(curMaxEdge, spTableMax[v2][(int)(floor(log2(levelOf[v2] - levelOf[v1])))]);
    v2 = spTable[v2][(int)(floor(log2(levelOf[v2] - levelOf[v1])))];
  }
  while(levelOf[v1] > levelOf[v2]){
    curMaxEdge = max(curMaxEdge, spTableMax[v1][(int)(floor(log2(levelOf[v1] - levelOf[v2])))]);
    v1 = spTable[v1][(int)(floor(log2(levelOf[v1] - levelOf[v2])))];
  }

  while(v1 != v2){

    int st = 1;
    int ed = 20;
    while(st <= ed){
      int mid = (st + ed) / 2;

      if(spTable[v1][mid] == spTable[v2][mid])
        ed = mid - 1;
      else
        st = mid + 1;
    }

    curMaxEdge = max(curMaxEdge, spTableMax[v1][ed]);
    curMaxEdge = max(curMaxEdge, spTableMax[v2][ed]);
    v1 = spTable[v1][ed];
    v2 = spTable[v2][ed];
  }

  return curMaxEdge;
}

int LCA2nd(int v1, int v2, int maxEdge){

  int cur2ndMaxEdge = -1;

  while(levelOf[v1] < levelOf[v2]){
    if(spTableMax[v2][(int)(floor(log2(levelOf[v2] - levelOf[v1])))] < maxEdge)
      cur2ndMaxEdge = max(cur2ndMaxEdge, spTableMax[v2][(int)(floor(log2(levelOf[v2] - levelOf[v1])))]);
    if(spTable2ndMax[v2][(int)(floor(log2(levelOf[v2] - levelOf[v1])))] < maxEdge)
      cur2ndMaxEdge = max(cur2ndMaxEdge, spTable2ndMax[v2][(int)(floor(log2(levelOf[v2] - levelOf[v1])))]);

    v2 = spTable[v2][(int)(floor(log2(levelOf[v2] - levelOf[v1])))];
  }
  while(levelOf[v1] > levelOf[v2]){
    if(spTableMax[v1][(int)(floor(log2(levelOf[v1] - levelOf[v2])))] < maxEdge)
      cur2ndMaxEdge = max(cur2ndMaxEdge, spTableMax[v1][(int)(floor(log2(levelOf[v1] - levelOf[v2])))]);
    if(spTable2ndMax[v1][(int)(floor(log2(levelOf[v1] - levelOf[v2])))] < maxEdge)
      cur2ndMaxEdge = max(cur2ndMaxEdge, spTable2ndMax[v1][(int)(floor(log2(levelOf[v1] - levelOf[v2])))]);

    v1 = spTable[v1][(int)(floor(log2(levelOf[v1] - levelOf[v2])))];
  }

  while(v1 != v2){

    int st = 1;
    int ed = 20;
    while(st <= ed){
      int mid = (st + ed) / 2;

      if(spTable[v1][mid] == spTable[v2][mid])
        ed = mid - 1;
      else
        st = mid + 1;
    }

    if(spTableMax[v1][ed] < maxEdge)
      cur2ndMaxEdge = max(cur2ndMaxEdge, spTableMax[v1][ed]);
    if(spTable2ndMax[v1][ed] < maxEdge)
      cur2ndMaxEdge = max(cur2ndMaxEdge, spTable2ndMax[v1][ed]);
    
    if(spTableMax[v2][ed] < maxEdge)
      cur2ndMaxEdge = max(cur2ndMaxEdge, spTableMax[v2][ed]);
    if(spTable2ndMax[v2][ed] < maxEdge)
      cur2ndMaxEdge = max(cur2ndMaxEdge, spTable2ndMax[v2][ed]);

    v1 = spTable[v1][ed];
    v2 = spTable[v2][ed];
  }

  return cur2ndMaxEdge;
}

//MST
int MSTWeight;
vector<bool> isMSTEdge;
vector<vector<pair<int, int>>> MST;
void getMST(){
  sort(edges.begin(), edges.end());

  for(int i = 0; i < E; i++){
    if(getGroup(edges[i][1]) == getGroup(edges[i][2])) continue;
    
    MSTWeight += edges[i][0];
    isMSTEdge[edges[i][3]] = true;
    unionGroup(edges[i][1], edges[i][2]);
    
    MST[edges[i][1]].push_back({edges[i][2], edges[i][0]});
    MST[edges[i][2]].push_back({edges[i][1], edges[i][0]});
  }
}

void dfs(int cur, int prv, int level){
  levelOf[cur] = level;

  for(auto e: MST[cur]){
    if(e.first == prv) continue;
    dfs(e.first, cur, level + 1);

    spTable[e.first][0] = cur;
    spTableMax[e.first][0] = e.second;
  }
}

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  cin >> V >> E;
  edges.assign(E, vector<int>(4, 0));
  for(int i = 0; i < E; i++){
    cin >> edges[i][1] >> edges[i][2] >> edges[i][0];
    edges[i][3] = i;
  }

  groupOf.assign(V + 1, 0);
  for(int i = 0; i < V + 1; i++)
    groupOf[i] = i;
  levelOf.assign(V + 1, 0);
  spTable.assign(V + 1, vector<int>(20, 0));
  spTableMax.assign(V + 1, vector<int>(20, -1));
  spTable2ndMax.assign(V + 1, vector<int>(20, -1));
  MSTWeight = 0;
  isMSTEdge.assign(E, false);
  MST.assign(V + 1, vector<pair<int, int>>());

  getMST();

  int MSTEdgeCnt = 0;
  for(int i = 0; i < E; i++)
    if(isMSTEdge[i]) MSTEdgeCnt++;
  if(MSTEdgeCnt != V - 1){
    cout << -1;
    return 0;
  }

  dfs(1, 1, 1);
  initSpTable();

  vector<int> MSTOf(E);
  for(int i = 0; i < E; i++){
    if(isMSTEdge[edges[i][3]]){
      MSTOf[edges[i][3]] = MSTWeight;
      continue;
    }

    int lca = LCA(edges[i][1], edges[i][2]);
    if(lca == edges[i][0]){
      int lca2nd = LCA2nd(edges[i][1], edges[i][2], lca);
      if(lca2nd == -1)
        MSTOf[edges[i][3]] = MSTWeight;
      else
        MSTOf[edges[i][3]] = MSTWeight - lca2nd + edges[i][0];
    }
    else
      MSTOf[edges[i][3]] = MSTWeight - lca + edges[i][0];
  }

  sort(MSTOf.begin(), MSTOf.end());
  for(int i = 0; i < E; i++){
    if(MSTOf[i] == MSTWeight) continue;
    cout << MSTOf[i];
    return 0;
  }
  cout << -1;

  return 0;
}