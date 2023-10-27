////231026
//22m 26s

#include <iostream>
#include <vector>
#include <string>
#include <cmath>

using namespace std;

int R, C, K;
vector<string> map;

int cnt = 0;

int dir[4][2] = {
  {-1,  0},
  { 0,  1},
  { 1,  0},
  { 0, -1},
};

void DFS(int i = R - 1, int j = 0, int visited = (1 << C * (R - 1)), int pathCnt = 1){
  if(i == 0 && j == C - 1){
    if(pathCnt == K) cnt++;
    return;
  }
  if(pathCnt >= K) return;

  for(int d = 0; d < 4; d++){
    if(0 <= i + dir[d][0] && i + dir[d][0] < R
    && 0 <= j + dir[d][1] && j + dir[d][1] < C
    && ((visited & (1 << (i + dir[d][0]) * C + j + dir[d][1])) == 0)
    && map[i + dir[d][0]][j + dir[d][1]] != 'T'){
      DFS(i + dir[d][0], j + dir[d][1], visited | (1 << (i + dir[d][0]) * C + j + dir[d][1]), pathCnt + 1);
    }
  }
}

int main(){

  cin >> R >> C >> K;
  map = vector<string>(R);

  for(int i = 0; i < R; i++)
    cin >> map[i];

  DFS();

  cout << cnt;

  return 0;
}