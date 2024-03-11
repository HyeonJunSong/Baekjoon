#include <iostream>
#include <vector>

using namespace std;

//board : 0 : 블럭 없음
//        1 : 블럭 있음
//        2 : 블럭 있고, 오른쪽에 연결된 블럭도 있음
//        3 : 블럭 있고, 왼쪽에 연결된 블럭도 있음

//block : 1 : 1 x 1
//        2 : 2 x 1 (세로 직사각형)
//        3 : 1 x 2 (가로 직사각형)

int putBlock(vector<vector<int>>& board, int I, int J, int block){

  //장애물 만날때까지 내리기
  switch (block){
    case 1:
      for(int i = I; i < 6; i++){
        if(i < 5 && board[i + 1][J] == 0) continue;
        board[i][J] = 1;
        break;
      }
      break;
    case 2:
      for(int i = I + 1; i < 6; i++){
        if(i < 5 && board[i + 1][J] == 0) continue;
        board[i - 1][J] = 1;
        board[i][J] = 1;
        break;
      }
      break;
    case 3:
      for(int i = I; i < 6; i++){
        if(i < 5 && board[i + 1][J] == 0 && board[i + 1][J + 1] == 0) continue;
        board[i][J] = 2;
        board[i][J + 1] = 3;
        break;
      }
      break;
  }

  int score = 0;
  //부수기
  while(true){
    bool ifDestroied = false;
  
    for(int i = 5; i > 1; i--){

      bool ifFull = true;
      for(int j = 0; j < 4; j++){
        if(board[i][j] != 0) continue;
        ifFull = false;
        break;
      }

      if(!ifFull) continue;

      for(int j = 0; j < 4; j++)
        board[i][j] = 0;
      score++;
      ifDestroied = true;
    }

    //떨어트리기
    for(int i2 = 5; i2 >= 0; i2--){
      for(int j = 0; j < 4; j++){
        switch(board[i2][j]){
          case 0:
          case 3:
            break;
          case 1:
            for(int i3 = i2; i3 < 6; i3++){
              if(i3 < 5 && board[i3 + 1][j] == 0) continue;
              board[i2][j] = 0;
              board[i3][j] = 1;
              break;
            }
            break;
          case 2:
            for(int i3 = i2; i3 < 6; i3++){
              if(i3 < 5 && board[i3 + 1][j] == 0 && board[i3 + 1][j + 1] == 0) continue;
              board[i2][j] = 0;
              board[i3][j] = 2;
              board[i2][j + 1] = 0;
              board[i3][j + 1] = 3;
              break;
            }
            break;
        }
      }
    }

    if(!ifDestroied) break;
  }

  //연한부분
  if(board[0][0] != 0 || board[0][1] != 0 || board[0][2] != 0 || board[0][3] != 0){
    for(int i = 3; i >= 0; i--)
      for(int j = 0; j < 4; j++)
        board[i + 2][j] = board[i][j];

    for(int i = 0; i < 2; i++)
      for(int j = 0; j < 4; j++)
        board[i][j] = 0;
  } else if(board[1][0] != 0 || board[1][1] != 0 || board[1][2] != 0 || board[1][3] != 0){
    for(int i = 4; i >= 0; i--)
      for(int j = 0; j < 4; j++)
        board[i + 1][j] = board[i][j];
  }

  return score;
}

int main(){

  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int N;
  cin >> N;

  vector<vector<int>> green(6, vector<int>(4, 0));
  vector<vector<int>> blue(6, vector<int>(4, 0));

  int totScore = 0;
  for(int i = 0; i < N; i++){
    int t, x, y;
    cin >> t >> x >> y;

    switch(t){
      case 1:
        totScore += putBlock(green, 0, y, 1);
        totScore += putBlock(blue, 0, x, 1);
        break;
      case 2:
        totScore += putBlock(green, 0, y, 3);
        totScore += putBlock(blue, 0, x, 2);
        break;
      case 3:
        totScore += putBlock(green, 0, y, 2);
        totScore += putBlock(blue, 0, x, 3);
        break;
    }
  }

  int totBlocks = 0;
  for(int i = 2; i < 6; i++){
    for(int j = 0; j < 4; j++){
      if(green[i][j] != 0)
        totBlocks++;
      if(blue[i][j] != 0)
        totBlocks++;
    }
  }
  cout << totScore << "\n" << totBlocks;

  return 0;
}