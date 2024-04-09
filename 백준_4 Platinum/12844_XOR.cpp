#include <iostream>
#include <vector>

using namespace std;

class Node{
public:
  int st;
  int ed;
  int lazy;
  int val;

};

int leafNum = 1;
vector<Node> segTree;

void initSegTree(int N, vector<int>& A){

  while(leafNum < N) leafNum *= 2;

  segTree = vector<Node>(2 * leafNum);

  for(int i = 0; i < N; i++){
    segTree[leafNum + i].st = i;
    segTree[leafNum + i].ed = i + 1;
    segTree[leafNum + i].lazy = -1;
    segTree[leafNum + i].val = A[i];
  }

  for(int i = N; i < leafNum; i++){
    segTree[leafNum + i].st = i;
    segTree[leafNum + i].ed = i + 1;
    segTree[leafNum + i].val = 0;
  }

  for(int i = leafNum - 1; i > 0; i--){
    segTree[i].st = segTree[2 * i].st;
    segTree[i].ed = segTree[2 * i + 1].ed;
    segTree[i].lazy = -1;
    segTree[i].val = segTree[2 * i].val ^ segTree[2 * i + 1].val;
  }
}
void updateSegTree(int idx, int st, int ed, int k){
  if(segTree[idx].st == st && segTree[idx].ed == ed){

    if((ed - st) % 2 != 0)
      segTree[idx].val ^= k;

    if(segTree[idx].lazy != -1)
      segTree[idx].lazy ^= k;
    else
      segTree[idx].lazy = k;
    
    return;
  }
  
  if(segTree[idx].lazy != -1){
    updateSegTree(2 * idx, segTree[2 * idx].st, segTree[2 * idx].ed, segTree[idx].lazy);
    updateSegTree(2 * idx + 1, segTree[2 * idx + 1].st, segTree[2 * idx + 1].ed, segTree[idx].lazy);
    segTree[idx].lazy = -1;
  }

  if(segTree[2 * idx].ed >= ed)
    updateSegTree(2 * idx, st, ed, k);
  else if(segTree[2 * idx + 1].st <= st)
    updateSegTree(2 * idx + 1, st, ed, k);
  else{
    updateSegTree(2 * idx, st, segTree[2 * idx].ed, k);
    updateSegTree(2 * idx + 1, segTree[2 * idx + 1].st, ed, k);
  }
  segTree[idx].val = segTree[2 * idx].val ^ segTree[2 * idx + 1].val;

  return;
}

int getValSegTree(int idx, int st, int ed){
  if(segTree[idx].st == st && segTree[idx].ed == ed)
    return segTree[idx].val;
  
  if(segTree[idx].lazy != -1){
    updateSegTree(2 * idx, segTree[2 * idx].st, segTree[2 * idx].ed, segTree[idx].lazy);
    updateSegTree(2 * idx + 1, segTree[2 * idx + 1].st, segTree[2 * idx + 1].ed, segTree[idx].lazy);
    segTree[idx].lazy = -1;
  }

  if(segTree[2 * idx].ed >= ed)
    return getValSegTree(2 * idx, st, ed);
  if(segTree[2 * idx + 1].st <= st)
    return getValSegTree(2 * idx + 1, st, ed);
  
  return getValSegTree(2 * idx, st, segTree[2 * idx].ed) ^ getValSegTree(2 * idx + 1, segTree[2 * idx + 1].st, ed);
}


int main(){

  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  int N;
  cin >> N;
  vector<int> A(N);
  for(int i = 0; i < N; i++)
    cin >> A[i];

  initSegTree(N, A);

  int Q;
  cin >> Q;
  for(int q = 0; q < Q; q++){
    int query, i, j, k;
    cin >> query;
    switch(query){
      case 1:
        cin >> i >> j >> k;
        j++;
        updateSegTree(1, i, j, k);
      break;
      case 2:
        cin >> i >> j;
        j++;
        cout << getValSegTree(1, i, j) << "\n";
      break;
    }
  }


  return 0;
}