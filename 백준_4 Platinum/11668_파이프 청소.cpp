#include <iostream>
#include <vector>

using namespace std;

vector<pair<int, int>> waterOrigins;

int CCW(pair<int, int> a, pair<int, int> b){
  if((a.first * b.second - a.second * b.first) > 0)
    return 1;
  else if ((a.first * b.second - a.second * b.first) < 0)
    return -1;
  else
    return 0;
}

bool ifCross(pair<pair<int, int>, pair<int, int>> a, pair<pair<int, int>, pair<int, int>> b) {
    //b 의 두점이 a 에 대해 같은 방향에 있는지
    //&& a 의 두점이 b 에 대해 같은 방향에 있는지

    pair<int, int> A1A2 = {a.second.first - a.first.first, a.second.second - a.first.second};
    pair<int, int> A1B1 = {b.first.first - a.first.first, b.first.second - a.first.second};
    pair<int, int> A1B2 = {b.second.first - a.first.first, b.second.second - a.first.second};

    int A2B1 = CCW(A1A2, A1B1);
    int A2B2 = CCW(A1A2, A1B2);


    pair<int, int> B1B2 = {b.second.first - b.first.first, b.second.second - b.first.second};
    pair<int, int> B1A1 = {a.first.first - b.first.first, a.first.second - b.first.second};
    pair<int, int> B1A2 = {a.second.first - b.first.first, a.second.second - b.first.second};

    int B2A1 = CCW(B1B2, B1A1);
    int B2A2 = CCW(B1B2, B1A2);

    if(A2B1 * A2B2 == 0 && B2A1 * B2A2 == 0)
      return min(b.first, b.second) <= max(a.first, a.second) && max(b.first, b.second) >= min(a.first, a.second);
    

    return (A2B1 * A2B2 <= 0) && (B2A1 * B2A2 <= 0);
}

class SCC{
public:
  int V;
  vector<vector<int>>& graph;
  int groupId = 0;
  vector<int> groupIdOf;
  vector<bool> visited;
  vector<int> stack;
  vector<int> stackIdx;
  const int MAX = 987654321;

  SCC(int V, vector<vector<int>>& graph):V(V), graph(graph){}

  vector<int> getScc(){
    groupIdOf = vector<int>(V, -1);
    stackIdx = vector<int>(V, -1);
    visited = vector<bool>(V, false);

    for (int v = 0; v < V; v++) {
      if (visited[v]) continue;
      DFS(v, stack, stackIdx);
    }
    return groupIdOf;
  }

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
};

int main() {

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int w, p;
    cin >> w >> p;

    waterOrigins = vector<pair<int, int>>(w);
    for(int i = 0; i < w; i++)
      cin >> waterOrigins[i].first >> waterOrigins[i].second;
    
    vector<pair<int, pair<int, int>>> pipes(p);
    for(int i = 0; i < p; i++){
      int s, x, y;
      cin >> s >> x >> y;
      pipes[i] = {s - 1, {x, y}};
    }

    vector<vector<int>> graph = vector<vector<int>>(p * 2);
    for(int i = 0; i < p - 1; i++){
      for(int j = i + 1; j < p; j++){
        if(waterOrigins[pipes[i].first] == waterOrigins[pipes[j].first])
        continue;

        if(ifCross({waterOrigins[pipes[i].first], pipes[i].second}, {waterOrigins[pipes[j].first], pipes[j].second})){
          graph[i].push_back(p + j);
          graph[p + j].push_back(i);
          graph[j].push_back(p + i);
          graph[p + i].push_back(j);
        }
      }
    }

    //scc 구하기
    SCC scc(p * 2, graph);
    vector<int> gNum = scc.getScc();

    bool ifPossible = true;
    for(int i = 0; i < p; i++){
      if(gNum[i] == gNum[p + i]){
        ifPossible = false;
        break;
      }
    }

    if(ifPossible)
      cout << "possible";
    else
      cout << "impossible";

    return 0;
}
