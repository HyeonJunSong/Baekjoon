#include <iostream>
#include <vector>

using namespace std;

class Node{
public:
  int st;
  int ed;
  int sum;
};

int leafNum = 1;
vector<Node> segTree;

void segInit(int N, vector<int>& arr){
  while(leafNum < N) leafNum *= 2;
  segTree = vector<Node>(2 * leafNum);

  for(int i = 0; i < N; i++){
    segTree[leafNum + i].st = i;
    segTree[leafNum + i].ed = i + 1;
    segTree[leafNum + i].sum = arr[i];
  }

  for(int i = N; i < leafNum; i++){
    segTree[leafNum + i].st = i;
    segTree[leafNum + i].ed = i + 1;
  }

  for(int i = leafNum - 1; i > 0; i--){
    segTree[i].st = segTree[2 * i].st;
    segTree[i].ed = segTree[2 * i + 1].ed;
    segTree[i].sum = segTree[2 * i].sum + segTree[2 * i + 1].sum;
  }

}

void segDelete(int i){
  int cur = leafNum + i;
  int toDelete = segTree[cur].sum;
  while(cur >= 1){
    segTree[cur].sum -= toDelete;
    cur /= 2;
  }
}

int segGet(int idx, int amount){
  if(segTree[idx].st + 1 == segTree[idx].ed){
    return idx - leafNum;
  }

  if(segTree[2 * idx].sum >= amount)
    return segGet(2 * idx, amount);
  else
    return segGet(2 * idx + 1, amount - segTree[2 * idx].sum);
}

int main(){

  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  int N;
  cin >> N;
  vector<int> w(N);
  for(int i = 0; i < N; i++)
    cin >> w[i];
  
  segInit(N, w);

  vector<int> ans(N);
  for(int i = 0; i < N; i++){
    int p;
    cin >> p;

    ans[i] = segGet(1, p);
    segDelete(ans[i]);
  }

  for(auto e: ans)
    cout << e + 1 << " ";
  
  return 0;
}