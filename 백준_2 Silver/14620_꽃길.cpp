#include <iostream>
#include <vector>

using namespace std;

int main(){

  int N;
  cin >> N;
  vector<vector<int>> garden(N, vector<int>(N));
  for(int i = 0; i < N; i++)
    for(int j = 0; j < N; j++)
      cin >> garden[i][j];
  
  int ans = 987654321;

  vector<pair<int, int>> possibleCoords;
  for(int i = 1; i < N - 1; i++)
    for(int j = 1; j < N - 1; j++)
      possibleCoords.push_back({i, j});

  vector<vector<bool>> visited(N, vector<bool>(N, false));
  int dir[4][2] = {
    {-1, 0},
    { 1, 0},
    {0, -1},
    {0,  1},
  };

  int curAns = 0;
  for(auto c1 : possibleCoords){

    for(int d = 0; d < 4; d++){
      visited[c1.first + dir[d][0]][c1.second + dir[d][1]] = true;
      curAns += garden[c1.first + dir[d][0]][c1.second + dir[d][1]];
    }
    visited[c1.first][c1.second] = true;
    curAns += garden[c1.first][c1.second];
    

    for(auto c2 : possibleCoords){
      bool ifPossible = true;
      for(int d = 0; d < 4; d++){
        if(!visited[c2.first + dir[d][0]][c2.second + dir[d][1]]) continue;
        ifPossible = false;
        break;
      }
      if(!ifPossible) continue;;

      for(int d = 0; d < 4; d++){
        visited[c2.first + dir[d][0]][c2.second + dir[d][1]] = true;
        curAns += garden[c2.first + dir[d][0]][c2.second + dir[d][1]];
      }
      visited[c2.first][c2.second] = true;
      curAns += garden[c2.first][c2.second];

  
      for(auto c3 : possibleCoords){
        ifPossible = true;
        for(int d = 0; d < 4; d++){
          if(!visited[c3.first + dir[d][0]][c3.second + dir[d][1]]) continue;
          ifPossible = false;
          break;
        }
        if(visited[c3.first][c3.second]) ifPossible = false;
        if(!ifPossible) continue;;

        for(int d = 0; d < 4; d++)
          curAns += garden[c3.first + dir[d][0]][c3.second + dir[d][1]];
        curAns += garden[c3.first][c3.second];

        ans = min(ans, curAns);

        for(int d = 0; d < 4; d++)
          curAns -= garden[c3.first + dir[d][0]][c3.second + dir[d][1]];
        curAns -= garden[c3.first][c3.second];
      }


      for(int d = 0; d < 4; d++){
        visited[c2.first + dir[d][0]][c2.second + dir[d][1]] = false;
        curAns -= garden[c2.first + dir[d][0]][c2.second + dir[d][1]];
      }
      visited[c2.first][c2.second] = false;
      curAns -= garden[c2.first][c2.second];
    }

    for(int d = 0; d < 4; d++){
      visited[c1.first + dir[d][0]][c1.second + dir[d][1]] = false;
      curAns -= garden[c1.first + dir[d][0]][c1.second + dir[d][1]];
    }
    visited[c1.first][c1.second] = false;
    curAns -= garden[c1.first][c1.second];

  }

  cout << ans;

  return 0;
}