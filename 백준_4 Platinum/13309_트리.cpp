#include <iostream>
#include <vector>

using namespace std;

int N, Q;
vector<vector<int>> tree;
vector<int> locOf;
vector<int> endPoints;

vector<pair<int, pair<int, int>>> segTree;

int initEndPoint(int idx, int parentIdx);
void initSegTree();
void changeNum(int st, int ed, int idx, int num);
int findMaxNum(int idx, int point);

int main(){

  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  cin >> N >> Q;
  tree = vector<vector<int>>(N + 1);
  for(int i = 2; i <= N; i++){
    int parent;
    cin >> parent;
    tree[parent].push_back(i);
  }

  locOf = vector<int>(N + 1, 0);
  initEndPoint(1, 0);

  initSegTree();

  for(int q = 0; q < Q; q++){
    int b, c, d;
    cin >> b >> c >> d;

    if(d == 0){
      if(findMaxNum(1, locOf[b]) == findMaxNum(1, locOf[c]))
        cout << "YES\n";
      else
        cout << "NO\n";
    } else {
      if(findMaxNum(1, locOf[b]) == findMaxNum(1, locOf[c])){
        cout << "YES\n";
        changeNum(locOf[b], endPoints[locOf[b]] + 1, 1, locOf[b]);
      }
      else{
        cout << "NO\n";
        changeNum(locOf[c], endPoints[locOf[c]] + 1, 1, locOf[c]);
      }
    }
  }

  return 0;
}

int initEndPoint(int idx, int parentIdx){

  int curEndPointIdx = endPoints.size();
  locOf[idx] = curEndPointIdx;
  endPoints.push_back(-1);

  int endPoint = curEndPointIdx;
  for(auto e: tree[idx]){
    if(e == parentIdx) continue;

    endPoint = initEndPoint(e, idx);
  }

  endPoints[curEndPointIdx] = endPoint;
  return endPoint;
}

void initSegTree(){
  int leafNum = 1;
  while(leafNum < N)
    leafNum *= 2;
  
  segTree = vector<pair<int, pair<int, int>>>(2 * leafNum, {0, {0, 0}});
  for(int i = 0; i < leafNum; i++){
    segTree[leafNum + i].second.first = i;
    segTree[leafNum + i].second.second = i + 1;
  }
  for(int i = leafNum - 1; i > 0; i--){
    segTree[i].second.first = segTree[2 * i].second.first;
    segTree[i].second.second = segTree[2 * i + 1].second.second;
  }
}

void changeNum(int st, int ed, int idx, int num){
  if(segTree[idx].second.first == st && segTree[idx].second.second == ed){
    segTree[idx].first = max(segTree[idx].first, num);
    return;
  }

  if(ed <= segTree[2 * idx].second.second){
    changeNum(st, ed, 2 * idx, num);
    return;
  }
  if(st >= segTree[2 * idx + 1].second.first){
    changeNum(st, ed, 2 * idx + 1, num);
    return;
  }

  changeNum(st, segTree[2 * idx].second.second, 2 * idx, num);
  changeNum(segTree[2 * idx + 1].second.first, ed, 2 * idx + 1, num);
  return;
}

int findMaxNum(int idx, int point){
  if(segTree[idx].second.first == point && segTree[idx].second.second == point + 1)
    return segTree[idx].first;

  if(point >= segTree[2 * idx + 1].second.first)
    return max(segTree[idx].first, findMaxNum(2 * idx + 1, point));
  else
    return max(segTree[idx].first, findMaxNum(2 * idx, point));
}