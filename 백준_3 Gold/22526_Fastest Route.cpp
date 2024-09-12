#include <iostream>
#include <vector>

using namespace std;

int N;
vector<vector<int>> T;
vector<int> memo;

int getAns(int curCleared){
  if(curCleared == ((1 << N) - 1)) return 0;

  int ans = 987654321;
  for(int i = 0; i < N; i++){
    if((1 << i) & curCleared) continue;

    int curClearMin = T[i][0];
    for(int j = 0; j < N; j++){
      if(!((1 << j) & curCleared)) continue;
      curClearMin = min(curClearMin, T[i][j + 1]);
    }

    if(memo[curCleared | (1 << i)] == -1)
      memo[curCleared | (1 << i)] = getAns(curCleared | (1 << i));
    ans = min(ans, memo[curCleared | (1 << i)] + curClearMin);
  }

  return ans;
}

int testCase(){
  cin >> N;
  if(N == 0) return 1;

  T.assign(N, vector<int>(N + 1));
  for(int i = 0; i < N; i++)
    for(int j = 0; j < N + 1; j++)
      cin >> T[i][j];

  memo.assign(1 << N, -1);
  cout << getAns(0) << "\n";

  return 0;
}

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  while(!testCase());

  return 0;
}
