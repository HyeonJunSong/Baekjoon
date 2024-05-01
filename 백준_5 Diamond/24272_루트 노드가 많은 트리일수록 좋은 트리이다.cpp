#include <iostream>
#include <vector>
#include <string>
#include <map>

using namespace std;

map<string, int> edgeToNum = {
  {"<-", -1},
  {"--", 0},
  {"->", 1},
};
vector<vector<pair<int, int>>> graph;
vector<pair<int, int>> parentOf;
vector<int> endOf;
vector<int> idxOf;

void treeToEulerRoute(int parent, int curNode){
  idxOf[curNode] = endOf.size();
  endOf.push_back(-1);
  for(auto e: graph[curNode]){
    if(e.first == parent) continue;
    parentOf[e.first] = {curNode, e.second};
    treeToEulerRoute(curNode, e.first);
  }
  endOf[idxOf[curNode]] = endOf.size() - 1;
}

class Node{
public:
  int st;
  int ed;
  int zeroNum;
  int val;
};

int leafNum = 1;
vector<Node> segTree;
void initSegtree(int N){
  while(leafNum < N) leafNum *= 2;

  segTree = vector<Node>(leafNum * 2);
  for(int i = 0; i < N; i++){
    segTree[leafNum + i].st = i;
    segTree[leafNum + i].ed = i + 1;
    segTree[leafNum + i].zeroNum = 1;
    segTree[leafNum + i].val = 0;
  }
  for(int i = N; i < leafNum; i++){
    segTree[leafNum + i].st = i;
    segTree[leafNum + i].ed = i + 1;
    segTree[leafNum + i].zeroNum = 0;
    segTree[leafNum + i].val = 0;
  }
  for(int i = leafNum - 1; i > 0; i--){
    segTree[i].st = segTree[2 * i].st;
    segTree[i].ed = segTree[2 * i + 1].ed;
    segTree[i].zeroNum = segTree[2 * i].zeroNum + segTree[2 * i + 1].zeroNum;
    segTree[i].val = 0;
  }
}

void updateSegtree(int idx, int st, int ed, int k){
  if(segTree[idx].st + 1 == segTree[idx].ed){
    segTree[idx].val += k;
    if(segTree[idx].val > 0)
      segTree[idx].zeroNum = 0;
    else
      segTree[idx].zeroNum = 1;
    return;
  }

  if(segTree[idx].st == st && segTree[idx].ed == ed){
    segTree[idx].val += k;

    if(segTree[idx].val > 0){
      segTree[idx].zeroNum = 0;
    } else {
      segTree[idx].zeroNum = segTree[2 * idx].zeroNum + segTree[2 * idx + 1].zeroNum;
    }

    return;
  }

  if(ed <= segTree[2 * idx].ed)
    updateSegtree(2 * idx, st, ed, k);
  else if(st >= segTree[2 * idx + 1].st)
    updateSegtree(2 * idx + 1, st, ed, k);
  else{
    updateSegtree(2 * idx, st, segTree[2 * idx].ed, k);
    updateSegtree(2 * idx + 1, segTree[2 * idx + 1].st, ed, k);
  }

  if(segTree[idx].val > 0)
    segTree[idx].zeroNum = 0;
  else
    segTree[idx].zeroNum = segTree[2 * idx].zeroNum + segTree[2 * idx + 1].zeroNum;
  return;
}

int main(){

  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  int N;
  cin >> N;

  graph = vector<vector<pair<int, int>>>(N);
  int st, ed;
  string edge;
  vector<pair<int, int>> links;
  for(int i = 0; i < N - 1; i++){
    cin >> st >> edge >> ed;
    st--; ed--;
    graph[st].push_back({ed, edgeToNum[edge]});
    graph[ed].push_back({st, -1 * edgeToNum[edge]});

    switch(edgeToNum[edge]){
      case -1:
        links.emplace_back(ed, st);
        break;
      case 1:
        links.emplace_back(st, ed);
        break;
    }
  }

  idxOf = vector<int>(N);
  parentOf = vector<pair<int, int>>(N);
  treeToEulerRoute(-1, 0);
  
  initSegtree(N);

  for(auto e: links){
    if(idxOf[e.first] < idxOf[e.second]){
      updateSegtree(1, idxOf[e.second], endOf[idxOf[e.second]] + 1, 1);
    }
    else{
      if(idxOf[e.first] != 0)
        updateSegtree(1, 0, idxOf[e.first], 1);
      if(endOf[idxOf[e.first]] + 1 != N)
        updateSegtree(1, endOf[idxOf[e.first]] + 1, N, 1);
    }
  }

  int Q;
  cin >> Q;
  for(int i = 0; i < Q; i++){
    cin >> st >> edge >> ed;
    st--; ed--;

    int edgeNum = edgeToNum[edge];
    if(parentOf[st].first == ed){
      swap(st, ed);
      edgeNum *= -1;
    }

    switch(parentOf[ed].second){
      case -1:
        switch(edgeNum){
          case -1:
          break;
          case 0:

            if(idxOf[ed] != 0)
              updateSegtree(1, 0, idxOf[ed], -1);
            if(endOf[idxOf[ed]] + 1 != N)
              updateSegtree(1, endOf[idxOf[ed]] + 1, N, -1);

            parentOf[ed].second = 0;
          break;
          case 1:

            if(idxOf[ed] != 0)
              updateSegtree(1, 0, idxOf[ed], -1);
            if(endOf[idxOf[ed]] + 1 != N)
              updateSegtree(1, endOf[idxOf[ed]] + 1, N, -1);

            updateSegtree(1, idxOf[ed], endOf[idxOf[ed]] + 1, 1);
            parentOf[ed].second = 1;

          break;
        }
      break;
      case 0:
        switch(edgeNum){
          case -1:
            if(idxOf[ed] != 0)
              updateSegtree(1, 0, idxOf[ed], 1);
            if(endOf[idxOf[ed]] + 1 != N)
              updateSegtree(1, endOf[idxOf[ed]] + 1, N, 1);
            parentOf[ed].second = -1;
          break;
          case 0:
          break;
          case 1:
            updateSegtree(1, idxOf[ed], endOf[idxOf[ed]] + 1, 1);
            parentOf[ed].second = 1;
          break;
        }
      break;
      case 1:
        switch(edgeNum){
          case -1:
            updateSegtree(1, idxOf[ed], endOf[idxOf[ed]] + 1, -1);

            if(idxOf[ed] != 0)
              updateSegtree(1, 0, idxOf[ed], 1);
            if(endOf[idxOf[ed]] + 1 != N)
              updateSegtree(1, endOf[idxOf[ed]] + 1, N, 1);
            parentOf[ed].second = -1;
          break;
          case 0:
            updateSegtree(1, idxOf[ed], endOf[idxOf[ed]] + 1, -1);
            parentOf[ed].second = 0;
          break;
          case 1:
          break;
        }
      break;
    }

    cout << segTree[1].zeroNum << "\n";
  }

  return 0;
}