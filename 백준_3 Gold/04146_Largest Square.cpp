#include <iostream>
#include <vector>

using namespace std;


void testCase(){

  int N, W, L;
  cin >> N >> W >> L;
  vector<vector<int>> accumSum;
  accumSum.assign(N, vector<int>(N, 0));
  for(int i = 0; i < W; i++){
    int I, J;
    cin >> I >> J;
    I--;J--;
    accumSum[I][J]++;
  }

  for(int j = 1; j < N; j++)
      accumSum[0][j] += accumSum[0][j - 1];
  
  for(int i = 1; i < N; i++){
    accumSum[i][0] += accumSum[i - 1][0];
    for(int j = 1; j < N; j++)
      accumSum[i][j] += accumSum[i - 1][j] + accumSum[i][j - 1] - accumSum[i - 1][j - 1];
  }

  int st = 1;
  int ed = N;

  while(st <= ed){
    int mid = (st + ed) / 2;

    bool ifPossible = false;
    for(int i = 0; i <= N - mid; i++){
      for(int j = 0; j <= N - mid; j++){
        if(accumSum[i + mid - 1][j + mid - 1]
         -(i == 0 ? 0 : accumSum[i - 1][j + mid - 1])
         -(j == 0 ? 0 : accumSum[i + mid - 1][j - 1])
         + ((i == 0 | j == 0) ? 0 : accumSum[i - 1][j - 1]) <= L){
          int temp = 
          ifPossible = true;
          break;
         }
      }
      if(ifPossible) break;
    }

    if(ifPossible)
      st = mid + 1;
    else
      ed = mid - 1;
  }

  cout << ed * ed << "\n";
}

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  int Z;
  cin >> Z;
  for(int i = 0; i < Z; i++) testCase();

  return 0;
}