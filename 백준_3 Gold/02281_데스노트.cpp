#include <iostream>
#include <vector>
#include <climits>

using namespace std;

long long n, m;
vector<int> arr;

vector<vector<long long>> memo;
long long getAns(int idx, long long curSt){

  if(idx == n - 1){
    if(curSt + arr[idx] > m)
      return (m - curSt + 1) * (m - curSt + 1);
    else
    return 0;
  }

  long long ans = LLONG_MAX;
  if(curSt + arr[idx] <= m){
    if(memo[idx + 1][curSt + arr[idx] + 1] == -1)
      memo[idx + 1][curSt + arr[idx] + 1] = getAns(idx + 1, curSt + arr[idx] + 1);
    ans = min(ans, memo[idx + 1][curSt + arr[idx] + 1]);
  }
  if(idx > 0){
    if(memo[idx + 1][arr[idx] + 1] == -1)
      memo[idx + 1][arr[idx] + 1] = getAns(idx + 1, arr[idx] + 1);
    ans = min(ans, memo[idx + 1][arr[idx] + 1] + (m - curSt + 1) * (m - curSt + 1));
  }

  return ans;
}

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  cin >> n >> m;

  arr = vector<int>(n);
  for(int i = 0; i < n; i++)
    cin >> arr[i];
  
  memo = vector<vector<long long>>(n, vector<long long>(m + 2, -1));
  cout << getAns(0, 0);

  return 0;
}