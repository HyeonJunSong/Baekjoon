////231104
//25m 5s

#include <iostream>
#include <vector>

using namespace std;

int N, M, T;
vector<vector<pair<int, int>>> map;

int dir[3][2] = {
  {1, 0},
  {0, 1},
  {1, 1}
};

vector<vector<vector<int>>> memo;

#define NINF -987654321

int getMaxWorks(int I, int J, int TLeft){

  if(I == N - 1 && J == M - 1)
    return 0;
  if(TLeft == 0)
    return NINF;

  int maxWorks = NINF;

  //하고 넘기기
  for(int d = 0; d < 3; d++){
    if(I + dir[d][0] < N && J + dir[d][1] < M
      && TLeft - map[I + dir[d][0]][J + dir[d][1]].second - 1 >= 0){
      if(memo[I + dir[d][0]][J + dir[d][1]][TLeft - map[I + dir[d][0]][J + dir[d][1]].second - 1] == -1)
        memo[I + dir[d][0]][J + dir[d][1]][TLeft - map[I + dir[d][0]][J + dir[d][1]].second - 1] = getMaxWorks(I + dir[d][0], J + dir[d][1], TLeft - map[I + dir[d][0]][J + dir[d][1]].second - 1);
      if(maxWorks < memo[I + dir[d][0]][J + dir[d][1]][TLeft - map[I + dir[d][0]][J + dir[d][1]].second - 1] + map[I + dir[d][0]][J + dir[d][1]].first)
        maxWorks = memo[I + dir[d][0]][J + dir[d][1]][TLeft - map[I + dir[d][0]][J + dir[d][1]].second - 1] + map[I + dir[d][0]][J + dir[d][1]].first;
    }
  }
  
  //안하고 넘기기
  for(int d = 0; d < 3; d++){
    if(I + dir[d][0] < N && J + dir[d][1] < M){
      if(memo[I + dir[d][0]][J + dir[d][1]][TLeft - 1] == -1)
        memo[I + dir[d][0]][J + dir[d][1]][TLeft - 1] = getMaxWorks(I + dir[d][0], J + dir[d][1], TLeft - 1);
      if(maxWorks < memo[I + dir[d][0]][J + dir[d][1]][TLeft - 1])
        maxWorks = memo[I + dir[d][0]][J + dir[d][1]][TLeft - 1];
    }
  }

  return maxWorks;
}

int main(){

  cin >> N >> M >> T;
  map = vector<vector<pair<int, int>>>(N, vector<pair<int, int>>(M));
  for(int i = 0; i < N; i++)
    for(int j = 0; j < M; j++)
      cin >> map[i][j].first;
  for(int i = 0; i < N; i++)
    for(int j = 0; j < M; j++)
      cin >> map[i][j].second;
  
  memo = vector<vector<vector<int>>>(N, vector<vector<int>>(M, vector<int>(T + 1, -1)));

  cout << getMaxWorks(0, 0, T);
  

  return 0;
}