#include <iostream>
#include <vector>

using namespace std;

#define MAX 987654321

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  int P;
  cin >> P;

  int B = 0, M = 0;

  vector<pair<int, int>> dataSets(P);
  for(int i = 0; i < P; i++){
    cin >> dataSets[i].first >> dataSets[i].second;
    if(B < dataSets[i].first)
      B = dataSets[i].first;
    if(M < dataSets[i].second)
      M = dataSets[i].second;
  }

  vector<vector<int>> dp(B + 1, vector<int>(M + 1, MAX));
  
  for(int i = 1; i < M + 1; i++)
    dp[1][i] = i;
  
  for(int i = 2; i < B + 1; i++){
    dp[i][1] = 1;
    dp[i][2] = 2;
    for(int j = 3; j < M + 1; j++){
      for(int k = 1; k < j - 1; k++){
        if(dp[i][j] < max(dp[i - 1][k], dp[i][j - 1 - k]) + 1) break;
        dp[i][j] = max(dp[i - 1][k], dp[i][j - 1 - k]) + 1;
      }
    }
  }

  for(int i = 0; i < P; i++)
    cout << dp[dataSets[i].first][dataSets[i].second] << "\n";

}