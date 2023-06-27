////230627
//14m47s

#include <iostream>
#include <vector>

using namespace std;

vector<vector<char>> star;

void saveStar(int I, int J, int N);
void saveBlank(int I, int J, int N);
void printStar(int N);

int main(){
  ios_base::sync_with_stdio(false);
  cout.tie(NULL);

  int N;
  cin >> N;

  star = vector<vector<char>>(N, vector<char>(N));

  saveStar(0, 0, N);
  printStar(N);

  return 0;
}

void saveStar(int I, int J, int N){

  //기저
  if(N == 3){
    star[I + 0][J + 0] = '*';
    star[I + 0][J + 1] = '*';
    star[I + 0][J + 2] = '*';
    star[I + 1][J + 0] = '*';
    star[I + 1][J + 1] = ' ';
    star[I + 1][J + 2] = '*';
    star[I + 2][J + 0] = '*';
    star[I + 2][J + 1] = '*';
    star[I + 2][J + 2] = '*';
    return;
  }
  
  //재귀
  saveStar(I + 0 * N / 3, J + 0 * N / 3, N / 3);
  saveStar(I + 0 * N / 3, J + 1 * N / 3, N / 3);
  saveStar(I + 0 * N / 3, J + 2 * N / 3, N / 3);
  saveStar(I + 1 * N / 3, J + 0 * N / 3, N / 3);
  saveBlank(I + 1 * N / 3, J + 1 * N / 3, N / 3);
  saveStar(I + 1 * N / 3, J + 2 * N / 3, N / 3);
  saveStar(I + 2 * N / 3, J + 0 * N / 3, N / 3);
  saveStar(I + 2 * N / 3, J + 1 * N / 3, N / 3);
  saveStar(I + 2 * N / 3, J + 2 * N / 3, N / 3);

  //리턴
}
void saveBlank(int I, int J, int N){
  for(int i = 0; i < N; i++)
    for(int j = 0; j < N; j++)
      star[I + i][J + j] = ' ';
}

void printStar(int N){
  for(int i = 0; i < N; cout << '\n' && i++)
    for(int j = 0; j < N; j++)
      cout << star[i][j];
}