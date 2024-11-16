#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int dir[4][2] = {
  {-1, 0},
  { 1, 0},
  { 0, -1},
  { 0, 1}
};

int main(){

  int N;
  cin >> N;

  vector<string> board(N);
  for(int i = 0; i < N; i++)
    cin >> board[i];
  
  vector<pair<int, int>> stack;
  vector<vector<bool>> visited(N, vector<bool>(N, false));

  vector<int> areas;
  for(int i = 0; i < N; i++){
    for(int j = 0; j < N; j++){
      if(visited[i][j]) continue;
      if(board[i][j] == '0') continue;

      int curAns = 0;
      stack.push_back({i, j});
      while(!stack.empty()){
        auto curNode = stack.back();
        stack.pop_back();

        if(visited[curNode.first][curNode.second]) continue;
        visited[curNode.first][curNode.second] = true;
        curAns++;

        for(int d = 0; d < 4; d++){
          if(0 <= curNode.first + dir[d][0] && curNode.first + dir[d][0] < N
          && 0 <= curNode.second + dir[d][1] && curNode.second + dir[d][1] < N
          && !visited[curNode.first + dir[d][0]][curNode.second + dir[d][1]]
          && board[curNode.first + dir[d][0]][curNode.second + dir[d][1]] == '1')
            stack.push_back({curNode.first + dir[d][0], curNode.second + dir[d][1]});
        }
      }
      areas.push_back(curAns);
    }
  }

  sort(areas.begin(), areas.end());
  cout << areas.size() << '\n';
  for(auto e: areas)
    cout << e << '\n';

  return 0;
}