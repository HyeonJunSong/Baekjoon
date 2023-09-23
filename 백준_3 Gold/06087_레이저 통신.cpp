////230923
//1h 11m 11s

#include <iostream>
#include <queue>
#include <vector>
#include <string>

using namespace std;

class node{
public:
  pair<int, int> before;
  pair<int, int> cur;

  int mirrorCnt;

  bool operator<(node b) const{
    return mirrorCnt > b.mirrorCnt;
  }
};

int main(){

  int W, H;
  cin >> W >> H;

  vector<string> map(H);
  for(int i = 0; i < H; i++)
    cin >> map[i];

  //C 위치 알아내기
  pair<int, int> st = {-1, -1};
  pair<int, int> ed = {-1, -1};
  
  for(int i = 0; i < H; i++){
    for(int j = 0; j < W; j++){
      if(map[i][j] == 'C'){
        if(st.first == -1)
          st = {j, i};
        else{
          ed = {j, i};
          break;
        }
      }
    }
    if(ed.first != -1) break;
  }

  priority_queue<node> PQ;

  if(0 < st.first && map[st.second][st.first - 1] != '*')
    PQ.push({st, {st.first - 1, st.second}, 0});
  if(W - 1 > st.first && map[st.second][st.first + 1] != '*')
    PQ.push({st, {st.first + 1, st.second}, 0});
  if(0 < st.second && map[st.second - 1][st.first] != '*')
    PQ.push({st, {st.first, st.second - 1}, 0});
  if(H - 1 > st.second && map[st.second + 1][st.first] != '*')
    PQ.push({st, {st.first, st.second + 1}, 0});

  vector<vector<vector<bool>>> visited(W, vector<vector<bool>>(H, vector<bool>(2, false)));
  visited[st.first][st.second][0] = true;
  visited[st.first][st.second][1] = true;

  while(!PQ.empty()){
    node curNode = PQ.top();
    PQ.pop();

    if(curNode.cur.first - curNode.before.first != 0){
      if(visited[curNode.cur.first][curNode.cur.second][0])
        continue;
      visited[curNode.cur.first][curNode.cur.second][0] = true;
    }
    else{
      if(visited[curNode.cur.first][curNode.cur.second][1])
        continue;
      visited[curNode.cur.first][curNode.cur.second][1] = true;
    }

    if(curNode.cur == ed){
      cout << curNode.mirrorCnt;
      break;
    }

    pair<int, int> curDir = {curNode.cur.first - curNode.before.first, curNode.cur.second - curNode.before.second};

    //반사1
    if(0 <= curNode.cur.first + curDir.second && curNode.cur.first + curDir.second < W
    && 0 <= curNode.cur.second + curDir.first && curNode.cur.second + curDir.first < H
    && map[curNode.cur.second + curDir.first][curNode.cur.first + curDir.second] != '*')
      PQ.push({curNode.cur, {curNode.cur.first + curDir.second, curNode.cur.second + curDir.first}, curNode.mirrorCnt + 1});

    //반사2
    if(0 <= curNode.cur.first - curDir.second && curNode.cur.first - curDir.second < W
    && 0 <= curNode.cur.second - curDir.first && curNode.cur.second - curDir.first < H
    && map[curNode.cur.second - curDir.first][curNode.cur.first - curDir.second] != '*')
      PQ.push({curNode.cur, {curNode.cur.first - curDir.second, curNode.cur.second - curDir.first}, curNode.mirrorCnt + 1});

    //직진
    if(0 <= curNode.cur.first + curDir.first && curNode.cur.first + curDir.first < W
    && 0 <= curNode.cur.second + curDir.second && curNode.cur.second + curDir.second < H
    && map[curNode.cur.second + curDir.second][curNode.cur.first + curDir.first] != '*')
      PQ.push({curNode.cur, {curNode.cur.first + curDir.first, curNode.cur.second + curDir.second}, curNode.mirrorCnt});
  }
  
  return 0;
}