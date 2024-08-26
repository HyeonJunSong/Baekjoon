#include <iostream>
#include <vector>

using namespace std;

vector<int> soldiers;

int N;
vector<vector<int>> memo;

int getAns(int idx, int lastIdx){

  if(idx == N) return 0;

  if(memo[idx + 1][lastIdx] == -1)
    memo[idx + 1][lastIdx] = getAns(idx + 1, lastIdx);
  int ans = memo[idx + 1][lastIdx];

  if(idx == lastIdx || soldiers[lastIdx] > soldiers[idx]){
    if(memo[idx + 1][idx] == -1)
      memo[idx + 1][idx] = getAns(idx + 1, idx);
    ans = max(ans, memo[idx + 1][idx] + 1);
  }

  return ans;
}

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  cin >> N;
  soldiers.assign(N, 0);
  for(int i = 0; i < N; i++)
    cin >> soldiers[i];
  
  memo.assign(N + 1, vector<int>(N, -1));
  int ans = 0;
  for(int i = 0; i < N; i++)
    ans = max(ans, getAns(i, i));
  cout << N - ans;

  return 0;
}