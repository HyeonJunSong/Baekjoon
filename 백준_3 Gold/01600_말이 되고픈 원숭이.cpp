#include <queue>
#include <iostream>
#include <vector>

using namespace std;

int dirs_adj[4][2] = {
  {-1,  0},
  { 0, -1},
  { 1,  0},
  { 0,  1}
};

int dirs_horse[8][2] = {
  {-1, -2},
  {-2, -1},
  {-2, +1},
  {-1, +2},
  {+1, -2},
  {+2, -1},
  {+2, +1},
  {+1, +2}
};

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  int K, W, H;
  cin >> K >> W >> H;

  vector<vector<int>> board(H, vector<int>(W, 0));
  for(int i = 0; i < H; i++)
    for(int j = 0; j < W; j++)
      cin >> board[i][j];
  
  vector<vector<vector<bool>>> visited(H, vector<vector<bool>>(W, vector<bool>(K + 1, false)));

  queue<vector<int>> Q;
  Q.push({0, 0, 0, 0});
  visited[0][0][0] = true;

  while(!Q.empty()){
    int cnt = Q.front()[0], curI = Q.front()[1], curJ = Q.front()[2], curK = Q.front()[3];
    Q.pop();

    if(curI == H - 1 && curJ == W - 1){
      cout << cnt;
      return 0;
    }
  
    for(int d = 0; d < 4; d++){
      int nxtI = curI + dirs_adj[d][0], nxtJ = curJ + dirs_adj[d][1];
      if(0 > nxtI || nxtI >= H || 0 > nxtJ || nxtJ >= W) continue;
      
      if(visited[nxtI][nxtJ][curK]) continue;
      visited[nxtI][nxtJ][curK] = true;

      if(board[nxtI][nxtJ] == 1) continue;
      Q.push({cnt + 1, nxtI, nxtJ, curK});
    }
    
    if(curK == K) continue;
    for(int d = 0; d < 8; d++){
      int nxtI = curI + dirs_horse[d][0], nxtJ = curJ + dirs_horse[d][1];
      if(0 > nxtI || nxtI >= H || 0 > nxtJ || nxtJ >= W) continue;
      
      if(visited[nxtI][nxtJ][curK + 1]) continue;
      visited[nxtI][nxtJ][curK + 1] = true;

      if(board[nxtI][nxtJ] == 1) continue;
      Q.push({cnt + 1, nxtI, nxtJ, curK + 1});
    }
  }

  cout << -1;

  return 0;
}
