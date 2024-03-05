#include <iostream>
#include <vector>

using namespace std;

#define INF 987654321

int N, M, L, G;
vector<vector<int>> ver = vector<vector<int>>(100, vector<int>(100));
vector<vector<int>> hor = vector<vector<int>>(100, vector<int>(100));

vector<vector<vector<vector<int>>>> memo(100, vector<vector<vector<int>>>(100, vector<vector<int>>(201, vector<int>(2))));

//0 : 오른쪽, 1 : 아래
int minGasUsage(int m, int n, int turns, int l){

  if(m == M - 1 || n == N - 1){
    if(turns == 0)
      return INF;
  
    int ans = 0;
    if(m == M - 1){
      for(int i = n; i < N - 1; i++)
        ans += hor[m][i];
    } else if(n == N - 1){
      for(int i = m; i < M - 1; i++)
        ans += ver[i][n];
    }
    return ans;
  }

  if(turns == 0) return INF;

  int ans = INF;
  if(l == 0){
    if(memo[m + 1][n][turns - 1][1] == -1)
      memo[m + 1][n][turns - 1][1] = minGasUsage(m + 1, n, turns - 1, 1);
    if(memo[m][n + 1][turns][0] == -1)
      memo[m][n + 1][turns][0] = minGasUsage(m, n + 1, turns, 0);

    ans = min(ans, memo[m + 1][n][turns - 1][1] + ver[m][n]);
    ans = min(ans, memo[m][n + 1][turns][0] + hor[m][n]);
  } else if(l == 1) {
    if(memo[m + 1][n][turns][1] == -1)
      memo[m + 1][n][turns][1] = minGasUsage(m + 1, n, turns, 1);
    if(memo[m][n + 1][turns - 1][0] == -1)
      memo[m][n + 1][turns - 1][0] = minGasUsage(m, n + 1, turns - 1, 0);

    ans = min(ans, memo[m + 1][n][turns][1] + ver[m][n]);
    ans = min(ans, memo[m][n + 1][turns - 1][0] + hor[m][n]);
  } else {
    if(memo[m + 1][n][turns][1] == -1)
      memo[m + 1][n][turns][1] = minGasUsage(m + 1, n, turns, 1);
    if(memo[m][n + 1][turns][0] == -1)
      memo[m][n + 1][turns][0] = minGasUsage(m, n + 1, turns, 0);

      ans = min(ans, memo[m + 1][n][turns][1] + ver[m][n]);
      ans = min(ans, memo[m][n + 1][turns][0] + hor[m][n]);
  }

  return ans;
}


void testCase(){

  cin >> M >> N >> L >> G;
  for(int i = 0; i < M; i++)
    for(int j = 0; j < N - 1; j++)
      cin >> hor[i][j];
  for(int i = 0; i < M - 1; i++)
    for(int j = 0; j < N; j++)
      cin >> ver[i][j];
  
  for(int i = 0; i < M; i++)
    for(int j = 0; j < N; j++)
      for(int k = 0; k <= (min(N, M)) * 2; k++)
        for(int l = 0; l < 2; l++)
          memo[i][j][k][l] = -1;

  int st = 1;
  int ed = (min(N, M)) * 2;

  while(st <= ed){
    int mid = (st + ed) / 2;

    if(minGasUsage(0, 0, mid, -1) > G)
      st = mid + 1;
    else
      ed = mid - 1;
  }

  if(st == (min(N, M)) * 2 + 1)
    cout << -1 << "\n";
  else
    cout << L * (M + N - 2) + st << "\n";

}

int main(){

  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  int T;
  cin >> T;
  for(int t = 0; t < T; t++)
    testCase();

  return 0;
}