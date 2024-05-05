#include <iostream>
#include <vector>

using namespace std;

int N;
vector<vector<int>> graph;

//HLD 관련
class HldNode{
public:
  int heavyNode;
  int root;
  int end;
  int parent;
  int idx;
};

vector<HldNode> hldNodes;

int getChildrenCnt(int prevNode, int curNode){
  int sum = 0;

  int heavyNodeCnt = 0;
  int heavyNode = -1;
  for(auto e: graph[curNode]){
    if(e == prevNode) continue;
    int curCnt = getChildrenCnt(curNode, e);
    if(heavyNodeCnt < curCnt){
      heavyNodeCnt = curCnt;
      heavyNode = e;
    }
    sum += curCnt;
  }
  hldNodes[curNode].heavyNode = heavyNode;
  return sum + 1;
}

vector<int> hldArr;

int HLD(int rootOfCurRoute, int prevNode, int curNode){

  if(hldNodes[curNode].heavyNode == -1){
    hldNodes[curNode].idx = hldArr.size();
    hldArr.push_back(curNode);
    hldNodes[curNode].root = rootOfCurRoute;
    hldNodes[curNode].end = curNode;
    hldNodes[curNode].parent = prevNode;
    return curNode;
  }

  hldNodes[curNode].idx = hldArr.size();
  hldArr.push_back(curNode);
  hldNodes[curNode].root = rootOfCurRoute;
  hldNodes[curNode].end = HLD(rootOfCurRoute, curNode, hldNodes[curNode].heavyNode);
  hldNodes[curNode].parent = prevNode;

  for(auto e: graph[curNode]){
    if(e == prevNode || e == hldNodes[curNode].heavyNode) continue;
    HLD(e, curNode, e);
  }

  return hldNodes[curNode].end;
}


// 세그 트리 관련
class segNode{
public:
  int st;
  int ed;
  int val;
};

int leafNum = 1;
vector<segNode> segTree;

void segInit(){
  while(leafNum < hldArr.size()) leafNum *= 2;
  segTree = vector<segNode>(leafNum * 2);
  
  for(int i = 0; i < leafNum; i++){
    segTree[leafNum + i].st = i;
    segTree[leafNum + i].ed = i + 1;
    segTree[leafNum + i].val = -1;
  }
  for(int i = leafNum - 1; i > 0; i--){
    segTree[i].st = segTree[2 * i].st;
    segTree[i].ed = segTree[2 * i + 1].ed;
    segTree[i].val = -1;
  }
}

void segUpdate(int x){
  int idx = leafNum + hldNodes[x].idx;
  if(segTree[idx].val == -1)
    segTree[idx].val = x;
  else
    segTree[idx].val = -1;
  idx /= 2;

  while(idx >= 1){
    if(segTree[2 * idx].val != -1)
      segTree[idx].val = segTree[2 * idx].val;
    else
      segTree[idx].val = segTree[2 * idx + 1].val;
    idx /= 2;
  }
}

int segGetVal(int idx, int st, int ed){
  if(segTree[idx].st == st && segTree[idx].ed == ed){
    return segTree[idx].val;
  }

  if(ed <= segTree[2 * idx].ed)
    return segGetVal(2 * idx, st, ed);
  if(segTree[2 * idx + 1].st <= st)
    return segGetVal(2 * idx + 1, st, ed);
  
  int left = segGetVal(2 * idx, st, segTree[2 * idx].ed);
  if(left != -1)
    return left;
  else
    return segGetVal(2 * idx + 1, segTree[2 * idx + 1].st, ed);
}

int main(){

  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  cin >> N;
  graph = vector<vector<int>>(N);
  for(int i = 0; i < N - 1; i++){
    int u, v;
    cin >> u >> v;
    u--;v--;

    graph[u].push_back(v);
    graph[v].push_back(u);
  }

  hldNodes = vector<HldNode>(N);
  getChildrenCnt(0, 0);
  HLD(0, -1, 0);
  
  segInit();

  int M;
  cin >> M;
  int q, i, v;
  for(int m = 0; m < M; m++){
    cin >> q;

    switch(q){
      case 1:
        cin >> i;
        i--;
        segUpdate(i);
      break;
      case 2:
        cin >> v;
        v--;
        int ans = -1;

        while(v != -1){
          int curVal = segGetVal(1, hldNodes[hldNodes[v].root].idx, hldNodes[v].idx + 1);
          if(curVal != -1)
            ans = curVal + 1;
          v = hldNodes[hldNodes[v].root].parent;
        }

        cout << ans << "\n";
      break;
    }
  }

  return 0;
}