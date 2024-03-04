#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <string>

using namespace std;

#define LL long long

#define INF 987654321

map<LL, int> numberMap;

int leafNum = 1;

class node{
public:

  int command;
  int firstTrueIdx;
  int firstFalseIdx;
  int st;
  int ed;

  node(){
    this->command = -1;
    this->firstTrueIdx = INF;
    this->firstFalseIdx = INF;
    this->st = INF;
    this->ed = INF;
  }

};

vector<node> segTree;

void segTreeInit(int N){

  while(leafNum < N)
    leafNum *= 2;
  
  segTree = vector<node>(2 * leafNum);
  for(int i = 0; i < leafNum; i++){
    segTree[leafNum + i].st = i;
    segTree[leafNum + i].ed = i + 1;
    segTree[leafNum + i].firstFalseIdx = i;
  }

  for(int i = leafNum - 1; i > 0; i--){
    segTree[i].st = segTree[2 * i].st;
    segTree[i].ed = segTree[2 * i + 1].ed;
    segTree[i].firstFalseIdx = segTree[2 * i].st;
  }
}

int segTreeCommand(int idx, int st, int ed, int command){
  if(segTree[idx].st == st && segTree[idx].ed == ed){

    if(command == -1)
      return segTree[idx].firstFalseIdx;

    switch(command){
      case 1:
        segTree[idx].firstFalseIdx = INF;
        segTree[idx].firstTrueIdx = segTree[idx].st;
        break;
      case 2:
        segTree[idx].firstFalseIdx = segTree[idx].st;
        segTree[idx].firstTrueIdx = INF;
        break;
      case 3:
        int tmp = segTree[idx].firstFalseIdx;
        segTree[idx].firstFalseIdx = segTree[idx].firstTrueIdx;
        segTree[idx].firstTrueIdx = tmp;
        break;
    }

    if(command == 3){
      switch(segTree[idx].command){
        case -1:
          segTree[idx].command = 3;
          break;
        case 1:
          segTree[idx].command = 2;
          break;
        case 2:
          segTree[idx].command = 1;
          break;
        case 3:
          segTree[idx].command = -1;
          break;
      }
    } else {
      segTree[idx].command = command;
    }

    return segTree[idx].firstFalseIdx;
  }

  //프로파게이션

  if(segTree[idx].command != -1){
    segTreeCommand(2 * idx, segTree[2 * idx].st, segTree[2 * idx].ed, segTree[idx].command);
    segTreeCommand(2 * idx + 1, segTree[2 * idx + 1].st, segTree[2 * idx + 1].ed, segTree[idx].command);

    segTree[idx].command = -1;
  }


  if(segTree[2 * idx].ed >= ed){
    segTreeCommand(2 * idx, st, ed, command);
  }
  else if(segTree[2 * idx + 1].st <= st){
    segTreeCommand(2 * idx + 1, st, ed, command);
  } else {
    segTreeCommand(2 * idx, st, segTree[2 * idx].ed, command);
    segTreeCommand(2 * idx + 1, segTree[2 * idx + 1].st, ed, command);
  }

  segTree[idx].firstFalseIdx = min(segTree[2 * idx].firstFalseIdx, segTree[2 * idx + 1].firstFalseIdx);
  segTree[idx].firstTrueIdx = min(segTree[2 * idx].firstTrueIdx, segTree[2 * idx + 1].firstTrueIdx);

  return segTree[idx].firstFalseIdx;
}

int main(){

  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  int N;
  cin >> N;

  vector<pair<int, pair<LL, LL>>> query;

  for(int i = 0; i < N; i++){
    int q;
    LL l, r;
    cin >> q >> l >> r;

    query.push_back({q, {l, r}});

    if(l > 1)
      numberMap[l - 1] = -1;
    numberMap[l] = -1;
    numberMap[l + 1] = -1;

    if(r > 1)
      numberMap[r - 1] = -1;
    numberMap[r] = -1;
    numberMap[r + 1] = -1;
  }

  numberMap[1] = -1;

  int numberMapSize = 0;

  vector<LL> numberMapRev(numberMap.size());
  for(auto e: numberMap){
    numberMapRev[numberMapSize] = e.first;
    numberMap[e.first] = numberMapSize++;
  }
  
  segTreeInit(numberMapSize);
  
  for(auto e: query){
    segTreeCommand(1, numberMap[e.second.first], numberMap[e.second.second] + 1, e.first);
    cout << numberMapRev[segTreeCommand(1, 0, numberMapSize, -1)] << '\n';
  }

  return 0;
}