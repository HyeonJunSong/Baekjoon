#include <iostream>
#include <vector>
#include <string>
#include <queue>

using namespace std;

class node{
public:
  int nasa;
  int curRotTime;
  int underRotTime;

  bool operator<(node b) const{
    return curRotTime > b.curRotTime;
  }
};

int main(){

  int N;
  cin >> N;

  string curS, wantS;
  cin >> curS;
  cin >> wantS;

  vector<int> cur(N), want(N);
  for(int i = 0; i < N; i++){
    cur[i] = curS[i] - '0';
    want[i] = wantS[i] - '0';
  }

  vector<vector<bool>> visited(N, vector<bool>(10, false));

  priority_queue<node> PQ;
  PQ.push({0, 0, 0});

  while(!PQ.empty()){
    node curNode = PQ.top();
    PQ.pop();

    if(curNode.nasa == N){
      cout << curNode.curRotTime;
      break;
    }

    if(visited[curNode.nasa][curNode.underRotTime]) continue;
      visited[curNode.nasa][curNode.underRotTime] = true;

    PQ.push({curNode.nasa + 1, curNode.curRotTime + (want[curNode.nasa] - (cur[curNode.nasa] + curNode.underRotTime) % 10 + 10) % 10, (curNode.underRotTime + (want[curNode.nasa] - (cur[curNode.nasa] + curNode.underRotTime) % 10 + 10) % 10) % 10});
    PQ.push({curNode.nasa + 1, curNode.curRotTime + ((cur[curNode.nasa] + curNode.underRotTime) % 10 - want[curNode.nasa] + 10) % 10, curNode.underRotTime});
  }


  return 0;
}