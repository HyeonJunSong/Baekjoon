#include <iostream>
#include <vector>
#include <queue>

using namespace std;

#define MAX_CAPACITY 2000000001

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  int n, m;
  cin >> n >> m;
  int source, sink;
  cin >> source >> sink;
  source--; sink--;
  sink += n;
  
  vector<vector<int>> capacity(2 * n, vector<int>(2 * n, 0));
  vector<vector<int>> flow(2 * n, vector<int>(2 * n, 0));

  for(int i = 0; i < n; i++){
    int cost;
    cin >> cost;
    capacity[i][n + i] = cost;
    capacity[n + i][i] = cost;
  }

  for(int i = 0; i < m; i++){
    int st, ed;
    cin >> st >> ed;
    st--; ed--;
    capacity[n + st][ed] = MAX_CAPACITY;
    capacity[n + ed][st] = MAX_CAPACITY;
  }


  while(true){
    queue<int> Q;
    Q.push(source);
    vector<int> parentOf(2 * n, -1);
    while(!Q.empty()){
      int curNode = Q.front();
      Q.pop();
      if(curNode == sink) break;

      for(int i = 0; i < 2 * n; i++){
        if(parentOf[i] != -1) continue;
        if(capacity[curNode][i] - flow[curNode][i] <= 0) continue;
        parentOf[i] = curNode;
        Q.push(i);
      }
    }

    if(parentOf[sink] == -1) break;

    int curNode = sink;
    int curFlow = MAX_CAPACITY;
    int curBlockNode;
    while(curNode != source){
      if(curFlow > capacity[parentOf[curNode]][curNode] - flow[parentOf[curNode]][curNode]){
        curFlow = capacity[parentOf[curNode]][curNode] - flow[parentOf[curNode]][curNode];
        curBlockNode = parentOf[curNode];
      }

      curNode = parentOf[curNode];
    }

    curNode = sink;
    while(curNode != source){
      flow[parentOf[curNode]][curNode] += curFlow;
      flow[curNode][parentOf[curNode]] -= curFlow;

      curNode = parentOf[curNode];
    }
  }

  queue<int> Q;
  Q.push(source);
  vector<bool> visited(2 * n, false);
  while(!Q.empty()){
    int curNode = Q.front();
    Q.pop();
    if(curNode == sink) break;

    if(visited[curNode]) continue;
    visited[curNode] = true;

    for(int i = 0; i < 2 * n; i++){
      if(visited[i]) continue;
      if(capacity[curNode][i] - flow[curNode][i] <= 0) continue;
      Q.push(i);
    }
  }

  for(int i = 0; i < n; i++){
    if(visited[i] && !visited[i + n])
      cout << i + 1 << " ";
  }


  
  return 0;
}