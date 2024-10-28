#include <iostream>
#include <vector>

using namespace std;

class Node{
  public:
  int st;
  int ed;
  int val;
  int ans;
};

int leafNum = 1;
vector<Node> segTree;
void segInit(int N, vector<int>& nums){
  while(leafNum < N) leafNum *= 2;
  segTree = vector<Node>(leafNum * 2);

  for(int i = 0; i < N; i++){
    segTree[leafNum + i].st = i;
    segTree[leafNum + i].ed = i + 1;
    segTree[leafNum + i].val = nums[i];
    segTree[leafNum + i].ans = i + 1;
  }
  for(int i = N; i < leafNum; i++){
    segTree[leafNum + i].st = i;
    segTree[leafNum + i].ed = i + 1;
    segTree[leafNum + i].val = 1000000001;
    segTree[leafNum + i].ans = i + 1;
  }

  for(int i = leafNum - 1; i > 0; i--){
    segTree[i].st = segTree[2 * i].st;
    segTree[i].ed = segTree[2 * i + 1].ed;
    segTree[i].val = min(segTree[2 * i].val, segTree[2 * i + 1].val);
    
    if(segTree[2 * i].val < segTree[2 * i + 1].val)
      segTree[i].ans = segTree[2 * i].ans;
    else if(segTree[2 * i].val > segTree[2 * i + 1].val)
      segTree[i].ans = segTree[2 * i + 1].ans;
    else
      segTree[i].ans = segTree[2 * i].ans;
  }
}

void segUpdate(int idx, int val){
  idx += leafNum;

  segTree[idx].val = val;

  idx /= 2;
  while(idx > 0){
    segTree[idx].val = min(segTree[2 * idx].val, segTree[2 * idx + 1].val);
    
    if(segTree[2 * idx].val < segTree[2 * idx + 1].val)
      segTree[idx].ans = segTree[2 * idx].ans;
    else if(segTree[2 * idx].val > segTree[2 * idx + 1].val)
      segTree[idx].ans = segTree[2 * idx + 1].ans;
    else
      segTree[idx].ans = segTree[2 * idx].ans;

    idx /= 2;
  }
}


int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  int N;
  cin >> N;
  vector<int> nums(N);
  for(int i = 0; i < N; i++)
    cin >> nums[i];
  
  segInit(N, nums);
  
  int Q;
  cin >> Q;
  
  for(int q = 0; q < Q; q++){
    int query;
    cin >> query;

    if(query == 1){
      int idx, val;
      cin >> idx >> val;
      segUpdate(idx - 1, val);
    } else {
      cout << segTree[1].ans << '\n';
    }
  }

  return 0;
}