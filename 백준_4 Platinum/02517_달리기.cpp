#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int leafNum = 1;
vector<pair<int, pair<int, int>>> segTree;

void initSegtree(int N){

  while(leafNum < N) leafNum *= 2;

  segTree.assign(leafNum * 2, {0, {0,0}});

  for(int i = 0; i < leafNum; i++){
    segTree[leafNum + i].second.first = i;
    segTree[leafNum + i].second.second = i + 1;
  }

  for(int i = leafNum - 1; i > 0; i--){
    segTree[i].second.first = segTree[2 * i].second.first;
    segTree[i].second.second = segTree[2 * i + 1].second.second;
  }

}

void updateSegtree(int idx){
  int treeIdx = leafNum + idx;
  while(treeIdx >= 1){
    segTree[treeIdx].first++;
    treeIdx /= 2;
  }
}

int getValSegtree(int treeIdx, int st, int ed){
  if(segTree[treeIdx].second.first == st && segTree[treeIdx].second.second == ed)
    return segTree[treeIdx].first;
  
  if(segTree[2 * treeIdx].second.second >= ed)
    return getValSegtree(2 * treeIdx, st, ed);
  if(segTree[2 * treeIdx + 1].second.first <= st)
    return getValSegtree(2 * treeIdx + 1, st, ed);

  return getValSegtree(2 * treeIdx, st, segTree[2 * treeIdx].second.second) + getValSegtree(2 * treeIdx + 1, segTree[2 * treeIdx + 1].second.first, ed);  
}

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  int N;
  cin >> N;

  vector<pair<int, int>> abillity(N);
  for(int i = 0; i < N; i++){
    cin >> abillity[i].first;
    abillity[i].second = i;
  } 

  sort(abillity.begin(), abillity.end());

  initSegtree(N);
  
  vector<int> ans(N);
  for(auto e : abillity){
    ans[e.second] = e.second + 1 - getValSegtree(1, 0, e.second + 1);
    updateSegtree(e.second);
  }

  for(auto e: ans)
    cout << e << "\n";

  return 0;
}