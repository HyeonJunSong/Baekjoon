#include <vector>
#include <iostream>
#include <queue>

using namespace std;

int dir[4][2] = {
  {-1,  0},
  { 1,  0},
  { 0, -1},
  { 0,  1}
};

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  int n, m;
  cin >> n >> m;

  vector<vector<int>> board(n, vector<int>(m, 0));
  for(int i = 0; i < n; i++)
    for(int j = 0; j < m; j++)
      cin >> board[i][j];

  pair<int, int> end = {-1, -1};  
  for(int i = 0; i < n; i++){
    for(int j = 0; j < m; j++){
      if(board[i][j] == 2){
        end = {i, j};
        break;
      }
    }
    if(end.first != -1) break;
  }

  vector<vector<int>> ans(n, vector<int>(m, 987654321));
  for(int i = 0; i < n; i++)
    for(int j = 0; j < m; j++)
      if(board[i][j] == 0)
        ans[i][j] = 0;

  queue<pair<int, pair<int, int>>> Q;
  Q.push({0, end});
  ans[end.first][end.second] = 0;

  while(!Q.empty()){
    pair<int, pair<int, int>> cur = Q.front();
    Q.pop();

    for(int d = 0; d < 4; d++){
      if(0 <= cur.second.first + dir[d][0] && cur.second.first + dir[d][0] < n
      && 0 <= cur.second.second + dir[d][1] && cur.second.second + dir[d][1] < m
      && ans[cur.second.first + dir[d][0]][cur.second.second + dir[d][1]] > cur.first + 1){
        Q.push({cur.first + 1, {cur.second.first + dir[d][0], cur.second.second + dir[d][1]}});
        ans[cur.second.first + dir[d][0]][cur.second.second + dir[d][1]] = cur.first + 1;
      }
    }
  }

  for(int i = 0; i < n; i++)
    for(int j = 0; j < m; j++)
      if(ans[i][j] == 987654321)
        ans[i][j] = -1;

  for(int i = 0; i < n; i++){
    for(int j = 0; j < m; j++)
      cout << ans[i][j] << " ";
    cout << "\n";
  }

  return 0;
}