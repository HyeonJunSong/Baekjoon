#include <iostream>
#include <vector>
#include <string>
#include <queue>

using namespace std;

class node{
  public:
  int I;
  int J;
  int moveCnt;
  int hp;
  int uHp;

  bool operator<(node b) const{
    if(moveCnt == b.moveCnt)
      return hp + uHp < b.hp + b.uHp;
    return moveCnt > b.moveCnt;
  }

};

int dir[4][2] = {
  {-1, 0},
  { 1, 0},
  { 0, 1},
  { 0,-1},
};

int main(){

  int N, H, D;
  cin >> N >> H >> D;

  vector<string> board(N);
  for(int i = 0; i < N; i++)
    cin >> board[i];
  
  vector<vector<int>> curMaxHP(N, vector<int>(N, -1));

  pair<int, int> st;
  for(int i = 0; i < N; i++){
    for(int j = 0; j < N; j++){
      if(board[i][j] == 'S')
        st = {i, j};
    }
  }

  priority_queue<node> PQ;
  PQ.push({
    st.first,
    st.second,
    0,
    H,
    0
  });

  int ans = -1;

  while(!PQ.empty()){
    node curNode = PQ.top();
    PQ.pop();

    if(curMaxHP[curNode.I][curNode.J] >= curNode.hp + curNode.uHp) continue;
    curMaxHP[curNode.I][curNode.J] = curNode.hp + curNode.uHp;

    if(board[curNode.I][curNode.J] == 'E'){
      ans = curNode.moveCnt;
      break;
    }
    
    //우산 들기
    if(board[curNode.I][curNode.J] == 'U')
      curNode.uHp = D;

    //죽음의 비 맞기
    if(!(curNode.I == st.first && curNode.J == st.second)){
      if(curNode.uHp > 0)
        curNode.uHp--;
      else if(curNode.hp > 0)
        curNode.hp--;
    }

    if(curNode.hp == 0) continue;

    //이동
    for(int d = 0; d < 4; d++){
      if(0 <= curNode.I + dir[d][0] && curNode.I + dir[d][0] < N
      && 0 <= curNode.J + dir[d][1] && curNode.J + dir[d][1] < N
      && curMaxHP[curNode.I + dir[d][0]][curNode.J + dir[d][1]] < curNode.hp + curNode.uHp)
        PQ.push({curNode.I + dir[d][0], curNode.J + dir[d][1], curNode.moveCnt + 1, curNode.hp, curNode.uHp});
    }

  }

  cout << ans;

  return 0;
}