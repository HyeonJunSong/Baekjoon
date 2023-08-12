////230812
//이해 및 설계 : 2m 10s
//입력 : 2m 41s
//구현 : 27m 3s

//tot : 31m 54s

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int N, M;
vector<vector<int>> warehouse;

int dir[4][2] = {
  {-1,  0},
  { 0,  1},
  { 1,  0},
  { 0, -1},
};

void oneTimeStamp(){
  ////치즈 안쪽공간 2로 체크
  //바깥 공간 체크
  vector<vector<bool>> ifOutside(N, vector<bool>(M, false));
  vector<vector<bool>> visted(N, vector<bool>(M, false));

  queue<pair<int, int>> Q;
  Q.push({0, 0});

  while(!Q.empty()){
    pair<int, int> curNode = Q.front();
    Q.pop();
    ifOutside[curNode.first][curNode.second] = true;
    if(visted[curNode.first][curNode.second]) continue;
    visted[curNode.first][curNode.second] = true;

    for(int d = 0; d < 4; d++){
      if(0 <= curNode.first + dir[d][0] && curNode.first + dir[d][0] < N
      && 0 <= curNode.second + dir[d][1] && curNode.second + dir[d][1] < M
      && warehouse[curNode.first + dir[d][0]][curNode.second + dir[d][1]] == 0)
        Q.push({curNode.first + dir[d][0], curNode.second + dir[d][1]});
    }
  }

  //치즈 안쪽공간 2로 체크
  for(int i = 0; i < N; i++)
    for(int j = 0; j < M; j++)
      if(!ifOutside[i][j] && warehouse[i][j] == 0)
        warehouse[i][j] = 2;
      
  
  ////녹일치즈 3으로 체크
  visted = vector<vector<bool>>(N, vector<bool>(M, false));
  vector<vector<bool>>ifMelted(N, vector<bool>(M, false));

  for(int i = 0; i < N; i++){
    for(int j = 0; j < M; j++){
      if(visted[i][j] || warehouse[i][j] == 0) continue;

      Q.push({i, j});
      while(!Q.empty()){
        pair<int, int> curNode = Q.front();
        Q.pop();

        if(visted[curNode.first][curNode.second]) continue;
        visted[curNode.first][curNode.second] = true;

        int outSideCnt = 0;
        for(int d = 0; d < 4; d++){
          if(0 <= curNode.first + dir[d][0] && curNode.first + dir[d][0] < N
          && 0 <= curNode.second + dir[d][1] && curNode.second + dir[d][1] < M){
            if(warehouse[curNode.first + dir[d][0]][curNode.second + dir[d][1]] == 0)
              outSideCnt++;

            if(warehouse[curNode.first + dir[d][0]][curNode.second + dir[d][1]] == 1)
              Q.push({curNode.first + dir[d][0], curNode.second + dir[d][1]});
          }
        }
        if(outSideCnt >= 2)
          warehouse[curNode.first][curNode.second] = 3;
      }

    }
  }

  //3인치즈 다 녹이기 & 2인거 다시 0으로
  for(int i = 0; i < N; i++)
    for(int j = 0; j < M; j++)
      if(warehouse[i][j] == 3 || warehouse[i][j] == 2)
        warehouse[i][j] = 0;
  
}

bool ifEmpty(){
  //전부 다 0인지 체크해서 맞으면 리턴
  int cheeseCnt = 0;
  for(int i = 0; i < N; i++)
    for(int j = 0; j < M; j++)
      if(warehouse[i][j] == 1)
        cheeseCnt++;
  return cheeseCnt == 0;
}

int main(){
  cin >> N >> M;
  warehouse = vector<vector<int>>(N, vector<int>(M));
  for(int i = 0; i < N; i++)
    for(int j = 0; j < M; j++)
      cin >> warehouse[i][j];

  int timeStamps = 0;
  while(!ifEmpty()){
    oneTimeStamp();
    timeStamps++;
  }
  
  cout << timeStamps;

  return 0;
}