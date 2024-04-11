#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#define LL long long

class Node{
public:
  int st;
  int ed;
  LL sum;
  int cnt;
};

int leafNum = 1;
vector<Node> segTree;

void segInit(int N){
  while(leafNum < N) leafNum *= 2;

  segTree = vector<Node>(leafNum * 2);

  for(int i = 0; i < N; i++){
    segTree[leafNum + i].st = i;
    segTree[leafNum + i].ed = i + 1;
    segTree[leafNum + i].sum = 0;
    segTree[leafNum + i].cnt = 0;
  }

  for(int i = N; i < leafNum; i++){
    segTree[leafNum + i].st = i;
    segTree[leafNum + i].ed = i + 1;
    segTree[leafNum + i].sum = 0;
    segTree[leafNum + i].cnt = 0;
  }

  for(int i = leafNum - 1; i > 0; i--){
    segTree[i].st = segTree[2 * i].st;
    segTree[i].ed = segTree[2 * i + 1].ed;
    segTree[i].sum = 0;
    segTree[i].cnt = 0;
  }
}

void segUpdate(int idx, LL val){
  int segIdx = leafNum + idx;
  while(segIdx >= 1){
    segTree[segIdx].sum += val;
    segTree[segIdx].cnt += 1;
    segIdx /= 2;
  }
}

int segGetCnt(int idx, LL TLeft){

  if(segTree[idx].st + 1 == segTree[idx].ed){
    if(segTree[idx].sum > TLeft)
      return 0;
    else
      return segTree[idx].cnt;
  }

  if(segTree[2 * idx].sum >= TLeft)
    return segGetCnt(2 * idx, TLeft);
  return segTree[2 * idx].cnt + segGetCnt(2 * idx + 1, TLeft - segTree[2 * idx].sum);
}

int main(){

  LL N, T, P;
  cin >> N >> T >> P;
  
  vector<pair<LL, int>> K(N);
  for(int i = 0; i < N; i++){
    cin >> K[i].first;
    K[i].second = i;
  }
  sort(K.begin(), K.end());

  segInit(N);

  vector<int> idxOrder(N);
  for(int i = 0; i < N; i++)
    idxOrder[K[i].second] = i;
  
  int ans = 0;
  for(int i = 0; i < N; i++){
    segUpdate(idxOrder[i], K[idxOrder[i]].first);
    ans = max(ans, segGetCnt(1, T - P * i));
  }

  cout << ans;

  return 0;
}