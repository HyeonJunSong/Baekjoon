#include <iostream>
#include <vector>

using namespace std;

int N;
vector<vector<vector<int>>> memo;
vector<int> FJ;

int getAns(int idx, int cur, int K){

  if(idx == N)
    return 0;

  int ans = 0;

  for(int i = 0; i < 3; i++){
    if(cur == i){
      if(memo[idx + 1][i][K] == -1)
        memo[idx + 1][i][K] = getAns(idx + 1, i, K);
      
      if((FJ[idx] + 1) % 3 == i)
        ans = max(ans, memo[idx + 1][i][K] + 1);
      else
        ans = max(ans, memo[idx + 1][i][K]);

    } else if(K > 0){
      if(memo[idx + 1][i][K - 1] == -1)
        memo[idx + 1][i][K - 1] = getAns(idx + 1, i, K - 1);

      if((FJ[idx] + 1) % 3 == i)
        ans = max(ans, memo[idx + 1][i][K - 1] + 1);
      else
        ans = max(ans, memo[idx + 1][i][K - 1]);
    }
  }

  return ans;
}

int main(){

  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int K;
  cin >> N >> K;
  FJ.assign(N, 0);
  for(int i = 0; i < N; i++){
    char inp;
    cin >> inp;
    switch(inp){
      case 'H':
        FJ[i] = 0;
      break;
      case 'P':
        FJ[i] = 1;
      break;
      case 'S':
        FJ[i] = 2;
      break;
    }
  }
  memo = vector<vector<vector<int>>>(N + 1, vector<vector<int>>(3, vector<int>(K + 1, -1)));

  int ans = 0;
  for(int i = 0; i < 3; i++)
    ans = max(ans, getAns(0, i, K));
  cout << ans;

  return 0;
}