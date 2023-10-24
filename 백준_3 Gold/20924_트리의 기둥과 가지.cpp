////231024
//25m 59s

#include <iostream>
#include <vector>

using namespace std;

int N, R;

vector<vector<pair<int, int>>> tree;

int getMaxBranchLen(int parentNode, int curNode){
  int ans = 0;
  for(auto e: tree[curNode]){
    if(e.first == parentNode) continue;

    int curLen = e.second + getMaxBranchLen(curNode, e.first);
    if(ans < curLen)
      ans = curLen;
  }

  return ans;
}

int main(){

  cin >> N >> R;

  if(N == 1){
    cout << "0 0";
    return 0;
  }
  
  tree = vector<vector<pair<int, int>>>(N + 1);
  for(int i = 0; i < N - 1; i++){
    int a, b, d;
    cin >> a >> b >> d;
    tree[a].push_back({b, d});
    tree[b].push_back({a, d});
  }

  //기가 노드 찾기
  int trunkLen = 0;
  int parent = R;
  if(tree[R].size() == 1){
    trunkLen += tree[R][0].second;
    R = tree[R][0].first;
    while(tree[R].size() == 2){
      if(tree[R][0].first == parent){
        trunkLen += tree[R][1].second;
        parent = R;
        R = tree[R][1].first;
      }
      else{
        trunkLen += tree[R][0].second;
        parent = R;
        R = tree[R][0].first;
      }
    }
  }

  cout << trunkLen << ' ' << getMaxBranchLen(parent, R);

  return 0;
}