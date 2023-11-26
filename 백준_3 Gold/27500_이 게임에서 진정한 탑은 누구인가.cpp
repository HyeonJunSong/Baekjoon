////231126
//2h 9m 7s

#include <iostream>
#include <vector>
#include <map>
#include <string>

using namespace std;

int hp1, hp2;
int d1, d2, d3, d4;
int m;

#define INF 987654321

//피오라의 행동. -1이면 공격을 받지 않는 상태, 양수면 그만큼의 데미지를 입히는 상태
vector<int> fioraAction;

vector<vector<vector<pair<int, int>>>> memo;

pair<int, int> getWinCase(int curJhp, int curPhp, int curFrame);
void printWinCase(int curJhp, int curPhp, int curFrame, pair<int, int> ans);

int main(){
  cin >> hp1 >> hp2;
  cin >> d1 >> d2 >> d3 >> d4;
  cin >> m;
  
  fioraAction = vector<int>(302, 0);
  for(int i = 0; i < m; i++){
    int frame;
    string attackName;
    cin >> frame >> attackName;

    if(attackName.compare("attack") == 0){
      if(frame + 4 >= 301) continue;
      fioraAction[frame + 4] = d3;
    }
    else{
      for(int i = 0; i < 9; i++){
        if(frame + i >= 301) break;
        fioraAction[frame + i] = -1;
      }
      if(frame + 9 >= 301) continue;
      fioraAction[frame + 9] = d4;
    }
  }

  memo = vector<vector<vector<pair<int, int>>>>(hp1 + 1, vector<vector<pair<int, int>>>(hp2 + 1, vector<pair<int, int>>(302, {-1, -1})));

  pair<int, int> ans = getWinCase(hp1, hp2, 0);
  if(ans.first == INF){
    cout << "NO";
    return 0;
  }
  cout << "YES\n";
  printWinCase(hp1, hp2, 0, ans);

  return 0;
}

pair<int, int> getWinCase(int curJhp, int curPhp, int curFrame){
  if(curJhp == 0)
    return {INF, INF};
  if(curPhp == 0)
    return {curFrame, -1 * curJhp};
  if(curFrame == 301)
    return {INF, INF};

  pair<int, int> bestWay({INF, INF});

  //넘기기
  if(fioraAction[curFrame] > 0){
    if(curJhp < fioraAction[curFrame]){
      if(memo[0][curPhp][curFrame + 1].first == -1)
        memo[0][curPhp][curFrame + 1] = getWinCase(0, curPhp, curFrame + 1);
      if(bestWay > memo[0][curPhp][curFrame + 1])
        bestWay = memo[0][curPhp][curFrame + 1];
    }
    else{
      if(curJhp > fioraAction[curFrame]){
        if(memo[curJhp - fioraAction[curFrame]][curPhp][curFrame + 1].first == -1)
          memo[curJhp - fioraAction[curFrame]][curPhp][curFrame + 1] = getWinCase(curJhp - fioraAction[curFrame], curPhp, curFrame + 1);
        if(bestWay > memo[curJhp - fioraAction[curFrame]][curPhp][curFrame + 1])
          bestWay = memo[curJhp - fioraAction[curFrame]][curPhp][curFrame + 1];
      }
    }
  }
  else{
    if(memo[curJhp][curPhp][curFrame + 1].first == -1)
      memo[curJhp][curPhp][curFrame + 1] = getWinCase(curJhp, curPhp, curFrame + 1);
    if(bestWay > memo[curJhp][curPhp][curFrame + 1])
      bestWay = memo[curJhp][curPhp][curFrame + 1];
  }

  //반격
  if(curFrame + 14 < 301){
    if(fioraAction[curFrame + 14] < 0){
      if(memo[curJhp][curPhp][curFrame + 15].first == -1)
        memo[curJhp][curPhp][curFrame + 15] = getWinCase(curJhp, curPhp, curFrame + 15);
      if(bestWay > memo[curJhp][curPhp][curFrame + 15])
        bestWay = memo[curJhp][curPhp][curFrame + 15];
    }
    else if(fioraAction[curFrame + 14] > 0){
      if(curJhp > fioraAction[curFrame + 14]){
        if(curPhp < d2){
          if(memo[curJhp - fioraAction[curFrame + 14]][0][curFrame + 15].first == -1)
            memo[curJhp - fioraAction[curFrame + 14]][0][curFrame + 15] = getWinCase(curJhp - fioraAction[curFrame + 14], 0, curFrame + 15);
          if(bestWay > memo[curJhp - fioraAction[curFrame + 14]][0][curFrame + 15])
            bestWay = memo[curJhp - fioraAction[curFrame + 14]][0][curFrame + 15];
        }
        else{
          if(memo[curJhp - fioraAction[curFrame + 14]][curPhp - d2][curFrame + 15].first == -1)
            memo[curJhp - fioraAction[curFrame + 14]][curPhp - d2][curFrame + 15] = getWinCase(curJhp - fioraAction[curFrame + 14], curPhp - d2, curFrame + 15);
          if(bestWay > memo[curJhp - fioraAction[curFrame + 14]][curPhp - d2][curFrame + 15])
            bestWay = memo[curJhp - fioraAction[curFrame + 14]][curPhp - d2][curFrame + 15];
        }
      }
    }
    else{
      if(curPhp < d2){
        if(memo[curJhp][0][curFrame + 15].first == -1)
          memo[curJhp][0][curFrame + 15] = getWinCase(curJhp, 0, curFrame + 15);
        if(bestWay > memo[curJhp][0][curFrame + 15])
          bestWay = memo[curJhp][0][curFrame + 15];
      }
      else{
        if(memo[curJhp][curPhp - d2][curFrame + 15].first == -1)
          memo[curJhp][curPhp - d2][curFrame + 15] = getWinCase(curJhp, curPhp - d2, curFrame + 15);
        if(bestWay > memo[curJhp][curPhp - d2][curFrame + 15])
          bestWay = memo[curJhp][curPhp - d2][curFrame + 15];
      }
    }
  }

  //평타
  for(int i = 0; i <= 4; i++){
    if(curFrame + i >= 301)
      break;
    if(fioraAction[curFrame + i] > 0)
      curJhp -= fioraAction[curFrame + i];
  }
  if(curJhp > 0 && curFrame + 4 < 301){
    if(fioraAction[curFrame + 4] < 0){
      if(memo[curJhp][curPhp][curFrame + 5].first == -1)
        memo[curJhp][curPhp][curFrame + 5] = getWinCase(curJhp, curPhp, curFrame + 5);
      if(bestWay > memo[curJhp][curPhp][curFrame + 5])
        bestWay = memo[curJhp][curPhp][curFrame + 5];
    }
    else{
      if(curPhp < d1){
        if(memo[curJhp][0][curFrame + 5].first == -1)
          memo[curJhp][0][curFrame + 5] = getWinCase(curJhp, 0, curFrame + 5);
        if(bestWay > memo[curJhp][0][curFrame + 5])
          bestWay = memo[curJhp][0][curFrame + 5];
      }
      else{
        if(memo[curJhp][curPhp - d1][curFrame + 5].first == -1)
          memo[curJhp][curPhp - d1][curFrame + 5] = getWinCase(curJhp, curPhp - d1, curFrame + 5);
        if(bestWay > memo[curJhp][curPhp - d1][curFrame + 5])
          bestWay = memo[curJhp][curPhp - d1][curFrame + 5];
      }
    }
  }
  
  return bestWay;
}

void printWinCase(int curJhp, int curPhp, int curFrame, pair<int, int> ans){

  //넘기기
  if(fioraAction[curFrame] > 0){
    if(curJhp < fioraAction[curFrame]){
      if(ans == memo[0][curPhp][curFrame + 1]){
        printWinCase(0, curPhp, curFrame + 1, ans);
        return;
      }
    }
    else{
      if(curJhp > fioraAction[curFrame]){
        if(ans == memo[curJhp - fioraAction[curFrame]][curPhp][curFrame + 1]){
          printWinCase(curJhp - fioraAction[curFrame], curPhp, curFrame + 1, ans);
          return;
        }
      }
    }
  }
  else{
    if(ans == memo[curJhp][curPhp][curFrame + 1]){
      printWinCase(curJhp, curPhp, curFrame + 1, ans);
      return;
    }
  }

  //반격
  if(curFrame + 14 < 301){
    if(fioraAction[curFrame + 14] < 0){
      if(ans == memo[curJhp][curPhp][curFrame + 15]){
        cout << curFrame << ' ' << "counter strike\n";
        printWinCase(curJhp, curPhp, curFrame + 15, ans);
        return;
      }
    }
    else if(fioraAction[curFrame + 14] > 0){
      if(curJhp > fioraAction[curFrame + 14]){
        if(curPhp < d2){
          if(ans == memo[curJhp - fioraAction[curFrame + 14]][0][curFrame + 15]){
            cout << curFrame << ' ' << "counter strike\n";
            printWinCase(curJhp - fioraAction[curFrame + 14], 0, curFrame + 15, ans);
            return;
          }
        }
        else{
          if(ans == memo[curJhp - fioraAction[curFrame + 14]][curPhp - d2][curFrame + 15]){
            cout << curFrame << ' ' << "counter strike\n";
            printWinCase(curJhp - fioraAction[curFrame + 14], curPhp - d2, curFrame + 15, ans);
            return;
          }
        }
      }
    }
    else{
      if(curPhp < d2){
        if(ans == memo[curJhp][0][curFrame + 15]){
          cout << curFrame << ' ' << "counter strike\n";
          printWinCase(curJhp, 0, curFrame + 15, ans);
          return;
        }
      }
      else{
        if(ans == memo[curJhp][curPhp - d2][curFrame + 15]){
          cout << curFrame << ' ' << "counter strike\n";
          printWinCase(curJhp, curPhp - d2, curFrame + 15, ans);
          return;
        }
      }
    }
  }

  //평타
  for(int i = 0; i <= 4; i++){
    if(curFrame + i >= 301)
      break;
    if(fioraAction[curFrame + i] > 0)
      curJhp -= fioraAction[curFrame + i];
  }
  if(curJhp > 0 && curFrame + 4 < 301){
    if(fioraAction[curFrame + 4] < 0){
      if(ans == memo[curJhp][curPhp][curFrame + 5]){
        cout << curFrame << ' ' << "attack\n";
        printWinCase(curJhp, curPhp, curFrame + 5, ans);
        return;
      }
    }
    else{
      if(curPhp < d1){
        if(ans == memo[curJhp][0][curFrame + 5]){
          cout << curFrame << ' ' << "attack\n";
          return;
        }
      }
      else{
        if(ans == memo[curJhp][curPhp - d1][curFrame + 5]){
          cout << curFrame << ' ' << "attack\n";
          printWinCase(curJhp, curPhp - d1, curFrame + 5, ans);
          return;
        }
      }
    }
  }
  
  return ;
}