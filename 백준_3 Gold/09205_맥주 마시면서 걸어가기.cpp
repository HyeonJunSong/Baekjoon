#include <iostream>
#include <vector>

using namespace std;

void testCase(){
  int n;
  cin >> n;
  n += 2;
  vector<pair<int, int>> coords(n);
  for(int i = 0; i < n; i++)
    cin >> coords[i].first >> coords[i].second;
  
  vector<vector<int>> graph(n);
  for(int i = 0; i < n - 1; i++){
    for(int j = i; j < n; j++){
      if(abs(coords[i].first - coords[j].first) + abs(coords[i].second - coords[j].second) > 1000) continue;
      graph[i].push_back(j);
      graph[j].push_back(i);
    }
  }

  vector<bool> visited(n, false);
  vector<int> stack;
  stack.push_back(0);

  bool ifPossible = false;

  while(!stack.empty()){
    int cur = stack.back();
    stack.pop_back();

    if(visited[cur]) continue;
    visited[cur] = true;

    if(cur == n - 1){
      ifPossible = true;
      break;
    }

    for(auto e: graph[cur]){
      if(visited[e]) continue;
      stack.push_back(e);      
    }
  }

  if(ifPossible) cout << "happy\n";
  else cout << "sad\n";
  
}

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  int t;
  cin >> t;
  for(int i = 0; i < t; i++)
    testCase();

  return 0;
}