#include <iostream>
#include <vector>

#define ll long long
#define NINF -1000000001

using namespace std;

class Node{
public:
  int st;
  int ed;
  ll maxVal;
};

int leafNum = 1;
vector<Node> segTree;

void segInit(int N){
  while(leafNum < N) leafNum *= 2;

  segTree = vector<Node>(2 * leafNum);
  for(int i = 0; i < leafNum; i++){
    segTree[leafNum + i].st = i;
    segTree[leafNum + i].ed = i + 1;
    segTree[leafNum + i].maxVal = NINF;
  }
  for(int i = leafNum - 1; i > 0; i--){
    segTree[i].st = segTree[2 * i].st;
    segTree[i].ed = segTree[2 * i + 1].ed;
    segTree[i].maxVal = NINF;
  }
}

void segUpdate(int idx, ll val){
  int segIdx = leafNum + idx;
  segTree[segIdx].maxVal = val;
  segIdx /= 2;

  while(segIdx >= 1){
    segTree[segIdx].maxVal = max(segTree[2 * segIdx].maxVal, segTree[2 * segIdx + 1].maxVal);
    segIdx /= 2;
  }
}

ll segGetVal(int idx, int st, int ed){
  if(segTree[idx].st == st && segTree[idx].ed == ed)
    return segTree[idx].maxVal;
  
  if(segTree[2 * idx].ed >= ed)
    return segGetVal(2 * idx, st, ed);
  if(segTree[2 * idx + 1].st <= st)
    return segGetVal(2 * idx + 1, st, ed);
  
  return max(segGetVal(2 * idx, st, segTree[2 * idx].ed), segGetVal(2 * idx + 1, segTree[2 * idx + 1].st, ed));
}

int main(){

  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int N, D;
  cin >> N >> D;

  vector<ll> K;
  K = vector<ll>(N);
  for(int i = 0; i < N; i++)
    cin >> K[i];
  
  segInit(N);
  
  ll ans = K[N - 1];
  segUpdate(N - 1, K[N - 1]);
  for(int i = N - 2; i >= 0; i--){
    ll curSegMax = max(0LL, segGetVal(1, i + 1, min(N - 1, i + D) + 1)) + K[i];
    ans = max(ans, curSegMax);
    segUpdate(i, curSegMax);
  }

  cout << ans;


  return 0;
}