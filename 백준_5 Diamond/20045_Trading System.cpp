#include <iostream>
#include <vector>
#include <map>
#include <queue>

using namespace std;

#define ll long long

int n, k;

class segNode{
public:
  int st;
  int ed;
  int val;

  segNode* L;
  segNode* R;
};

vector<segNode*> segRoots;
void segInit(segNode* root, int st, int ed){

  root->val = 0;
  root->st = st;
  root->ed = ed;

  if(ed - st == 1){
    root->L = nullptr;
    root->R = nullptr;
    return;
  }

  root->L = new segNode();
  root->R = new segNode();
  segInit(root->L, st, (st + ed) >> 1);
  segInit(root->R, (st + ed) >> 1, ed);

}

void segUpdate(segNode* curTree, segNode* prevTree, int idx){

  curTree->st = prevTree->st;
  curTree->ed = prevTree->ed;
  curTree->val = prevTree->val + 1;
  curTree->L = prevTree->L;
  curTree->R = prevTree->R;

  if(curTree->ed - curTree->st == 1) return;

  if(curTree->L->ed > idx){
    curTree->L = new segNode();
    segUpdate(curTree->L, prevTree->L, idx);
  } else {
    curTree->R = new segNode();
    segUpdate(curTree->R, prevTree->R, idx);
  }
}

int segGetVal(segNode* curNode, int k){
  if(curNode->ed - curNode->st == 1) return curNode->st;

  if(curNode->L->val >= k) return segGetVal(curNode->L, k);
  else return segGetVal(curNode->R, k - curNode->L->val);
}

class PQNode{
public:
  ll val;
  int idx;
  int k;

  bool operator<(PQNode b) const {
    return val < b.val;
  }
};

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  cin >> n >> k;

  vector<ll> nums;
  nums.assign(n + 1, 0);
  for(int i = 1; i <= n; i++)
    cin >> nums[i];
  for(int i = 1; i <= n; i++)
    nums[i] += nums[i - 1];
  
  map<ll, int> numMap;
  for(int i = 0; i <= n; i++)
    numMap[nums[i]] = 0;
  int numCnt = 0;
  for(auto e: numMap)
    numMap[e.first] = numCnt++;
  vector<ll> numOf(numCnt);
  for(auto e: numMap)
    numOf[e.second] = e.first;

  segNode* root = new segNode();
  int leafNum = 1;
  while(leafNum < numCnt) leafNum *= 2;

  segInit(root, 0, leafNum);
  segRoots.push_back(root);
  for(int i = 1; i <= n; i++){
    segNode* curTree = new segNode();
    segUpdate(curTree, segRoots.back(), numMap[nums[i - 1]]);
    segRoots.push_back(curTree);
  }

  priority_queue<PQNode> PQ;
  for(int i = 1; i <= n; i++)
    PQ.push({nums[i] - numOf[segGetVal(segRoots[i], 1)], i, 1});
  
  for(int i = 0; i < k; i++){
    PQNode curNode = PQ.top();
    PQ.pop();

    cout << curNode.val << " ";

    if(curNode.k + 1 <= curNode.idx)
      PQ.push({nums[curNode.idx] - numOf[segGetVal(segRoots[curNode.idx], curNode.k + 1)], curNode.idx, curNode.k + 1});
  }


  return 0;
}