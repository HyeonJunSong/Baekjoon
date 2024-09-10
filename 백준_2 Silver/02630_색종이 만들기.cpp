#include <iostream>
#include <vector>

using namespace std;

vector<vector<int>> board;

vector<int> ans(2, 0);
void getAns(int I, int J, int N){
  bool ifAllSame = true;
  for(int i = I; i < I + N; i++){
    for(int j = J; j < J + N; j++){
      if(board[I][J] != board[i][j]){
        ifAllSame = false;
        break;
      }
    }
  }

  if(ifAllSame){
    ans[board[I][J]]++;
    return;
  }
  getAns(I, J, N / 2);
  getAns(I + N / 2, J, N / 2);
  getAns(I, J + N / 2, N / 2);
  getAns(I + N / 2, J + N / 2, N / 2);  
  return;
}

int main(){
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  int N;
  cin >> N;
  board.assign(N, vector<int>(N, 0));
  for(int i = 0; i < N; i++)
    for(int j = 0; j < N; j++)
      cin >> board[i][j];

  getAns(0, 0, N);
  cout << ans[0] << "\n" << ans[1];

  return 0;
}