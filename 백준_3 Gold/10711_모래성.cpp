////230818
//28m 47s

#include <iostream>
#include <set>
#include <string>
#include <vector>

using namespace std;

int H, W;
vector<string> beach;

int dir[8][2] = {
  {-1,  0},
  {-1,  1},
  { 0,  1},
  { 1,  1},
  { 1,  0},
  { 1, -1},
  { 0, -1},
  {-1, -1},
};

bool ifDestroied(int i, int j){
  int totEmptyCnt = 0;
  for(int d = 0;  d < 8; d++){
    if(beach[i + dir[d][0]][j + dir[d][1]] == '.')
      totEmptyCnt++;
  }

  if(totEmptyCnt >= beach[i][j] - '0')
    return true;
  else
    return false;
}

set<pair<int, int>> sandCastles;
//한 파도 시뮬레이션. 모래성의 변화가 없으면 false 리턴
bool wave(){

  //이번 파도에 없어지는 모래성들 없애기
  for(auto iter = sandCastles.begin(); iter != sandCastles.end(); iter++){
    beach[iter->first][iter->second] = '.';
  }


  //이번 파도에 없어지는 모래성 주변에 없어질 모래성들 없나 찾기
  set<pair<int, int>> newSandCastles;
    for(auto iter = sandCastles.begin(); iter != sandCastles.end(); iter++){
      for(int d = 0;  d < 8; d++){
      if(beach[iter->first + dir[d][0]][iter->second + dir[d][1]] != '.'
      && ifDestroied(iter->first + dir[d][0], iter->second + dir[d][1]))
        newSandCastles.insert({iter->first + dir[d][0], iter->second + dir[d][1]});
    }
  }

  if(newSandCastles.size() != 0){
    sandCastles = newSandCastles;
    return true;
  }

  return false;
}

int main(){
  cin >> H >> W;
  beach = vector<string>(H);
  for(int i = 0; i < H; i++)
    cin >> beach[i];
  
  //전체 돌면서 없어질 모래성 찾기
  for(int i = 1; i < H - 1; i++){
    for(int j = 1; j < W - 1; j++){
      if(ifDestroied(i, j))
        sandCastles.insert({i, j});
    }
  }

  if(sandCastles.size() == 0){
    cout << 0;
    return 0;
  }

  //파도 시뮬레이션
  int waveCnt = 0;
  do{
    waveCnt++;
  }while(wave());
  
  cout << waveCnt;

  return 0;
}