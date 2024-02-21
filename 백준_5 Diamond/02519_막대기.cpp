#include <iostream>
#include <vector>

using namespace std;

bool ifCCW(pair<int, int> a, pair<int, int> b){
  return (a.first * b.second - a.second * b.first) > 0;
}

bool ifCross(pair<pair<int, int>, pair<int, int>>& a, pair<pair<int, int>, pair<int, int>>& b) {
    //b 의 두점이 a 에 대해 같은 방향에 있는지
    //&& a 의 두점이 b 에 대해 같은 방향에 있는지

    pair<int, int> A1A2 = {a.second.first - a.first.first, a.second.second - a.first.second};
    pair<int, int> A1B1 = {b.first.first - a.first.first, b.first.second - a.first.second};
    pair<int, int> A1B2 = {b.second.first - a.first.first, b.second.second - a.first.second};

    pair<int, int> B1B2 = {b.second.first - b.first.first, b.second.second - b.first.second};
    pair<int, int> B1A1 = {a.first.first - b.first.first, a.first.second - b.first.second};
    pair<int, int> B1A2 = {a.second.first - b.first.first, a.second.second - b.first.second};

    return (ifCCW(A1A2, A1B1) ^ ifCCW(A1A2, A1B2)) && (ifCCW(B1B2, B1A1) ^ ifCCW(B1B2, B1A2));
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

    int N;
    cin >> N;
    vector<pair<pair<int, int>, pair<int, int>>> sticks(3 * N);
    for (int i = 0; i < 3 * N; i++) {
        pair<int, int> a1, a2;

        cin >> a1.first >> a1.second >> a2.first >> a2.second;

        if (a1 < a2) {
            sticks[i].first = a1;
            sticks[i].second = a2;
        }
        else {
            sticks[i].first = a2;
            sticks[i].second = a1;
        }
    }

    vector<vector<int>> graph = vector<vector<int>>(3 * N * 2);

    //각자의 막대에 논리 연결해주기
    //0번이 아니면 1,2 번 맞고, 1번이 아니면 2, 0번 맞고, 2번이 아니면 0, 1번 맞고
    //번호에 2 곱하면 not 노드
    for (int i = 0; i < N; i++) {
        graph[3 * N + (3 * i + 0)].push_back(3 * i + 1);
        graph[3 * N + (3 * i + 0)].push_back(3 * i + 2);
        graph[3 * N + (3 * i + 1)].push_back(3 * i + 2);
        graph[3 * N + (3 * i + 1)].push_back(3 * i + 0);
        graph[3 * N + (3 * i + 2)].push_back(3 * i + 0);
        graph[3 * N + (3 * i + 2)].push_back(3 * i + 1);
    }

    //교차하는 애들에 논리 연결해주기
    //내가 맞으면 나랑 교차하는 애들은 아님
    for (int i = 0; i < 3 * N; i++) {
        for (int j = i + 1; j < 3 * N; j++) {
            if (ifCross(sticks[i], sticks[j])) {
                graph[i].push_back(3 * N + j);
                graph[j].push_back(3 * N + i);
            }
        }
    }

    //scc 구하기
    SCC scc(2 * 3 * N, graph);
    vector<int> gNum = scc.getScc();

    //각 막대에 대해 not 자신노드로 가는 애들이 있으면 false
    vector<int> sticksToSelect;
    for(int i = 0; i < 3 * N; i++){
      if(gNum[i] == gNum[3 * N + i]){
        cout << -1;
        exit(0);
      }

      if(gNum[3 * N + i] < gNum[i])
        sticksToSelect.push_back(i);
    }

    cout << sticksToSelect.size() << "\n";
    for(int i = 0; i < sticksToSelect.size(); i++)
      cout << sticksToSelect[i] + 1 << ' ';

    return 0;
}
