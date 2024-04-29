#include <iostream>
#include <vector>

using namespace std;

int N, M;
vector<vector<vector<int>>> graph;
vector<int> ifPossible;

bool findIfPossible(int idx, vector<bool>& visited){

  if(ifPossible[idx] == 1) return true;

  if(graph[idx].size() == 0){
    ifPossible[idx] = 0;
    return false;
  }

  visited[idx] = true;

  for(auto e: graph[idx]){
    bool curIfPossible = true;
    for(auto e2: e){
      if(visited[e2]){
        curIfPossible = false;
        break;
      };
      if(!findIfPossible(e2, visited)){
        curIfPossible = false;
        break;
      }
    }

    if(curIfPossible){
      visited[idx] = false;

      ifPossible[idx] = 1;
      return true;
    }
  }

  visited[idx] = false;

  ifPossible[idx] = 0;
  return false;
}

int main(){

  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  cin >> N >> M;

  graph = vector<vector<vector<int>>>(N + 1);
  for(int i = 0; i < M; i++){
    int k;
    cin >> k;
    vector<int> recipe(k);
    for(int j = 0; j < k; j++)
      cin >> recipe[j];
    int r;
    cin >> r;
    
    graph[r].push_back(recipe);
  }

  ifPossible = vector<int>(N + 1, -1);
  int L;
  cin >> L;
  for(int i = 0; i < L; i++){
    int cur;
    cin >> cur;
    ifPossible[cur] = 1;
  }

  vector<bool> visited(N + 1, false);

  vector<int> ans;
  for(int i = 1; i <= N; i++){
    if(findIfPossible(i, visited))
      ans.push_back(i);
  }

  cout << ans.size() << "\n";
  for(auto e : ans)
    cout << e << " ";

  return 0;
}