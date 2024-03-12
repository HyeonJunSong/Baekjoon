#include <iostream>
#include <vector>
#include <queue>
#include <set>

using namespace std;

int main(){

  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  int N, K;
  cin >> N >> K;

  vector<int> oasis(N);
  set<int> visited;
  for(int i = 0; i < N; i++){
    cin >> oasis[i];
    visited.insert(oasis[i]);
  }
  
  priority_queue<pair<int, int>> PQ;

  for(auto e: oasis){
    if(visited.find(e - 1) == visited.end())
      PQ.push({-1, e - 1});

    if(visited.find(e + 1) == visited.end())
      PQ.push({-1, e + 1});
  }

  long long ans = 0;
  while(K > 0){
    pair<int, int> curNode = PQ.top();
    PQ.pop();

    if(visited.find(curNode.second) != visited.end()) continue;
    visited.insert(curNode.second);

    ans -= curNode.first;
    K--;

    if(visited.find(curNode.second - 1) == visited.end())
      PQ.push({curNode.first - 1, curNode.second - 1});

    if(visited.find(curNode.second + 1) == visited.end())
      PQ.push({curNode.first - 1, curNode.second + 1});
  }

  cout << ans;

  return 0;
}