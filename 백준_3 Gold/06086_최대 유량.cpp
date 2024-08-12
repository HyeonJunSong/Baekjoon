#include <iostream>
#include <vector>
#include <map>
#include <queue>

using namespace std;

int main(){

  int N;
  cin >> N;

  vector<pair<pair<char, char>, int>> pipes(N);
  for(int i = 0; i < N; i++)
    cin >> pipes[i].first.first >> pipes[i].first.second >> pipes[i].second;

  map<char, int> idxOf;
  for(auto e: pipes){
    if(idxOf.find(e.first.first) == idxOf.end())
      idxOf[e.first.first] = idxOf.size();
    if(idxOf.find(e.first.second) == idxOf.end())
      idxOf[e.first.second] = idxOf.size();
  }

  int nodeNum = idxOf.size();
  vector<vector<int>> capacity(nodeNum, vector<int>(nodeNum, 0));
  vector<vector<int>> flow(nodeNum, vector<int>(nodeNum, 0));

  for(auto e: pipes){
    capacity[idxOf[e.first.first]][idxOf[e.first.second]] += e.second;
    capacity[idxOf[e.first.second]][idxOf[e.first.first]] += e.second;
  }

  int source = idxOf['A'];
  int sink = idxOf['Z'];

  int ans = 0;
  while(true){
    //경로 찾기
    queue<int> Q;
    Q.push(source);

    vector<int> parentOf(nodeNum, -1);

    while(Q.size()){
      int curNode = Q.front();
      Q.pop();

      if(curNode == sink) break;

      for(int i = 0; i < nodeNum; i++){
        if(parentOf[i] != -1) continue;
        if(capacity[curNode][i] - flow[curNode][i] <= 0) continue;
        parentOf[i] = curNode;
        Q.push(i);
      }
    }

    //유량 찾기
    if(parentOf[sink] == -1) break;

    int curFlow = 987654321;
    int curNode = sink;
    while(curNode != source){
      curFlow = min(curFlow, capacity[parentOf[curNode]][curNode] - flow[parentOf[curNode]][curNode]);
      curNode = parentOf[curNode];
    }

    //갱신하기
    curNode = sink;
    while(curNode != source){
      flow[parentOf[curNode]][curNode] += curFlow;
      flow[curNode][parentOf[curNode]] -= curFlow;
      curNode = parentOf[curNode];
    }

    ans += curFlow;
  }

  cout << ans;

  return 0;
}