#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int M, N, K;
vector<vector<bool>> ifFull;

int dir[4][2] = {
  {-1, 0},
  { 0, 1},
  { 0,-1},
  { 1, 0},
};

int numOfSpaces(int i, int j){

  if(ifFull[i][j])
    return 0;
  ifFull[i][j] = true;

  int cnt = 1;
  for(int d = 0; d < 4; d++){
    if(0 <= i + dir[d][0] && i + dir[d][0] < M
    && 0 <= j + dir[d][1] && j + dir[d][1] < N
    && !ifFull[i + dir[d][0]][j + dir[d][1]] ){
      cnt += numOfSpaces(i + dir[d][0], j + dir[d][1]);
    }
  }

  return cnt;
}

int main(){
  cin >> M >> N >> K;

  ifFull = vector<vector<bool>>(M, vector<bool>(N, false));

  for(int i = 0; i < K; i++){
    int x1, y1, x2, y2;
    cin >> x1 >> y1 >> x2 >> y2;

    for(int i = y1; i < y2; i++)
      for(int j = x1; j < x2; j++)
        ifFull[i][j] = true;
  }

  vector<int> ans;
  for(int i = 0; i < M; i++){
    for(int j = 0; j < N; j++){
      if(ifFull[i][j]) continue;
      ans.push_back(numOfSpaces(i, j));
    }
  }

  cout << ans.size() << "\n";
  sort(ans.begin(), ans.end());
  for(auto iter: ans)
    cout << iter << " ";

  return 0; 
}