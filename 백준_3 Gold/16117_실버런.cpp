#include <iostream>
#include <vector>

using namespace std;

int N, M;
vector<vector<int>> board;
vector<vector<int>> memo;

int getAns(int I, int J){
  if(J == M) return 0;

  int ans = 0;
  if(I > 0){
    if(memo[I - 1][J + 1] == -1)
      memo[I - 1][J + 1] = getAns(I - 1, J + 1);
    ans = max(ans, memo[I - 1][J + 1]);
  }
  if(I < N - 1){
    if(memo[I + 1][J + 1] == -1)
      memo[I + 1][J + 1] = getAns(I + 1, J + 1);
    ans = max(ans, memo[I + 1][J + 1]);
  }
  if(J < M - 1){
    if(memo[I][J + 2] == -1)
      memo[I][J + 2] = getAns(I, J + 2);
    ans = max(ans, memo[I][J + 2] + board[I][J + 1]);    
  }

  return ans + board[I][J];
}

vector<vector<vector<int>>> memo2;

//status 0 : 위에서 내려온거, 1 : 밑에서 올라온거
int getAns2(int I, int J, int status){
  if(J == M) return 0;

  int ans = 0;

  if(status == 0){
    if(I < N - 1){
      if(memo2[I + 1][J + 1][0] == -1)
        memo2[I + 1][J + 1][0] = getAns2(I + 1, J + 1, 0);
      ans = max(ans, memo2[I + 1][J + 1][0]);
    }

    if(memo2[I][J + 1][1] == -1)
      memo2[I][J + 1][1] = getAns2(I, J + 1, 1);
    ans = max(ans, memo2[I][J + 1][1]);
  } else {
    if(I > 0){
      if(memo2[I - 1][J + 1][1] == -1)
        memo2[I - 1][J + 1][1] = getAns2(I - 1, J + 1, 1);
      ans = max(ans, memo2[I - 1][J + 1][1]);
    }
    if(memo2[I][J + 1][0] == -1)
      memo2[I][J + 1][0] = getAns2(I, J + 1, 0);
    ans = max(ans, memo2[I][J + 1][0]);
  }

  return ans + board[I][J];
}

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  cin >> N >> M;
  board.assign(N, vector<int>(M, 0));
  for(int i = 0; i < N; i++)
    for(int j = 0; j < M; j++)
      cin >> board[i][j];
  
  memo.assign(N, vector<int>(M + 1, -1));
  memo2.assign(N, vector<vector<int>>(M + 1, vector<int>(2, -1)));
  
  
  int ans = 0;
  for(int i = 0; i < N; i++){
    ans = max(ans, getAns(i, 0));
    ans = max(ans, getAns(i, 1) + board[i][0]);
  }
  for(int i = 0; i < N; i++){
    ans = max(ans, getAns2(i, 0, 0));
    ans = max(ans, getAns2(i, 0, 1));
  }
  
  cout << ans;

  return 0;
}