#include <iostream>
#include <vector>

using namespace std;

int N, M, L;
vector<vector<vector<int>>> graph;

vector<vector<int>> groups;

int getDiameter(int curInd, int parentInd);
int getMaxDepthOf(int curInd, int parentInd);

int main(){
  cin >> N >> M >> L;
  graph = vector<vector<vector<int>>>(N);
  for(int i = 0; i < M; i++){
    int A, B, T;
    cin >> A >> B >> T;
    graph[A].push_back({B, T, -1});
    graph[B].push_back({A, T, -1});
  }

  vector<bool> visited(N, false);
  for(int i = 0; i < N; i++){
    if(visited[i]) continue;

    vector<vector<int>> stack(1, {i, -1});
    groups.push_back(vector<int>());

    while(stack.size() > 0){
      vector<int> curNode = stack.back();
      stack.pop_back();
      visited[curNode[0]] = true;
      groups.back().push_back(curNode[0]);

      for(auto e: graph[curNode[0]]){
        if(e[0] == curNode[1]) continue;
        stack.push_back({e[0], curNode[0]});
      }
    }
  }

  int maxDepth1 = -1;
  int maxDepth2 = -1;
  int maxDepth3 = -1;

  for(auto g : groups){
    int curGroupMaxDepth = 987654321;
    if(g.size() == 1)
      curGroupMaxDepth = 0;
    else if(g.size() == 2)
      curGroupMaxDepth = graph[g[0]][0][1];
    else{
      for(auto idx : g){
        if(graph[idx].size() == 1) continue;

        int curDepth = getMaxDepthOf(idx, -1);
        if(curGroupMaxDepth > curDepth)
          curGroupMaxDepth = curDepth;
      }
    }

    if (maxDepth1 < curGroupMaxDepth){
      maxDepth3 = maxDepth2;
      maxDepth2 = maxDepth1;
      maxDepth1 = curGroupMaxDepth;
    }
    else if (maxDepth2 < curGroupMaxDepth){
      maxDepth3 = maxDepth2;
      maxDepth2 = curGroupMaxDepth;
    }
    else if (maxDepth3 < curGroupMaxDepth)
      maxDepth3 = curGroupMaxDepth;
  }

  int maxDiameter = 0;
  for(auto g : groups){
    int curDiameter = getDiameter(g[0], -1);
    if(maxDiameter < curDiameter)
      maxDiameter = curDiameter;
  }


  if (maxDepth2 == -1)
    cout << maxDiameter;
  else if (maxDepth3 == -1){
    if(maxDiameter > maxDepth1 + maxDepth2 + L)
      cout << maxDiameter;
    else
      cout << maxDepth1 + maxDepth2 + L;
  }
  else{
    if(maxDiameter < maxDepth1 + maxDepth2 + L){
      if(maxDepth1 + maxDepth2 + L < maxDepth2 + maxDepth3 + 2 * L)
        cout << maxDepth2 + maxDepth3 + 2 * L;
      else
        cout << maxDepth1 + maxDepth2 + L;
    }
    else{
      if(maxDiameter < maxDepth2 + maxDepth3 + 2 * L)
        cout << maxDepth2 + maxDepth3 + 2 * L;
      else
        cout << maxDiameter;
    }
  }

  return 0;
}

int getDiameter(int curInd, int parentInd){
  int diameter = 0;
  int childMax1 = 0;
  int childMax2 = 0;

  for(auto e : graph[curInd]){
    if(e[0] == parentInd) continue;

    int curDiameter = getDiameter(e[0], curInd);
    if(diameter < curDiameter)
      diameter = curDiameter;

    if(childMax1 < e[2]){
      childMax2 = childMax1;
      childMax1 = e[2];
    }
    else if(childMax2 < e[2])
      childMax2 = e[2];
  }

  if(diameter < childMax1 + childMax2)
    return childMax1 + childMax2;
  else
    return diameter;
}

int getMaxDepthOf(int curInd, int parentInd){
  int maxDepth = 0;

  for(int idx = 0; idx < graph[curInd].size(); idx++){
    if(graph[curInd][idx][0] == parentInd) continue;

    if(graph[curInd][idx][2] == -1)
      graph[curInd][idx][2] = getMaxDepthOf(graph[curInd][idx][0], curInd) + graph[curInd][idx][1];

    if(maxDepth < graph[curInd][idx][2])
      maxDepth = graph[curInd][idx][2];
  }

  return maxDepth;
}