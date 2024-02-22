#include <iostream>
#include <vector>

using namespace std;

int N, M, x, y, K;
vector<vector<int>> board;
vector<vector<int>> dice;

void rollDice(int command){
  int tmp;
  switch (command){
    case 1:
      tmp = dice[0][1];
      dice[0][1] = dice[1][0];
      dice[1][0] = dice[0][3];
      dice[0][3] = dice[1][1];
      dice[1][1] = tmp;
      break;
    case 2:
      tmp = dice[0][1];
      dice[0][1] = dice[1][1];
      dice[1][1] = dice[0][3];
      dice[0][3] = dice[1][0];
      dice[1][0] = tmp;
      break;
    case 3:
      tmp = dice[0][1];
      dice[0][1] = dice[0][2];
      dice[0][2] = dice[0][3];
      dice[0][3] = dice[0][0];
      dice[0][0] = tmp;
      break;
    case 4:
      tmp = dice[0][1];
      dice[0][1] = dice[0][0];
      dice[0][0] = dice[0][3];
      dice[0][3] = dice[0][2];
      dice[0][2] = tmp;
      break;
  }
}

int main(){

  cin >> N >> M >> x >> y >> K;
  board = vector<vector<int>>(N, vector<int>(M));
  for(int i = 0; i < N; i++)
    for(int j = 0; j < M; j++)
      cin >> board[i][j];
    
  dice.push_back({0, 0, 0, 0});
  dice.push_back({0, 0});

  int command;
  for(int i = 0; i < K; i++){
    cin >> command;

    switch(command){
      case 1:
        if(y + 1 == M) continue;
        y++;
      break;
      case 2:
        if(y - 1 == -1) continue;
        y--;
      break;
      case 3:
        if(x - 1 == -1) continue;
        x--;
      break;
      case 4:
        if(x + 1 == N) continue;
        x++;
      break;
    }
    rollDice(command);

    if(board[x][y] == 0)
      board[x][y] = dice[0][3];
    else{
      dice[0][3] = board[x][y];
      board[x][y] = 0;
    }
    cout << dice[0][1] << "\n";
  }

  return 0;
}