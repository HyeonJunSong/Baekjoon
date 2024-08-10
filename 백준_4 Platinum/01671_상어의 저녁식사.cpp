#include <iostream>
#include <vector>

using namespace std;

class Shark{
public:
  int size;
  int speed;
  int intelligence;
  int idx;

  bool ifEatable(Shark b){
    if(size == b.size && speed == b.speed && intelligence == b.intelligence)
      return idx > b.idx;
    return size >= b.size && speed >= b.speed && intelligence >= b.intelligence;
  }
};

int N;
vector<Shark> sharks;
vector<vector<int>> graph;
vector<bool> visited;

vector<int> matched;
bool tryMatch(int sharkIdx){
  for(int i = 0; i < graph[sharkIdx].size(); i++){
    if(visited[graph[sharkIdx][i]]) continue;
    visited[graph[sharkIdx][i]] = true;

    if(matched[graph[sharkIdx][i]] == -1 || tryMatch(matched[graph[sharkIdx][i]])){
      matched[graph[sharkIdx][i]] = sharkIdx;
      return true;
    }
  }
  return false;
}

int main(){

  cin >> N;

  sharks.assign(N, {0, 0, 0, 0});
  for(int i = 0; i < N; i++){
    cin >> sharks[i].size >> sharks[i].speed >> sharks[i].intelligence;
    sharks[i].idx = i;
  }
  
  graph.assign(N, {});
  for(int i = 0; i < N; i++){
    for(int j = 0; j < N; j++){
      if(sharks[i].ifEatable(sharks[j]))
        graph[i].push_back(j);
    }
  }
  visited.assign(N, false);

  matched.assign(N, -1);

  int ans = 0;
  for(int i = 0; i < N; i++){
    for(int j = 0; j < N; j++) visited[j] = false;
    if(tryMatch(i)) ans++;
    for(int j = 0; j < N; j++) visited[j] = false;
    if(tryMatch(i)) ans++;
  }

  cout << N - ans;

  return 0;
}