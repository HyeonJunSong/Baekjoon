#include <iostream>
#include <vector>
#include <string>
#include <queue>

using namespace std;

class Node{
public:
  int move;
  int I;
  int J;
  int curR;

  bool operator< (Node b) const {
    return move > b.move;
  }
};

int dir[5][2] = {
  {-1,  0},
  { 1,  0},
  { 0, -1},
  { 0,  1},
  { 0,  0},
};

int k;
inline int getAreaNum(int I, int J){
  return k * (I / 4) + (J / 4);
}

int rotate1[4][4][4] = {
  {
    { 0,  1,  2,  3},
    { 4,  5,  6,  7},
    { 8,  9, 10, 11},
    {12, 13, 14, 15},
  },
  {
    {12,   8,  4,  0},
    {13,   9,  5,  1},
    {14,  10,  6,  2},
    {15,  11,  7,  3},
  },
  {
    {15,  14, 13, 12},
    {11,  10,  9,  8},
    { 7,   6,  5,  4},
    { 3,   2,  1,  0},
  },
  {
    { 3,   7, 11, 15},
    { 2,   6, 10, 14},
    { 1,   5,  9, 13},
    { 0,   4,  8, 12},
  }
};

int rotate2[16][2] = {
  {0, 0}, {0, 1}, {0, 2}, {0, 3},
  {1, 0}, {1, 1}, {1, 2}, {1, 3},
  {2, 0}, {2, 1}, {2, 2}, {2, 3},
  {3, 0}, {3, 1}, {3, 2}, {3, 3}
};

pair<int, int> rotatedLoc(int I, int J, int r){
  return {(I / 4) * 4 + rotate2[rotate1[r][I % 4][J % 4]][0], (J / 4) * 4 + rotate2[rotate1[r][I % 4][J % 4]][1]};
}

int main(){

  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  cin >> k;

  vector<string> maze(4 * k);
  for(int i = 0; i < 4 * k; i++)
    cin >> maze[i];
  
  vector<vector<vector<bool>>> visited(4 * k, vector<vector<bool>>(4 * k, vector<bool>(4, false)));

  priority_queue<Node> PQ;
  for(int i = 0; i < 4 * k; i++){
    for(int j = 0; j < 4 * k; j++){
      if(maze[i][j] == 'S'){
        PQ.push({0, i, j, 0});
        break;
      }
    }
    if(!PQ.empty()) break;
  }
  
  int ans = -1;
  while(!PQ.empty()){
    Node curNode = PQ.top();
    PQ.pop();

    if(visited[curNode.I][curNode.J][curNode.curR]) continue;
      visited[curNode.I][curNode.J][curNode.curR] = true;
    
    if(maze[curNode.I][curNode.J] == 'E'){
      ans = curNode.move;
      break;
    }

    int curArea = getAreaNum(curNode.I, curNode.J);

    for(int d = 0; d < 5; d++){
      if(0 <= curNode.I + dir[d][0] && curNode.I + dir[d][0] < 4 * k
      && 0 <= curNode.J + dir[d][1] && curNode.J + dir[d][1] < 4 * k
      && maze[curNode.I + dir[d][0]][curNode.J + dir[d][1]] != '#'
      && curArea == getAreaNum(curNode.I + dir[d][0], curNode.J + dir[d][1])){
          PQ.push({curNode.move + 1, curNode.I + dir[d][0], curNode.J + dir[d][1], (curNode.curR + 3) % 4});
      }
    }

    pair<int, int> curLoc = rotatedLoc(curNode.I, curNode.J, curNode.curR);

    for(int d = 0; d < 4; d++){

      if(0 <= curLoc.first + dir[d][0] && curLoc.first + dir[d][0] < 4 * k
      && 0 <= curLoc.second + dir[d][1] && curLoc.second + dir[d][1] < 4 * k
      && maze[curLoc.first + dir[d][0]][curLoc.second + dir[d][1]] != '#'
      && curArea != getAreaNum(curLoc.first + dir[d][0], curLoc.second + dir[d][1])){
          PQ.push({curNode.move + 1, curLoc.first + dir[d][0], curLoc.second + dir[d][1], 3});
      }
    }
    
  }

  cout << ans;


  return 0;
}