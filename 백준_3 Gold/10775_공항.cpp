#include <iostream>
#include <vector>

using namespace std;

int G, P;
vector<int> g;
vector<pair<pair<int, int>, int>> segTree;

int findMaxFalse(int idx, int st, int ed){
  if(segTree[idx].first.first == st && segTree[idx].first.second == ed)
    return segTree[idx].second;
  
  if(segTree[2 * idx].first.second >= ed)
    return findMaxFalse(2 * idx, st, ed);
  if(segTree[2 * idx + 1].first.first <= st)
    return findMaxFalse(2 * idx + 1, st, ed);
  
  return max(segTree[2 * idx].second, findMaxFalse(2 * idx + 1, segTree[2 * idx + 1].first.first, ed));
}

int targetToTrue(int idx, int target){
  if(segTree[idx].first.first == target && segTree[idx].first.second == target + 1){
    segTree[idx].second = -1;
    return -1;
  }
  
  if(segTree[2 * idx].first.second >= target + 1){
    segTree[idx].second = max(targetToTrue(2 * idx, target), segTree[2 * idx + 1].second);
    return segTree[idx].second;
  }
  if(segTree[2 * idx + 1].first.first <= target){
    segTree[idx].second = max(segTree[2 * idx].second, targetToTrue(2 * idx + 1, target));
    return segTree[idx].second;
  }
}


int main(){

  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  cin >> G >> P;
  g = vector<int>(P);
  for(int i = 0; i < P; i++)
    cin >> g[i];

  int leafNum = 1;
  while(leafNum < G)
    leafNum *= 2;
  
  segTree = vector<pair<pair<int, int>, int>>(leafNum * 2);

  for(int i = 0; i < G; i++){
    segTree[leafNum + i].first.first = i;
    segTree[leafNum + i].first.second = i + 1;
    segTree[leafNum + i].second = i;
  }
  for(int i = G; i < leafNum; i++){
    segTree[leafNum + i].first.first = i;
    segTree[leafNum + i].first.second = i + 1;
    segTree[leafNum + i].second = -1;
  }
  for(int i = leafNum - 1; i > 0; i--){
    segTree[i].first.first = segTree[2 * i].first.first;
    segTree[i].first.second = segTree[2 * i + 1].first.second;
    segTree[i].second = segTree[2 * i + 1].second;
  }

  int ans = 0;
  for(auto e : g){
    int curLoc = findMaxFalse(1, 0, e);
    if(0 <= curLoc && curLoc < G){
      ans += 1;
      targetToTrue(1, curLoc);
    }
    else
      break;
  }
  cout << ans;

  return 0;
}