#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int main(){

  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int N, M, K, t;
  cin >> N >> M >> K >> t;

  vector<pair<int, int>> gom(M);
  vector<pair<int, int>> gum(K);
  
  for(int i = 0; i < M; i++){
    cin >> gom[i].first >> gom[i].second;
    gom[i].first--; gom[i].second--;
  }
  for(int i = 0; i < K; i++){
    cin >> gum[i].first >> gum[i].second;
    gum[i].first--; gum[i].second--;
  }
  
  vector<vector<vector<bool>>> ifContaminated(N, vector<vector<bool>>(N, vector<bool>(2, false)));

  int dir[8][2] = {
    {-1, -2},
    { 1, -2},
    {-1,  2},
    { 1,  2},
    {-2, -1},
    { 2, -1},
    {-2,  1},
    { 2,  1},
  };

  queue<pair<pair<int, int>, int>> Q;
  for(auto e: gom)
    Q.push({e, 0});
  
  while(!Q.empty()){
    pair<pair<int, int>, int> curNode = Q.front();
    Q.pop();

    if(ifContaminated[curNode.first.first][curNode.first.second][curNode.second % 2]) continue;
    if(curNode.second == t){
      ifContaminated[curNode.first.first][curNode.first.second][curNode.second % 2] = true;
      continue;
    }
    
    bool ifSurvived = false;
    for(int d = 0; d < 8; d++){
      if(0 <= curNode.first.first + dir[d][0] && curNode.first.first + dir[d][0] < N
      && 0 <= curNode.first.second + dir[d][1] && curNode.first.second + dir[d][1] < N){
      if(!ifContaminated[curNode.first.first + dir[d][0]][curNode.first.second + dir[d][1]][(curNode.second + 1) % 2])
        ifSurvived = true;
        Q.push({{curNode.first.first + dir[d][0], curNode.first.second + dir[d][1]}, curNode.second + 1});
      }
    }
    if(ifSurvived)
      ifContaminated[curNode.first.first][curNode.first.second][curNode.second % 2] = true;
  }

  bool ans = false;
  for(auto e: gum){
    if(ifContaminated[e.first][e.second][t % 2]){
      ans = true;
      break;
    }
  }

  if(ans)
    cout << "YES";
  else
    cout << "NO";

  return 0;
}