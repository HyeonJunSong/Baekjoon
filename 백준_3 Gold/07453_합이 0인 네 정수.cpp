#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#define LL long long

LL findLoc(vector<pair<LL, LL>>& arr, LL num);

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int n;
  cin >> n;
  vector<vector<LL>> nums(n, vector<LL>(4));
  for(int i = 0; i < n; i++)
    for(int j = 0; j < 4; j++)
      cin >> nums[i][j];
  
  vector<LL> rightNums;
  vector<LL> leftNums;
  
  for(int i = 0; i < n; i++)
    for(int j = 0; j < n; j++){
      leftNums.push_back(nums[i][0] + nums[j][1]);
      rightNums.push_back(nums[i][2] + nums[j][3]);
    }

  sort(leftNums.begin(), leftNums.end());
  sort(rightNums.begin(), rightNums.end());

  vector<pair<LL, LL>> leftMergedNum;
  for(auto e : leftNums){
    if(leftMergedNum.size() > 0 && leftMergedNum.back().first == e)
      leftMergedNum.back().second += 1;
    else
      leftMergedNum.push_back({e, 1});
  }
  vector<pair<LL, LL>> rightMergedNum;
  for(auto e : rightNums){
    if(rightMergedNum.size() > 0 && rightMergedNum.back().first == e)
      rightMergedNum.back().second += 1;
    else
      rightMergedNum.push_back({e, 1});
  }
  
  LL ans = 0;
  for(auto e: leftMergedNum)
      ans += findLoc(rightMergedNum, -1 * e.first) * e.second;
  
  cout << ans;

  return 0;
}

LL findLoc(vector<pair<LL, LL>>& arr, LL num){
  int st = 0;
  int ed = arr.size() - 1;

  while(st <= ed){
    int mid = (st + ed) / 2;
    if(arr[mid].first < num)
      st = mid + 1;
    else if (arr[mid].first > num)
      ed = mid - 1;
    else
      return arr[mid].second;
  }

  return 0;
}