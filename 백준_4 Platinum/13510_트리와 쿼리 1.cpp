#include <iostream>
#include <vector>

using namespace std;

int N;
vector<vector<pair<int, pair<int, int>>>> graph;
vector<int> nodeAtEdge;

class hldNode{
public:
  int idx;
  int root;
  int parent;
  int heavy;
  int level;
  int toParent;

  hldNode(){
    idx = 0;
    root = 0;
    parent = 0;
    heavy = 0;
    level = 0;
    toParent = 0;
  }
};
vector<hldNode> hldList;
vector<int> hldStack;

int hldHeavyInit(int parent, int cur){

  int heavyWeight = 0;
  int heavyNode = -1;
  int weightSum = 0;
  for(auto e: graph[cur]){
    if(e.first == parent) continue;
    int curWeight = hldHeavyInit(cur, e.first);
    if(heavyWeight < curWeight){
      heavyWeight = curWeight;
      heavyNode = e.first;
    }
    weightSum += curWeight;
  }
  hldList[cur].heavy = heavyNode;

  return weightSum + 1;
}

void hldInit(int node, int root, int parent, int level){

  if(hldList[node].heavy == -1){
    hldList[node].idx = hldStack.size();
    hldStack.push_back(node);
    hldList[node].root = root;
    hldList[node].parent = parent;
    hldList[node].level = level;
    return;
  }

  hldList[node].idx = hldStack.size();
  hldStack.push_back(node);
  hldList[node].root = root;
  hldList[node].parent = parent;
  hldList[node].level = level;
  hldInit(hldList[node].heavy, root, node, level + 1);

  for(auto e: graph[node]){
    if(e.first == parent) continue;
    if(e.first == hldList[node].heavy){
      hldList[e.first].toParent = e.second.first;
      nodeAtEdge[e.second.second] = e.first;
      continue;
    }
    
    hldList[e.first].toParent = e.second.first;
    nodeAtEdge[e.second.second] = e.first;
    hldInit(e.first, e.first, node, level + 1);
  }
  return;
}

int lca(int a, int b){
  while(a != b){
    if(hldList[a].root == hldList[b].root){
      if(hldList[a].level < hldList[b].level)
        b = a;
      else
        a = b;
    } else{
      if(hldList[hldList[a].root].level < hldList[hldList[b].root].level)
        b = hldList[hldList[b].root].parent;
      else if(hldList[hldList[a].root].level > hldList[hldList[b].root].level)
        a = hldList[hldList[a].root].parent;
      else{
        a = hldList[a].parent;
        b = hldList[b].parent;
      }
    }
  }

  return a;
}

class segNode{
public:
  int st;
  int ed;
  int val;
};

vector<segNode> segTree;
int leafNum = 1;

void segInit(int N){
  while(leafNum < N) leafNum *= 2;
  segTree = vector<segNode>(leafNum * 2);

  for(int i = 0; i < N; i++){
    segTree[leafNum + i].st = i;
    segTree[leafNum + i].ed = i + 1;
    segTree[leafNum + i].val = hldList[hldStack[i]].toParent;
  }

  for(int i = N; i < leafNum; i++){
    segTree[leafNum + i].st = i;
    segTree[leafNum + i].ed = i + 1;
    segTree[leafNum + i].val = 0;
  }

  for(int i = leafNum - 1; i > 0; i--){
    segTree[i].st = segTree[2 * i].st;
    segTree[i].ed = segTree[2 * i + 1].ed;
    segTree[i].val = max(segTree[2 * i].val, segTree[2 * i + 1].val);
  }
  return;
}

void segUpdate(int x, int w){
  int curIdx = leafNum + x;
  segTree[curIdx].val = w;
  curIdx /= 2;

  while(curIdx >= 1){
    segTree[curIdx].val = max(segTree[2 * curIdx].val, segTree[2 * curIdx + 1].val);
    curIdx /= 2;
  }
  return;
}

int segGetVal(int idx, int st, int ed){
  if(segTree[idx].st == st && segTree[idx].ed == ed)
    return segTree[idx].val;
  
  if(ed <= segTree[2 * idx].ed)
    return segGetVal(2 * idx, st, ed);
  if(segTree[2 * idx + 1].st <= st)
    return segGetVal(2 * idx + 1, st, ed);
  return max(segGetVal(2 * idx, st, segTree[2 * idx].ed), segGetVal(2 * idx + 1, segTree[2 * idx + 1].st, ed));
}

int main(){

  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  cin >> N;
  graph = vector<vector<pair<int, pair<int, int>>>>(N);
  int u, v, w;
  for(int i = 0; i < N - 1; i++){
    cin >> u >> v >> w;
    u--;v--;
    graph[u].push_back({v, {w, i}});
    graph[v].push_back({u, {w, i}});
  }
  nodeAtEdge = vector<int>(N - 1);

  hldList = vector<hldNode>(N);
  hldHeavyInit(0, 0);
  hldInit(0, 0, 0, 0);
  segInit(N);

  int Q;
  cin >> Q;

  int query, i, c;

  for(int q = 0; q < Q; q++){
    cin >> query;
    switch(query){
      case 1:
        cin >> i >> c;
        i--;
        segUpdate(hldList[nodeAtEdge[i]].idx, c);
      break;
      case 2:
        cin >> u >> v;
        u--;
        v--;

        int curLCA = lca(u, v);
        int ans = 0;

        while(hldList[curLCA].root != hldList[u].root){
          ans = max(ans, segGetVal(1, hldList[hldList[u].root].idx, hldList[u].idx + 1));
          u = hldList[hldList[u].root].parent;
        }
        if(curLCA != u)
          ans = max(ans, segGetVal(1, hldList[curLCA].idx + 1, hldList[u].idx + 1));

        while(hldList[curLCA].root != hldList[v].root){
          ans = max(ans, segGetVal(1, hldList[hldList[v].root].idx, hldList[v].idx + 1));
          v = hldList[hldList[v].root].parent;
        }
        if(curLCA != v)
          ans = max(ans, segGetVal(1, hldList[curLCA].idx + 1, hldList[v].idx + 1));

        cout << ans << "\n";
      break;
    }

  }

  return 0;
}