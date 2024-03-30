#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<vector<int>> groupOfGrid;

#define LL long long

vector<int> groupOf;
vector<LL> xorValOfGroup;

int getGroupNum(int idx){
  if(groupOf[idx] != idx)
    groupOf[idx] = getGroupNum(groupOf[idx]);
  return groupOf[idx];
}

int dir[4][2] = {
  {-1, 0},
  { 1, 0},
  { 0, 1},
  { 0,-1},
};

int main(){

  int n, m;
  cin >> n >> m;

  vector<pair<LL, pair<int, int>>> values;
  for(int i = 0; i < n; i++){
    for(int j = 0; j < m; j++){
      LL val;
      cin >> val;
      values.push_back({-1 * val, {i, j}});
    }
  }
  sort(values.begin(), values.end());

  groupOfGrid = vector<vector<int>>(n, vector<int>(m, -1));

  LL prevSum = 0;
  LL ans = 0;

  for(auto e: values){

    int curGroupNum = -1;
    for(int d = 0; d < 4; d++){
      if(0 <= e.second.first + dir[d][0] && e.second.first + dir[d][0] < n
      && 0 <= e.second.second + dir[d][1] && e.second.second + dir[d][1] < m
      && groupOfGrid[e.second.first + dir[d][0]][e.second.second + dir[d][1]] != -1){
        if(curGroupNum == -1){
          curGroupNum = getGroupNum(groupOfGrid[e.second.first + dir[d][0]][e.second.second + dir[d][1]]);
        } else{
          if(curGroupNum != getGroupNum(groupOfGrid[e.second.first + dir[d][0]][e.second.second + dir[d][1]])){
            if(curGroupNum < getGroupNum(groupOfGrid[e.second.first + dir[d][0]][e.second.second + dir[d][1]])){
              prevSum -= xorValOfGroup[getGroupNum(groupOfGrid[e.second.first + dir[d][0]][e.second.second + dir[d][1]])];
              prevSum -= xorValOfGroup[curGroupNum];
              xorValOfGroup[curGroupNum] ^= xorValOfGroup[getGroupNum(groupOfGrid[e.second.first + dir[d][0]][e.second.second + dir[d][1]])];
              prevSum += xorValOfGroup[curGroupNum];
              groupOf[getGroupNum(groupOfGrid[e.second.first + dir[d][0]][e.second.second + dir[d][1]])] = curGroupNum;
            } else {
              prevSum -= xorValOfGroup[curGroupNum];
              prevSum -= xorValOfGroup[getGroupNum(groupOfGrid[e.second.first + dir[d][0]][e.second.second + dir[d][1]])];
              xorValOfGroup[getGroupNum(groupOfGrid[e.second.first + dir[d][0]][e.second.second + dir[d][1]])] ^= xorValOfGroup[curGroupNum];
              prevSum += xorValOfGroup[getGroupNum(groupOfGrid[e.second.first + dir[d][0]][e.second.second + dir[d][1]])];
              groupOf[curGroupNum] = getGroupNum(groupOfGrid[e.second.first + dir[d][0]][e.second.second + dir[d][1]]);
              curGroupNum = getGroupNum(groupOfGrid[e.second.first + dir[d][0]][e.second.second + dir[d][1]]);
            }
          }
        }
      }
    }
    if(curGroupNum == -1){
      groupOfGrid[e.second.first][e.second.second] = groupOf.size();
      groupOf.push_back(groupOfGrid[e.second.first][e.second.second]);
      xorValOfGroup.push_back(-1 * e.first);
      prevSum += -1 * e.first;
    } else {
      groupOfGrid[e.second.first][e.second.second] = curGroupNum;
      prevSum -= xorValOfGroup[curGroupNum];
      xorValOfGroup[curGroupNum] ^= -1 * e.first;
      prevSum += xorValOfGroup[curGroupNum];
    }

    ans = max(ans, prevSum);
  }

  cout << ans;

  return 0;
}