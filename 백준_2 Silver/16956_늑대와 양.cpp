#include <iostream>
#include <string>
#include <vector>

using namespace std;

int dir[4][2] = {
  {-1, 0},
  {1, 0},
  {0, 1},
  {0, -1}
};

int main(){

  int R, C;
  cin >> R >> C;
  vector<string> city(R);
  for(int i = 0; i < R; i++)
    cin >> city[i];
  
  vector<pair<int, int>> sheepLoc;
  for(int i = 0; i < R; i++){
    for(int j = 0; j < C; j++){
      if(city[i][j] == 'S')
        sheepLoc.push_back({i, j});
    }
  }

  for(auto e: sheepLoc){
    for(int d = 0; d < 4; d++){
      if(0 <= e.first + dir[d][0] && e.first + dir[d][0] < R
      && 0 <= e.second + dir[d][1] && e.second + dir[d][1] < C){
        if(city[e.first + dir[d][0]][e.second + dir[d][1]] == 'W'){
          cout << 0;
          exit(0);
        } else if(city[e.first + dir[d][0]][e.second + dir[d][1]] == 'S')
          continue;
        else
          city[e.first + dir[d][0]][e.second + dir[d][1]] = 'D';
      }
    }
  }

  cout << 1 << endl;
  for(auto e: city)
    cout << e << endl;


  return 0;
}