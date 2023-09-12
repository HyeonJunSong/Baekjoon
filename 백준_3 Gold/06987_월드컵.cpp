////23.09.12
//1h 11m 5s

#include <iostream>
#include <vector>

using namespace std;

bool ifPossibleGameDFS(int cur, int prevRight, vector<vector<int>>& game, int& numOfGames){

  if(cur == 6){
    if(numOfGames == 15)
      return true;
    else
      return false;
  }

  if(prevRight == 5)
    return ifPossibleGameDFS(cur + 1, cur + 1, game, numOfGames);

  for(int i = prevRight + 1; i < 6; i++){
    //승
    if(game[cur][0] > 0 && game[i][2] > 0){
      game[cur][0]--;
      game[i][2]--;
      numOfGames++;
      if(ifPossibleGameDFS(cur, i, game, numOfGames)) return true;
      numOfGames--;
      game[cur][0]++;
      game[i][2]++;
    }

    //무
    if(game[cur][1] > 0 && game[i][1] > 0){
      game[cur][1]--;
      game[i][1]--;
      numOfGames++;
      if(ifPossibleGameDFS(cur, i, game, numOfGames)) return true;
      numOfGames--;
      game[cur][1]++;
      game[i][1]++;
    }

    //패
    if(game[cur][2] > 0 && game[i][0] > 0){
      game[cur][2]--;
      game[i][0]--;
      numOfGames++;
      if(ifPossibleGameDFS(cur, i, game, numOfGames)) return true;
      numOfGames--;
      game[cur][2]++;
      game[i][0]++;
    }
  }

  return false;
}

int main(){
  vector<vector<vector<int>>> games(4, vector<vector<int>>(6, vector<int>(3)));

  for(int i = 0; i < 4; i++){
    for(int j = 0; j < 6; j++){
      for(int k = 0; k < 3; k++){
        cin >> games[i][j][k];
      }
    }
  }

  for(int i = 0; i < 4; i++){
    int numOfGames = 0;

    bool ifGameCntAll5 = true;
    for(int j = 0; j < 6; j++){
      int gameCnt = 0;
      for(int k = 0; k < 3; k++)
        gameCnt += games[i][j][k];
      if(gameCnt != 5){
        ifGameCntAll5 = false;
        break;
      }
    }
    if(!ifGameCntAll5){
      cout << "0 ";
      continue;
    }
      

    if(ifPossibleGameDFS(0, 0, games[i], numOfGames))
      cout << "1 ";
    else
      cout << "0 ";
  }

  return 0;
}