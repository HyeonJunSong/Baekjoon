#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

class Node{
public:
  Node* l;
  Node* r;

  //[st, ed)
  int st;
  int ed;
  int val;

  Node(Node* l, Node* r, int st, int ed, int val) : l(l), r(r), st(st), ed(ed), val(val) {};
  Node(Node* node){
    this->l = node->l;
    this->r = node->r;
    this->st = node->st;
    this->ed = node->ed;
    this->val = node->val;
  }
};

vector<Node*> segTree;
void segInit(Node*& root, int st, int ed){
  root = new Node(nullptr, nullptr, st, ed, 0);
  if(ed - st == 1) return;
  segInit(root->l, st, (st + ed) >> 1);
  segInit(root->r, (st + ed) >> 1, ed);
}
void segUpdate(Node* prevTree, Node*& curNode, int target){
  curNode = new Node(prevTree);

  if(curNode->ed - curNode->st == 1){
    curNode->val++;
    return;
  }

  if(target < curNode->l->ed)
    segUpdate(prevTree->l, curNode->l, target);
  else
    segUpdate(prevTree->r, curNode->r, target);
  curNode->val = curNode->l->val + curNode->r->val;
}
int segGetVal(Node* node, int st, int ed){
  if(node->st == st && node->ed == ed)
    return node->val;
  
  if(ed <= node->l->ed)
    return segGetVal(node->l, st, ed);
  if(st >= node->r->st)
    return segGetVal(node->r, st, ed);
  return segGetVal(node->l, st, node->l->ed) + segGetVal(node->r, node->r->st, ed);
}

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  //입력
  int N;
  cin >> N;

  vector<pair<int, int>> arr(N);
  for(int i = 0; i < N; i++){
    cin >> arr[i].first;
    arr[i].second = i;
  }
  
  //정렬후, 순서대로 퍼시스턴트 세그트리에 넣기
  //segTree[i] : i번째로 넣은 숫자까지의 세그트리
  //세그 트리에는 index를 저장
  sort(arr.begin(), arr.end());

  segTree.assign(N + 1, nullptr);
  segInit(segTree[0], 0, N);
  map<int, int> numMap;
  for(int i = 0; i < N; i++){
    segUpdate(segTree[i], segTree[i + 1], arr[i].second);
    numMap[-arr[i].first] = i + 1;
  }

  //쿼리 수행
  int Q;
  cin >> Q;
  for(int q = 0; q < Q; q++){
    int i, j, k;
    cin >> i >> j >> k;

    if(numMap.lower_bound(-k) == numMap.end())
      cout << (j - i + 1) << "\n";
    else
      cout << (j - i + 1) - segGetVal(segTree[numMap.lower_bound(-k)->second], i - 1, j) << "\n";
  }

  return 0;
}