#include <iostream>
#include <vector>
#include <queue>

using namespace std;
#define INF 987654321
#define LL long long

int leafNum;
vector<pair<int, pair<int, int>>> segTree;

void segTreeInit(int N){
  leafNum = 1;
  while(leafNum < N)
    leafNum *= 2;

  segTree = vector<pair<int, pair<int, int>>>(leafNum * 2);
  for(int i = 0; i < leafNum; i++){
    segTree[leafNum + i].first = INF;
    segTree[leafNum + i].second.first = i;
    segTree[leafNum + i].second.second = i + 1;
  }
  for(int i = leafNum - 1; i > 0; i--){
    segTree[i].first = INF;
    segTree[i].second.first = segTree[2 * i].second.first;
    segTree[i].second.second = segTree[2 * i + 1].second.second;
  }
}

void segTreeInsert(int idx, int nodeIdx, int val){
  if(segTree[idx].second.first == nodeIdx && segTree[idx].second.second == nodeIdx + 1){
    segTree[idx].first = min(val, segTree[idx].first);
    return;
  }
  
  if(segTree[2 * idx].second.second >= nodeIdx + 1){
    segTreeInsert(2 * idx, nodeIdx, val);
    segTree[idx].first = min(segTree[idx].first, segTree[2 * idx].first);
  }
  else{
    segTreeInsert(2 * idx + 1, nodeIdx, val);
    segTree[idx].first = min(segTree[idx].first, segTree[2 * idx + 1].first);
  }
}

int segTreeSearchMin(int idx, int stIdx, int edIdx){
  if(segTree[idx].second.first == stIdx && segTree[idx].second.second == edIdx)
    return segTree[idx].first;
  
  if(segTree[2 * idx].second.second >= edIdx)
    return segTreeSearchMin(2 * idx, stIdx, edIdx);
  if(segTree[2 * idx + 1].second.first <= stIdx)
    return segTreeSearchMin(2 * idx + 1, stIdx, edIdx);
  
  return min(segTreeSearchMin(2 * idx, stIdx, segTree[2 * idx].second.second), segTreeSearchMin(2 * idx + 1, segTree[2 * idx + 1].second.first, edIdx));
}

int main(){

  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  int N;
  cin >> N;

  vector<int> apartments(3);
  for(int i = 0; i < 3; i++)
    cin >> apartments[i];

  vector<vector<pair<int, LL>>> graph(N + 1);
  int M;
  cin >> M;
  for(int i = 0; i < M; i++){
    int X, Y, Z;
    cin >> X >> Y >> Z;
    graph[X].push_back({Y, Z});
    graph[Y].push_back({X, Z});
  }

  vector<vector<int>> distanceRanks(3, vector<int>(N + 1));
  //아파트 세곳에서 각 매장 후보지까지의 최단거리 구하기 -> 다익스트라 세번

  for(int i = 0; i < 3; i++){

    priority_queue<pair<LL, int>> PQ;
    PQ.push({0, apartments[i]});
    vector<bool> visited(N + 1, false);

    distanceRanks[i][apartments[i]] = 1;
    int curRank = 1;
    LL lastRankDistance = 0;

    while(!PQ.empty()){
      pair<LL, int> curNode = PQ.top();
      PQ.pop();

      if(visited[curNode.second]) continue;
      visited[curNode.second] = true;

      if(lastRankDistance == curNode.first)
        distanceRanks[i][curNode.second] = curRank;
      else
        distanceRanks[i][curNode.second] = ++curRank;
      lastRankDistance = curNode.first;

      for(auto e: graph[curNode.second]){
        if(visited[e.first]) continue;

        PQ.push({curNode.first - e.second, e.first});
      }
    }
  }

  segTreeInit(N + 1);

  vector<vector<int>> ARankOrder(N + 1);
  for(int i = 1; i <= N; i++)
    ARankOrder[distanceRanks[0][i]].push_back(i);

  vector<bool> ifPossible(N + 1, true);
  for(auto e: ARankOrder){

    for(auto e2: e){
      if(segTreeSearchMin(1, 0, distanceRanks[1][e2]) < distanceRanks[2][e2])
        ifPossible[e2] = false;
    }

    for(auto e2: e)
      segTreeInsert(1, distanceRanks[1][e2], distanceRanks[2][e2]);

  }

  int T;
  cin >> T;
  for(int t = 0; t < T; t++){
    int Q;
    cin >> Q;
    if(ifPossible[Q])
      cout << "YES\n";
    else
      cout << "NO\n";
  }

  return 0;
}