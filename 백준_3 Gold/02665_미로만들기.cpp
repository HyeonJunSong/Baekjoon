////231208
//12m 08s

#include <iostream>
#include <vector>
#include <string>
#include <queue>

using namespace std;

class node{
public:
  int curI;
  int curJ;
  int distroied;

  bool operator<(node b) const{
    return distroied > b.distroied;
  }
};

int dir[4][2] = {
  {-1,  0},
  { 0,  1},
  { 1,  0},
  { 0, -1}
};

int main(){

  int n;
  cin >> n;
  vector<string> room(n);
  for(int i = 0; i < n; i++)
    cin >> room[i];
  
  priority_queue<node> PQ;
  PQ.push({0, 0 ,0});

  vector<vector<bool>> visited(n, vector<bool>(n, false));

  while(!PQ.empty()){
    node curNode = PQ.top();
    PQ.pop();

    if(curNode.curI == n - 1 && curNode.curJ == n - 1){
      cout << curNode.distroied;
      break;
    }

    if(visited[curNode.curI][curNode.curJ]) continue;
    visited[curNode.curI][curNode.curJ] = true;

    for(int d = 0; d < 4; d++){
      if(0 <= curNode.curI + dir[d][0] && curNode.curI + dir[d][0] < n
      && 0 <= curNode.curJ + dir[d][1] && curNode.curJ + dir[d][1] < n){
        if(room[curNode.curI + dir[d][0]][curNode.curJ + dir[d][1]] == '0')
          PQ.push({curNode.curI + dir[d][0], curNode.curJ + dir[d][1], curNode.distroied + 1});
        else
          PQ.push({curNode.curI + dir[d][0], curNode.curJ + dir[d][1], curNode.distroied});
      }
    }

  }
  


  return 0;
}