#include <iostream>
#include <vector>

using namespace std;

vector<vector<int>> graph;

class hldNode{
public:
  int idx;
  int level;
  int heavy;
  int root;
  int parent;
};
vector<hldNode> hldList;
vector<int> hldNodeOf;

int hldHeavyInit(int par, int cur){

  int heavyIdx = -1;
  int heavyWei = 0;
  int totWei = 0;

  for(auto e: graph[cur]){
    if(e == par) continue;
    int curWei = hldHeavyInit(cur, e);
    if(heavyWei < curWei){
      heavyWei = curWei;
      heavyIdx = e;
    }
    totWei += curWei;
  }
  hldList[cur].heavy = heavyIdx;

  return totWei + 1;
}

void hldInit(int par, int cur, int root, int level){

  hldList[cur].idx = hldNodeOf.size();
  hldNodeOf.push_back(cur);
  hldList[cur].parent = par;
  hldList[cur].root = root;
  hldList[cur].level = level;

  if(hldList[cur].heavy == -1) return;

  hldInit(cur, hldList[cur].heavy, root, level + 1);
  for(auto e: graph[cur]){
    if(e == par || e == hldList[cur].heavy) continue;
    hldInit(cur, e, e, level + 1);
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
    } else {
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

void segInit(int N, vector<int>& e){
  while(leafNum < N) leafNum *= 2;
  segTree = vector<segNode>(leafNum * 2);

  for(int i = 0; i < N; i++){
    segTree[leafNum + i].st = i;
    segTree[leafNum + i].ed = i + 1;
    segTree[leafNum + i].val = e[hldNodeOf[i]];
  }

  for(int i = N; i < leafNum; i++){
    segTree[leafNum + i].st = i;
    segTree[leafNum + i].ed = i + 1;
    segTree[leafNum + i].val = 0;
  }

  for(int i = leafNum - 1; i > 0; i--){
    segTree[i].st = segTree[2 * i].st;
    segTree[i].ed = segTree[2 * i + 1].ed;
    segTree[i].val = segTree[2 * i].val ^ segTree[2 * i + 1].val;
  }

  return;
}

void segUpdate(int x, int val){
  int idx = leafNum + x;

  segTree[idx].val = val;
  idx /= 2;

  while(idx > 0){
    segTree[idx].val = segTree[2 * idx].val ^ segTree[2 * idx + 1].val;
    idx /= 2;
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
  return segGetVal(2 * idx, st, segTree[2 * idx].ed) ^ segGetVal(2 * idx + 1, segTree[2 * idx + 1].st, ed);
}

int main(){

  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  int N, Q;
  cin >> N >> Q;
  vector<int> e(N);
  for(int i = 0; i < N; i++)
    cin >> e[i];
  
  graph = vector<vector<int>>(N);
  for(int i = 0; i < N - 1; i++){
    int a, b;
    cin >> a >> b;
    a--; b--;
    graph[a].push_back(b);
    graph[b].push_back(a);
  }

  hldList = vector<hldNode>(N);
  hldHeavyInit(0, 0);
  hldInit(0, 0, 0, 0);
  segInit(N, e);

  int query, i, v, j;
  for(int q = 0; q < Q; q++){
    cin >> query;
    switch(query){
      case 1:
        cin >> i >> v;
        i--;
        segUpdate(hldList[i].idx, v);
      break;
      case 2:
        cin >> i >> j;
        i--;j--;

        int curLca = lca(i, j);
        int ans = segTree[leafNum + hldList[curLca].idx].val;

        while(hldList[i].root != hldList[curLca].root){
          ans ^= segGetVal(1, hldList[hldList[i].root].idx, hldList[i].idx + 1);
          i = hldList[hldList[i].root].parent;
        }
        ans ^= segGetVal(1, hldList[curLca].idx, hldList[i].idx + 1);

        while(hldList[j].root != hldList[curLca].root){
          ans ^= segGetVal(1, hldList[hldList[j].root].idx, hldList[j].idx + 1);
          j = hldList[hldList[j].root].parent;
        }
        ans ^= segGetVal(1, hldList[curLca].idx, hldList[j].idx + 1);

        cout << ans << "\n";

      break;
    }
  }



  return 0;
}