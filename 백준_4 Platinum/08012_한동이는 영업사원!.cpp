#include <iostream>
#include <vector>
#include <queue>

using namespace std;

//level, parent
vector<pair<int, int>> pohang;

int n;

int distance(int a, int b);

int main(){

  cin >> n;
  pohang = vector<pair<int, int>>(n, {-1, -1});

  queue<pair<int, int>> edgesLeft;

  for(int i = 0; i < n - 1 ; i++){
    pair<int, int> curEdge;
    cin >> curEdge.first >> curEdge.second;

    if(pohang[curEdge.first].first != -1){
      pohang[curEdge.second].first = pohang[curEdge.first].first + 1;
      pohang[curEdge.second].second = curEdge.first;
      continue;
    }
    if(pohang[curEdge.second].first != -1){
      pohang[curEdge.first].first = pohang[curEdge.second].first + 1;
      pohang[curEdge.first].second = curEdge.second;
      continue;
    }
    edgesLeft.push(curEdge);
  }

  while(!edgesLeft.empty()){
    pair<int, int> curEdge = edgesLeft.front();
    edgesLeft.pop();

    if(pohang[curEdge.first].first != -1){
      pohang[curEdge.second].first = pohang[curEdge.first].first + 1;
      pohang[curEdge.second].second = curEdge.first;
      continue;
    }
    if(pohang[curEdge.second].first != -1){
      pohang[curEdge.first].first = pohang[curEdge.second].first + 1;
      pohang[curEdge.first].second = curEdge.second;
      continue;
    }
    edgesLeft.push(curEdge);
  }

  int m;
  cin >> m;
  
  int totDis = 0;

  int prevNode;
  cin >> prevNode;
  for(int i = 1; i < m; i++){
    int curNode;
    cin >> curNode;

    totDis += distance(prevNode, curNode);
    prevNode = curNode;
  }

  cout << totDis;

  return 0;
}

int distance(int a, int b){

  int aDis = 0;
  int bDis = 0;
  //같은 레벨까지 끌어올리기
  while(pohang[a].first > pohang[b].first){
    a = pohang[a].second;
    aDis++;
  }
  while(pohang[a].first < pohang[b].first){
    b = pohang[b].second;
    bDis++;
  }

  //같은 노드에 도착할때까지 올라가기
  while(a != b){
    a = pohang[a].second;
    b = pohang[b].second;
    aDis++;
    bDis++;
  }

  return aDis + bDis;

}