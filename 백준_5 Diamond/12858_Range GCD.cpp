#include <iostream>
#include <vector>

using namespace std;

#define ll long long

ll gcd(ll a, ll b){
  if(a > b) swap(a, b);

  //0은 매직넘버로 처리
  if(a == 0) return b;

  while(b % a != 0){
    b %= a;
    swap(a, b);
  }

  return a;
}

class Node{
  public:
  int st;
  int ed;
  
  ll fVal;
  ll rVal;
  ll diffGcd;

  ll lazy;
};

int leafNum = 1;
vector<Node> segTree;
void segInit(int N, vector<ll>& nums){
  while(leafNum < N) leafNum *= 2;
  segTree = vector<Node>(leafNum * 2);
  
  for(int i = 0; i < N; i++){
    segTree[leafNum + i].st = i;
    segTree[leafNum + i].ed = i + 1;
    segTree[leafNum + i].fVal = nums[i];
    segTree[leafNum + i].rVal = nums[i];
    segTree[leafNum + i].diffGcd = 0;
    segTree[leafNum + i].lazy = 0;
  }  
  for(int i = N; i < leafNum; i++){
    segTree[leafNum + i].st = i;
    segTree[leafNum + i].ed = i + 1;
    segTree[leafNum + i].fVal = 0;
    segTree[leafNum + i].rVal = 0;
    segTree[leafNum + i].diffGcd = 0;
    segTree[leafNum + i].lazy = 0;
  }

  for(int i = leafNum - 1; i > 0; i--){
    segTree[i].st = segTree[2 * i].st;
    segTree[i].ed = segTree[2 * i + 1].ed;
    segTree[i].fVal = segTree[2 * i].fVal;
    segTree[i].rVal = segTree[2 * i + 1].rVal;
    segTree[i].diffGcd = gcd(gcd(segTree[2 * i].diffGcd, segTree[2 * i + 1].diffGcd), abs(segTree[2 * i].rVal - segTree[2 * i + 1].fVal));
    segTree[i].lazy = 0;
  }

}

void segUpdate(int idx, int st, int ed, ll val){
  if(segTree[idx].st == st && segTree[idx].ed == ed){
    segTree[idx].fVal += val;
    segTree[idx].rVal += val;
    segTree[idx].lazy += val;
    return;
  }

  if(segTree[idx].lazy > 0){
    segUpdate(2 * idx, segTree[2 * idx].st, segTree[2 * idx].ed, segTree[idx].lazy);
    segUpdate(2 * idx + 1, segTree[2 * idx + 1].st, segTree[2 * idx + 1].ed, segTree[idx].lazy);
    segTree[idx].lazy = 0;
  }

  if(ed <= segTree[2 * idx].ed)
    segUpdate(2 * idx, st, ed, val);
  else if(st >= segTree[2 * idx + 1].st)
    segUpdate(2 * idx + 1, st, ed, val);
  else{
    segUpdate(2 * idx, st, segTree[2 * idx].ed, val);
    segUpdate(2 * idx + 1, segTree[2 * idx + 1].st, ed, val);
  }

  segTree[idx].diffGcd = gcd(gcd(segTree[2 * idx].diffGcd, segTree[2 * idx + 1].diffGcd), abs(segTree[2 * idx].rVal - segTree[2 * idx + 1].fVal));
  segTree[idx].fVal = segTree[2 * idx].fVal;
  segTree[idx].rVal = segTree[2 * idx + 1].rVal;
}

ll segGetVal(int idx, int st, int ed){
  if(segTree[idx].st == st && segTree[idx].ed == ed)
    return gcd(segTree[idx].diffGcd, gcd(segTree[idx].fVal, segTree[idx].rVal));

  if(segTree[idx].lazy > 0){
    segUpdate(2 * idx, segTree[2 * idx].st, segTree[2 * idx].ed, segTree[idx].lazy);
    segUpdate(2 * idx + 1, segTree[2 * idx + 1].st, segTree[2 * idx + 1].ed, segTree[idx].lazy);
    segTree[idx].lazy = 0;
    segTree[idx].diffGcd = gcd(gcd(segTree[2 * idx].diffGcd, segTree[2 * idx + 1].diffGcd), abs(segTree[2 * idx].rVal - segTree[2 * idx + 1].fVal));
    segTree[idx].fVal = segTree[2 * idx].fVal;
    segTree[idx].rVal = segTree[2 * idx + 1].rVal;
  }

  if(ed <= segTree[2 * idx].ed)
    return segGetVal(2 * idx, st, ed);
  if(st >= segTree[2 * idx + 1].st)
    return segGetVal(2 * idx + 1, st, ed);
  return gcd(segGetVal(2 * idx, st, segTree[2 * idx].ed), segGetVal(2 * idx + 1, segTree[2 * idx + 1].st, ed));
}

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  int N;
  cin >> N;
  vector<ll> nums(N);
  for(int i = 0; i < N; i++)
    cin >> nums[i];

  segInit(N, nums);

  int Q;
  cin >> Q;

  for(int q = 0; q < Q; q++){
    int T, A, B;
    cin >> T >> A >> B;

    if(T == 0)
      cout << segGetVal(1, A - 1, B) << '\n';
    else
      segUpdate(1, A - 1, B, (ll)T);
  }



  return 0;
}