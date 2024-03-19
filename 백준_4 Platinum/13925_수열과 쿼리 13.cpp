#include <iostream>
#include <vector>

using namespace std;

#define LL long long

class node{
public:
  int st;
  int ed;
  LL val;
  pair<LL, LL> op;
};

int leafNum = 1;
vector<node> segTree;

#define MOD 1000000007

void initTree(vector<LL>& arr, int N){
  while(leafNum < N)
    leafNum *= 2;
  
  segTree = vector<node>(leafNum * 2);
  for(int i = 0; i < N; i++){
    segTree[leafNum + i].st = i;
    segTree[leafNum + i].ed = i + 1;
    segTree[leafNum + i].val = arr[i];
    segTree[leafNum + i].op = {1, 0};
  }
  for(int i = N; i < leafNum; i++){
    segTree[leafNum + i].st = i;
    segTree[leafNum + i].ed = i + 1;
    segTree[leafNum + i].val = 0;
  }

  for(int i = leafNum - 1; i > 0; i--){
    segTree[i].st = segTree[2 * i].st;
    segTree[i].ed = segTree[2 * i + 1].ed;
    segTree[i].val = (segTree[2 * i].val + segTree[2 * i + 1].val) % MOD;
    segTree[i].op = {-1, 0};
  }
}

LL command(int idx, int st, int ed, LL a, LL b){

  if(segTree[idx].st == st && segTree[idx].ed == ed){

    if(segTree[idx].op.first == -1){
      segTree[idx].op.first = a;
      segTree[idx].op.second = b;
    }
    else {
      segTree[idx].op.first *= a;
      segTree[idx].op.second *= a;
      segTree[idx].op.second %= MOD;
      segTree[idx].op.second += b;

      segTree[idx].op.first %= MOD;
      segTree[idx].op.second %= MOD;
    }

    segTree[idx].val = ((segTree[idx].val * a) % MOD + (b * (ed - st)) % MOD) % MOD;

    return segTree[idx].val;
  }

  if(segTree[idx].op.first != -1){

    command(2 * idx, segTree[2 * idx].st, segTree[2 * idx].ed, segTree[idx].op.first, segTree[idx].op.second);
    command(2 * idx + 1, segTree[2 * idx + 1].st, segTree[2 * idx + 1].ed, segTree[idx].op.first, segTree[idx].op.second);

    segTree[idx].op.first = -1;
  }

  LL ans;

  if(ed <= segTree[2 * idx].ed){
    ans = command(2 * idx, st, ed, a, b);
  } else if(segTree[2 * idx + 1].st <= st){
    ans = command(2 * idx + 1, st, ed, a, b);
  } else {
    ans = (command(2 * idx, st, segTree[2 * idx].ed, a, b) + command(2 * idx + 1, segTree[2 * idx + 1].st, ed, a, b)) % MOD;
  }

  segTree[idx].val = (segTree[2 * idx].val + segTree[2 * idx + 1].val) % MOD;
  
  return ans;
}

int main(){

  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  int N;
  cin >> N;

  vector<LL> arr(N);
  for(int i = 0; i < N; i++)
    cin >> arr[i];
  
  initTree(arr, N);
  
  int M;
  cin >> M;
  for(int i = 0; i < M; i++){
    int c;
    cin >> c;

    int x, y;
    LL v;
    switch(c){
      case 4:
        cin >> x >> y;
        cout << command(1, x - 1, y, 1, 0) << "\n";
      break;
      default:
        cin >> x >> y >> v;
        switch(c){
          case 1:
            command(1, x - 1, y, 1, v);
            break;
          case 2:
            command(1, x - 1, y, v, 0);
            break;
          case 3:
            command(1, x - 1, y, 0, v);
            break;
        }
      break;
    }
  }

  return 0;
}