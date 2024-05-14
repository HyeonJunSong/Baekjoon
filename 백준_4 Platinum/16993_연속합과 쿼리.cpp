#include <iostream>
#include <vector>

using namespace std;

#define NINF -1001

class Val{
public:
  //{최대 연속합, {좌측 부터 최대 연속합, 우측 부터 최대 연속합}}
  pair<int, pair<int, int>> val;
  //누적합
  int accumSum;

};

class Node{
public:
  int st;
  int ed;
  Val v;

};

vector<Node> segTree;
int leafNum = 1;
void segInit(int N, vector<int>& arr){
  while(leafNum < N) leafNum *= 2;
  segTree = vector<Node>(2 * leafNum);

  for(int i = 0; i < N; i++){
    segTree[leafNum + i].st = i;
    segTree[leafNum + i].ed = i + 1;
    segTree[leafNum + i].v.val = {arr[i], {arr[i], arr[i]}};
    segTree[leafNum + i].v.accumSum = arr[i];
  }
  for(int i = N; i < leafNum; i++){
    segTree[leafNum + i].st = i;
    segTree[leafNum + i].ed = i + 1;
    segTree[leafNum + i].v.val = {NINF, {NINF, NINF}};
    segTree[leafNum + i].v.accumSum = NINF;
  }

  for(int i = leafNum - 1; i > 0; i--){
    segTree[i].st = segTree[2 * i].st;
    segTree[i].ed = segTree[2 * i + 1].ed;
    segTree[i].v.accumSum = segTree[2 * i].v.accumSum + segTree[2 * i + 1].v.accumSum;

    segTree[i].v.val.second.first = max(segTree[2 * i].v.val.second.first, segTree[2 * i].v.accumSum + segTree[2 * i + 1].v.val.second.first);
    segTree[i].v.val.second.second = max(segTree[2 * i + 1].v.val.second.second, segTree[2 * i + 1].v.accumSum + segTree[2 * i].v.val.second.second);

    segTree[i].v.val.first = NINF;
    segTree[i].v.val.first = max(segTree[i].v.val.first, segTree[2 * i].v.val.first);
    segTree[i].v.val.first = max(segTree[i].v.val.first, segTree[2 * i + 1].v.val.first);
    segTree[i].v.val.first = max(segTree[i].v.val.first, segTree[2 * i].v.val.second.second + segTree[2 * i + 1].v.val.second.first);
  }
}

Val segGetVal(int idx, int st, int ed){
  if(segTree[idx].st == st && segTree[idx].ed == ed)
    return segTree[idx].v;
  
  if(ed <= segTree[2 * idx].ed)
    return segGetVal(2 * idx, st, ed);
  if(segTree[2 * idx + 1].st <= st)
    return segGetVal(2 * idx + 1, st, ed);
  
  Val left = segGetVal(2 * idx, st, segTree[2 * idx].ed);
  Val righ = segGetVal(2 * idx + 1, segTree[2 * idx + 1].st, ed);

  Val curRes;
  curRes.accumSum = left.accumSum + righ.accumSum;
  curRes.val.second.first = max(left.val.second.first, left.accumSum + righ.val.second.first);
  curRes.val.second.second = max(righ.val.second.second, righ.accumSum + left.val.second.second);
  curRes.val.first = NINF;
  curRes.val.first = max(curRes.val.first, left.val.first);
  curRes.val.first = max(curRes.val.first, righ.val.first);
  curRes.val.first = max(curRes.val.first, left.val.second.second + righ.val.second.first);
  
  return curRes;
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
  segInit(N, A);

  int M;
  cin >> M;
  int I, J;
  for(int i = 0; i < M; i++){
    cin >> I >> J;
    cout << segGetVal(1, I - 1, J).val.first << "\n";
  }

  return 0;
}