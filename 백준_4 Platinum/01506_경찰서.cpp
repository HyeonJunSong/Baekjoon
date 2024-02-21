#include <iostream>
#include <vector>
#include <string>

using namespace std;

int groupId = 0;
vector<vector<int>> graph;
vector<int> groupIdOf;
vector<bool> visited;
#define MAX 987654321

int DFS(int curNode, vector<int>& stack, vector<int>& stackIdx) {

    visited[curNode] = true;
    stack.push_back(curNode);
    stackIdx[curNode] = stack.size();

    int minParentIdx = MAX;

    for (auto e : graph[curNode]) {
        if (stackIdx[e] != -1 && stackIdx[e] < minParentIdx) {
            minParentIdx = stackIdx[e];
            continue;
        }

        if (visited[e]) continue;

        minParentIdx = min(DFS(e, stack, stackIdx), minParentIdx);
    }

    if (minParentIdx == stackIdx[curNode] || minParentIdx == MAX) {
        while (stack.size() > 0 && stack.back() != curNode) {
            groupIdOf[stack.back()] = groupId;
            stackIdx[stack.back()] = -1;
            stack.pop_back();
        }
        groupIdOf[stack.back()] = groupId;
        stackIdx[stack.back()] = -1;
        stack.pop_back();

        groupId += 1;

        return MAX;
    }

    return minParentIdx;
}

int main(){

  int N;
  cin >> N;
  vector<int> cost(N);
  for(int i = 0; i < N; i++)
    cin >> cost[i];
  vector<string> city(N);
  for(int i = 0; i < N; i++)
    cin >> city[i];
  
  graph = vector<vector<int>>(N);
  for(int i = 0; i < N; i++){
    for(int j = 0; j < N; j++){
      if(city[i][j] == '1')
        graph[i].push_back(j);
    }
  }
  groupIdOf = vector<int>(N);
  visited = vector<bool>(N, false);
  vector<int> stack;
  vector<int> stackIdx(N, -1);

  for (int v = 0; v < N; v++) {
      if (visited[v]) continue;
      DFS(v, stack, stackIdx);
  }
  
  int ans = 0;
  for(int i = 0; i < groupId; i++){
    int curMinCost = MAX;
    for(int j = 0; j < N; j++){
      if(groupIdOf[j] == i)
        curMinCost = min(curMinCost, cost[j]);
    }
    ans += curMinCost;
  }
  cout << ans;



  return 0;
}