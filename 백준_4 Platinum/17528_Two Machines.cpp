#include <iostream>
#include <vector>

using namespace std;

int n;
vector<pair<int, int>> arr;
vector<vector<int>> memo;
int getAns(int idx, int timeLeft){

  if(idx == n) return 0;

  if(memo[idx + 1][timeLeft] == -1)
    memo[idx + 1][timeLeft] = getAns(idx + 1, timeLeft);

  if(timeLeft >= arr[idx].first){
    if(memo[idx + 1][timeLeft - arr[idx].first] == -1)
      memo[idx + 1][timeLeft - arr[idx].first] = getAns(idx + 1, timeLeft - arr[idx].first);
    
    return min(memo[idx + 1][timeLeft] + arr[idx].second, memo[idx + 1][timeLeft - arr[idx].first]);
  }

  return memo[idx + 1][timeLeft] + arr[idx].second;
}

int main(){

  cin >> n;
  arr.assign(n, {0, 0});
  for(int i = 0; i < n; i++)
    cin >> arr[i].first >> arr[i].second;
  memo = vector<vector<int>>(n + 1, vector<int>(62501, -1));
  
  int ans = 987654321;

  for(int i = 0; i <= 62500; i++)
    ans = min(ans, max(i, getAns(0, i)));
  
  cout << ans;

  return 0;
}