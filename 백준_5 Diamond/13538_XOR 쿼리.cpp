#include <iostream>
#include <vector>

#define RANGE_ST 0
#define RANGE_ED 524287

using namespace std;

class Node{
public:

  //범위 : [st, ed]
  int st;
  int ed;

  Node* L;
  Node* R;

  int cnt;

  Node(int st, int ed){
    this->st = st;
    this->ed = ed;
    L = nullptr;
    R = nullptr;
    cnt = 0;
  }

  Node(Node* cpy){
    st  = cpy->st;
    ed  = cpy->ed;
    L   = cpy->L;
    R   = cpy->R;
    cnt = cpy->cnt;
  }
};

vector<Node*> rootOf;
void segInit(Node*& node, int st, int ed){
  node = new Node(st, ed);

  if(st == ed) return;

  segInit(node->L, st, st + (ed - st + 1)/2 - 1);
  segInit(node->R, st + (ed - st + 1)/2, ed);
}

void segUpdate(Node* prvTree, Node*& curTree, int x){
  curTree = new Node(prvTree);
  if(curTree->st == curTree->ed){
    curTree->cnt++;
    return;
  }

  //※자식이 하나인 노드는 없음
  if(x <= curTree->L->ed){
    segUpdate(prvTree->L, curTree->L, x);
  } else{
    segUpdate(prvTree->R, curTree->R, x);
  }
  curTree->cnt = curTree->L->cnt + curTree->R->cnt;
  return;
}

int segGetSum(Node* stTree, Node* edTree, int st, int ed){
  if(stTree->st == st && stTree->ed == ed)
    return edTree->cnt - stTree->cnt;
  if(ed <= stTree->L->ed)
    return segGetSum(stTree->L, edTree->L, st, ed);
  if(stTree->R->st <= st)
    return segGetSum(stTree->R, edTree->R, st, ed);
  
  return segGetSum(stTree->L, edTree->L, st, stTree->L->ed) + segGetSum(stTree->R, edTree->R,  stTree->R->st, ed);
}

int segGetKth(Node* stTree, Node* edTree, int k){
  if(stTree->st == stTree->ed)
    return stTree->st;
  
  int leftSide = segGetSum(stTree->L, edTree->L, stTree->L->st, stTree->L->ed);
  if(k <= leftSide)
    return segGetKth(stTree->L, edTree->L, k);
  else
    return segGetKth(stTree->R, edTree->R, k - leftSide);
}

int segGetMaxXOR(Node* stTree, Node* edTree, int x, int curBit){

  if(stTree->st == stTree->ed)
    return stTree->st;

  //오른쪽의 스타트가 좌우 구분 비트
  if((x & (1 << curBit)) > 0){
    if(edTree->L->cnt - stTree->L->cnt > 0)
      return segGetMaxXOR(stTree->L, edTree->L, x, curBit - 1);
    else
      return segGetMaxXOR(stTree->R, edTree->R, x, curBit - 1);
  } else{
    if(edTree->R->cnt - stTree->R->cnt > 0)
      return segGetMaxXOR(stTree->R, edTree->R, x, curBit - 1);
    else
      return segGetMaxXOR(stTree->L, edTree->L, x, curBit - 1);
  }
}

int main(){

  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  rootOf.push_back(nullptr);
  segInit(rootOf[0], RANGE_ST, RANGE_ED);
  int rootOfSize = 1;

  int M;
  cin >> M;

  for(int i = 0; i < M; i++){
    int query, x, L, R, k;
    cin >> query;
    switch(query){
      case 1:
        cin >> x;
        if(rootOfSize == rootOf.size())
          rootOf.push_back(nullptr);
        rootOfSize++;
        segUpdate(rootOf[rootOfSize - 2], rootOf[rootOfSize - 1], x);
      break;
      case 2:
        cin >> L >> R >> x;
        cout << segGetMaxXOR(rootOf[L - 1], rootOf[R], x, 18) << "\n";
      break;
      case 3:
        cin >> k;
        rootOfSize -= k;
      break;
      case 4:
        cin >> L >> R >> x;
        cout << segGetSum(rootOf[L - 1], rootOf[R], 0, x) << "\n";
      break;
      case 5:
        cin >> L >> R >> k;
        cout << segGetKth(rootOf[L - 1], rootOf[R], k) << "\n";
      break;
    }
  }

  return 0;
}