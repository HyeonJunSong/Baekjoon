#include <iostream>
#include <vector>
#include <map>
#include <string>

using namespace std;

vector<vector<pair<int, char>>> graph;
vector<vector<bool>> ifConnected;

vector<vector<int>> visited;

int getAns(int idx0, int idx1, int len){

  if(visited[idx0][idx1] < len) return 987654321;
  visited[idx0][idx1] = len;

  if(idx0 == idx1)
    return 0;
  if(ifConnected[idx0][idx1])
    return 1;
  
  int ans = 987654321;
  for(auto e1: graph[idx0]){
    for(auto e2: graph[idx1]){
      if(e1.second == e2.second){
        ans = min(ans, getAns(e1.first, e2.first, len + 1));
      }
    }
  }

  if(ans == 987654321)
    return ans;
  return 2 + ans;
}

int main(){

  int N, M;
  cin >> N >> M;


  graph = vector<vector<pair<int, char>>>(N);
  ifConnected = vector<vector<bool>>(N, vector<bool>(N, false));
  for(int i = 0; i < M; i++){
    int st, ed;
    char w;
    cin >> st >> ed >> w;

    graph[st].emplace_back(ed, w);
    graph[ed].emplace_back(st, w);

    ifConnected[st][ed] = true;
    ifConnected[ed][st] = true;
  }

  visited = vector<vector<int>>(N, vector<int>(N, 987654321));

  int ans = getAns(0, 1, 0);
  if(ans == 987654321)
    cout << -1;
  else
    cout << ans;

  return 0;
}