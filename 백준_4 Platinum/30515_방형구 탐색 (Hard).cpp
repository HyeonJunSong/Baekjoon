#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

vector<pair<int, int>> A;
map<int, int> aliveIdx;

struct node{
  int aliveCnt;
  int st;
  int ed;
};

typedef struct node Node;

int leafNum = 1;
vector<Node> segTree;

void segTreeInit(int N){
  while(leafNum < N) leafNum *= 2;
  segTree = vector<Node>(leafNum * 2);

  for(int i = 0; i < N; i++){
    segTree[leafNum + i].st = i;
    segTree[leafNum + i].ed = i + 1;
    segTree[leafNum + i].aliveCnt = 1;
  }

  for(int i = N; i < leafNum; i++){
    segTree[leafNum + i].st = i;
    segTree[leafNum + i].ed = i + 1;
    segTree[leafNum + i].aliveCnt = 0;
  }

  for(int i = leafNum - 1; i > 0; i--){
    segTree[i].st = segTree[2 * i].st;
    segTree[i].ed = segTree[2 * i + 1].ed;
    segTree[i].aliveCnt = segTree[2 * i].aliveCnt + segTree[2 * i + 1].aliveCnt;
  }
}

void segTreeDelete(int idx){
  int curIdx = leafNum + idx;

  while(curIdx >= 1){
    segTree[curIdx].aliveCnt--;
    curIdx /= 2;
  }
}

int segTreeSearch(int idx, int st, int ed){
  if(segTree[idx].st == st && segTree[idx].ed == ed){
    return segTree[idx].aliveCnt;
  }

  if(segTree[2 * idx].ed >= ed)
    return segTreeSearch(2 * idx, st, ed);
  if(segTree[2 * idx + 1].st <= st)
    return segTreeSearch(2 * idx + 1, st, ed);
  
  return segTreeSearch(2 * idx, st, segTree[2 * idx].ed) + segTreeSearch(2 * idx + 1, segTree[2 * idx + 1].st, ed);
}

int query1(int l, int r, int k){

  int st, ed;
  pair<int, int> target;

  int lIdx, rIdx;

  //lower bound 찾기
  st = 0;
  ed = A.size() - 1;
  target = {k, l};
  while(st <= ed){
    int mid = (st + ed) / 2;
    if(A[mid] < target)
      st = mid + 1;
    else
      ed = mid - 1;
  }
  lIdx = st;

  //upper bound 찾기
  st = 0;
  ed = A.size() - 1;
  target = {k, r};
  while(st <= ed){
    int mid = (st + ed) / 2;
    if(A[mid] <= target)
      st = mid + 1;
    else
      ed = mid - 1;
  }
  rIdx = ed;

  if(lIdx > rIdx) return 0;
  return segTreeSearch(1, lIdx, rIdx + 1);
}

void query2(int l, int r){
  
  auto e = aliveIdx.lower_bound(l);
  int upperIdx = 987654321;
  if(aliveIdx.upper_bound(r) != aliveIdx.end())
    upperIdx = aliveIdx.upper_bound(r)->first;
  vector<pair<int, int>> toErase;
  while(e != aliveIdx.end() && e->first != upperIdx){
    segTreeDelete(e->second);
    toErase.push_back(*e);
    e++;
  }
  for(auto e: toErase)
    aliveIdx.erase(e.first);
}

int main(){

  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  int N;
  cin >> N;
  A.assign(N, {0, 0});

  for(int i = 0; i < N; i++){
    cin >> A[i].first;
    A[i].second = i;
  }

  sort(A.begin(), A.end());

  for(int i = 0; i < N; i++)
    aliveIdx[A[i].second] = i;
  
  segTreeInit(N);
  
  int Q;
  cin >> Q;

  for(int q = 0; q < Q; q++){
    int cmd;
    cin >> cmd;

    int l, r, k;
    if(cmd == 1){
      cin >> l >> r >> k;
      l--;r--;
      cout << query1(l, r, k) << "\n";
    } else{
      cin >> l >> r;
      l--;r--;
      query2(l, r);
    }
  }
  return 0;
}