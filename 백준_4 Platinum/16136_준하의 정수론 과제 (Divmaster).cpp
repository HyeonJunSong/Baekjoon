#include <iostream>
#include <vector>

using namespace std;

#define ll long long

vector<bool> ifPrime;
void era(){
  ifPrime.assign(1000001, true);
  for(int i = 2; i < 1000001; i++){
    if(!ifPrime[i]) continue;
    for(int j = i + i; j < 1000001; j += i)
      ifPrime[j] = false;
  }
}
int getDivCnt(int num){  
  int divCnt = 1;
  int curDiv = 2;
  while(num != 1){

    if(ifPrime[num]){
      divCnt *= 2;
      break;
    }

    if(!ifPrime[curDiv] || num % curDiv != 0){
      curDiv++;
      continue;
    }

    int curDivCnt = 0;
    while(num % curDiv == 0){
      num /= curDiv;
      curDivCnt++;
    }
    divCnt *= (curDivCnt + 1);
    curDiv++;
  }

  return divCnt;
}

class segNode{
  public:
  int st;
  int ed;
  ll val;
  bool ifDone;
};

int leafNum = 1;
vector<segNode> segTree;
void segInit(vector<ll>& nums){
  while(leafNum < nums.size()) leafNum *= 2;
  segTree = vector<segNode>(2 * leafNum);
  
  for(int i = 0; i < nums.size(); i++){
    segTree[leafNum + i].st = i;
    segTree[leafNum + i].ed = i + 1;
    segTree[leafNum + i].val = nums[i];
    segTree[leafNum + i].ifDone = (nums[i] == 1 || nums[i] == 2);
  }
  
  for(int i = nums.size(); i < leafNum; i++){
    segTree[leafNum + i].st = i;
    segTree[leafNum + i].ed = i + 1;
    segTree[leafNum + i].val = 0;
    segTree[leafNum + i].ifDone = true;
  }

  for(int i = leafNum - 1; i > 0; i--){
    segTree[i].st = segTree[2 * i].st;
    segTree[i].ed = segTree[2 * i + 1].ed;
    segTree[i].val = segTree[2 * i].val + segTree[2 * i + 1].val;
    segTree[i].ifDone = segTree[2 * i].ifDone && segTree[2 * i + 1].ifDone;
  }
}

void segUpdate(int idx, int st, int ed){
  if(segTree[idx].ifDone) return;

  if(segTree[idx].ed - segTree[idx].st == 1){
    segTree[idx].val = (ll)(getDivCnt(segTree[idx].val));
    if(segTree[idx].val == 2) segTree[idx].ifDone = true;

    return;
  }

  if(ed <= segTree[2 * idx].ed)
    segUpdate(2 * idx, st, ed);
  else if(st >= segTree[2 * idx + 1].st)
    segUpdate(2 * idx + 1, st, ed);
  else{
    segUpdate(2 * idx, st, segTree[2 * idx].ed);
    segUpdate(2 * idx + 1, segTree[2 * idx + 1].st, ed);
  }
  segTree[idx].val = segTree[2 * idx].val + segTree[2 * idx + 1].val;
  segTree[idx].ifDone = segTree[2 * idx].ifDone && segTree[2 * idx + 1].ifDone;
}

ll segGetVal(int idx, int st, int ed){
  if(segTree[idx].st == st && segTree[idx].ed == ed)
    return segTree[idx].val;

  if(ed <= segTree[2 * idx].ed)
    return segGetVal(2 * idx, st, ed);
  if(st >= segTree[2 * idx + 1].st)
    return segGetVal(2 * idx + 1, st, ed);
  return segGetVal(2 * idx, st, segTree[2 * idx].ed) + segGetVal(2 * idx + 1, segTree[2 * idx + 1].st, ed);
}

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  int N, Q;
  cin >> N >> Q;

  vector<ll> nums;
  nums.assign(N, 0);
  for(int i = 0; i < N; i++)
    cin >> nums[i];
  
  era();
  segInit(nums);

  for(int q = 0; q < Q; q++){
    int T, S, E;
    cin >> T >> S >> E;

    if(T == 1){
      segUpdate(1, S - 1, E);
    } else {
      cout << segGetVal(1, S - 1, E) << "\n";
    }
  }

  return 0;
}