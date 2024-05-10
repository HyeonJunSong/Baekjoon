#include <iostream>
#include <vector>

using namespace std;

#define ll unsigned long long
#define DIV 4294967296

vector<vector<int>> graph;

class hldNode{
public:
  int idx;
  int root;
  int leaf;
  int parent;
  int childEdIdx;
  int heavy;
  int level;
};

vector<hldNode> hldList;
vector<int> hldNodeQueue;

int getChildCntAndInitHeavyNode(int parent, int idx){
  int cnt = 0;

  int heavyIdx = -1;
  int heavyCnt = 0;
  for(auto e: graph[idx]){
    if(e == parent) continue;
    int curCnt = getChildCntAndInitHeavyNode(idx, e);
    cnt += curCnt;

    if(heavyCnt < curCnt){
      heavyCnt = curCnt;
      heavyIdx = e;
    }
  }
  hldList[idx].heavy = heavyIdx;
  return cnt + 1;
}

int hldInit(int parent, int cur, int root, int level){

  if(hldList[cur].heavy == -1){
    hldList[cur].idx = hldNodeQueue.size();
    hldList[cur].root = root;
    hldList[cur].leaf = cur;
    hldList[cur].parent = parent;
    hldList[cur].childEdIdx = hldList[cur].idx;
    hldList[cur].level = level;
    hldNodeQueue.push_back(cur);
    return cur;
  }

  hldList[cur].idx = hldNodeQueue.size();
  hldList[cur].root = root;
  hldNodeQueue.push_back(cur);
  hldList[cur].leaf = hldInit(cur, hldList[cur].heavy, root, level + 1);
  hldList[cur].parent = parent;

  for(auto e: graph[cur]){
    if(e == parent || e == hldList[cur].heavy) continue;
    hldInit(cur, e, e, level + 1);
  }
  hldList[cur].childEdIdx = hldNodeQueue.size() - 1;
  hldList[cur].level = level;

  return hldList[cur].leaf;
}

int lca(int a, int b){
  while(a != b){
    if(hldList[a].root == hldList[b].root){
      if(hldList[a].level < hldList[b].level)
        b = a;
      else
        a = b;
    }else{
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
  ll val;
  pair<ll, ll> lazy;
};
vector<segNode> segTree;
int leafNum = 1;

void segInit(int N){
  while(leafNum < N) leafNum *= 2;
  segTree = vector<segNode>(leafNum * 2);
  
  for(int i = 0; i < N; i++){
    segTree[leafNum + i].st = i;
    segTree[leafNum + i].ed = i + 1;
    segTree[leafNum + i].val = 0;
    segTree[leafNum + i].lazy = {1, 0};
  }
  for(int i = N; i < leafNum; i++){
    segTree[leafNum + i].st = i;
    segTree[leafNum + i].ed = i + 1;
    segTree[leafNum + i].val = 0;
    segTree[leafNum + i].lazy = {0, 0};
  }
  
  for(int i = leafNum - 1; i > 0; i--){
    segTree[i].st = segTree[2 * i].st;
    segTree[i].ed = segTree[2 * i + 1].ed;
    segTree[i].val = 0;
    segTree[i].lazy = {1, 0};
  }
}

void segUpdate(int idx, int st, int ed, pair<ll, ll> op){
  if(segTree[idx].st == st && segTree[idx].ed == ed){
    segTree[idx].lazy.first *= op.first;
    segTree[idx].lazy.second *= op.first;
    segTree[idx].lazy.second += op.second;
    segTree[idx].val = segTree[idx].val * op.first + (op.second) * (ed - st);

    segTree[idx].lazy.first %= DIV;
    segTree[idx].lazy.second %= DIV;
    segTree[idx].val %= DIV;
    return;
  }

  if(segTree[idx].lazy.first != 1 || segTree[idx].lazy.second != 0){
    segUpdate(2 * idx, segTree[2 * idx].st, segTree[2 * idx].ed, segTree[idx].lazy);
    segUpdate(2 * idx + 1, segTree[2 * idx + 1].st, segTree[2 * idx + 1].ed, segTree[idx].lazy);
    segTree[idx].lazy = {1, 0};
  }

  if(ed <= segTree[2 * idx].ed)
    segUpdate(2 * idx, st, ed, op);
  else if(segTree[2 * idx + 1].st <= st)
    segUpdate(2 * idx + 1, st, ed, op);
  else{
    segUpdate(2 * idx, st, segTree[2 * idx].ed, op);
    segUpdate(2 * idx + 1, segTree[2 * idx + 1].st, ed, op);
  }
  segTree[idx].val = segTree[2 * idx].val + segTree[2 * idx + 1].val;
  segTree[idx].val %= DIV;
  return;
}

ll segGetVal(int idx, int st, int ed){
  if(segTree[idx].st == st && segTree[idx].ed == ed){
    return segTree[idx].val;
  }

  if(segTree[idx].lazy.first != 1 || segTree[idx].lazy.second != 0){
    segUpdate(2 * idx, segTree[2 * idx].st, segTree[2 * idx].ed, segTree[idx].lazy);
    segUpdate(2 * idx + 1, segTree[2 * idx + 1].st, segTree[2 * idx + 1].ed, segTree[idx].lazy);
    segTree[idx].lazy = {1, 0};
    segTree[idx].val = segTree[2 * idx].val + segTree[2 * idx + 1].val;
    segTree[idx].val %= DIV;
  }

  if(ed <= segTree[2 * idx].ed)
    return segGetVal(2 * idx, st, ed);
  if(segTree[2 * idx + 1].st <= st)
    return segGetVal(2 * idx + 1, st, ed);
  return (segGetVal(2 * idx, st, segTree[2 * idx].ed) + segGetVal(2 * idx + 1, segTree[2 * idx + 1].st, ed)) % DIV;
}

int main(){

  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  int N, Q;
  cin >> N >> Q;

  graph = vector<vector<int>>(N);

  int st, ed;
  for(int i = 0; i < N - 1; i++){
    cin >> st >> ed;
    st--; ed--;

    graph[st].push_back(ed);
    graph[ed].push_back(st);
  }

  hldList = vector<hldNode>(N);
  getChildCntAndInitHeavyNode(0, 0);
  hldInit(0, 0, 0, 0);
  segInit(N);

  int query, X, Y, curLCA;
  ll V;
  for(int q = 0; q < Q; q++){
    cin >> query;

    switch(query){
      case 1:
        cin >> X >> V;
        X--;
        segUpdate(1, hldList[X].idx, hldList[X].childEdIdx + 1, {1, V});
      break;
      case 2:
        cin >> X >> Y >> V;
        X--;Y--;
        curLCA = lca(X, Y);
        while(hldList[X].root != hldList[curLCA].root){
          segUpdate(1, hldList[hldList[X].root].idx, hldList[X].idx + 1, {1, V});
          X = hldList[hldList[X].root].parent;
        }
        segUpdate(1, hldList[curLCA].idx, hldList[X].idx + 1, {1, V});
        
        while(hldList[Y].root != hldList[curLCA].root){
          segUpdate(1, hldList[hldList[Y].root].idx, hldList[Y].idx + 1, {1, V});
          Y = hldList[hldList[Y].root].parent;
        }

        if(curLCA != Y)
          segUpdate(1, hldList[curLCA].idx + 1, hldList[Y].idx + 1, {1, V});
      break;
      case 3:
        cin >> X >> V;
        X--;
        segUpdate(1, hldList[X].idx, hldList[X].childEdIdx + 1, {V, 0});
      break;
      case 4:
        cin >> X >> Y >> V;
        X--;Y--;
        curLCA = lca(X, Y);
        while(hldList[X].root != hldList[curLCA].root){
          segUpdate(1, hldList[hldList[X].root].idx, hldList[X].idx + 1, {V, 0});
          X = hldList[hldList[X].root].parent;
        }
        segUpdate(1, hldList[curLCA].idx, hldList[X].idx + 1, {V, 0});
        
        while(hldList[Y].root != hldList[curLCA].root){
          segUpdate(1, hldList[hldList[Y].root].idx, hldList[Y].idx + 1, {V, 0});
          Y = hldList[hldList[Y].root].parent;
        }
        if(curLCA != Y)
          segUpdate(1, hldList[curLCA].idx + 1, hldList[Y].idx + 1, {V, 0});
      break;
      case 5:
        cin >> X;
        X--;
        cout << segGetVal(1, hldList[X].idx, hldList[X].childEdIdx + 1) << "\n";
      break;
      case 6:
        cin >> X >> Y;
        X--;Y--;
        curLCA = lca(X, Y);
        ll ans = 0;
        while(hldList[X].root != hldList[curLCA].root){
          ans += segGetVal(1, hldList[hldList[X].root].idx, hldList[X].idx + 1);
          ans %= DIV;
          X = hldList[hldList[X].root].parent;
        }
        ans += segGetVal(1, hldList[curLCA].idx, hldList[X].idx + 1);
        ans %= DIV;
        
        while(hldList[Y].root != hldList[curLCA].root){
          ans += segGetVal(1, hldList[hldList[Y].root].idx, hldList[Y].idx + 1);
          ans %= DIV;
          Y = hldList[hldList[Y].root].parent;
        }
        if(curLCA != Y){
          ans += segGetVal(1, hldList[curLCA].idx + 1, hldList[Y].idx + 1);
          ans %= DIV;
        }
        cout << ans << "\n";
      break;
    }
  }

  return 0;
}