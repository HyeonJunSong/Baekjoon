#include <iostream>
#include <vector>

using namespace std;

int N;
vector<vector<int>> dices;

int getAns(int curNum, int idx){
  if(idx == N) return 0;
  for(int i = 0; i < 6; i++){
    if(dices[idx][i] == curNum){
      if(i == 0)
        return getAns(dices[idx][5], idx + 1) + max(max(dices[idx][1], dices[idx][2]), max(dices[idx][3], dices[idx][4]));
      else if(i == 1)
        return getAns(dices[idx][3], idx + 1) + max(max(dices[idx][0], dices[idx][2]), max(dices[idx][4], dices[idx][5]));
      else if(i == 2)
        return getAns(dices[idx][4], idx + 1) + max(max(dices[idx][0], dices[idx][1]), max(dices[idx][3], dices[idx][5]));
      else if(i == 3)
        return getAns(dices[idx][1], idx + 1) + max(max(dices[idx][0], dices[idx][2]), max(dices[idx][4], dices[idx][5]));
      else if(i == 4)
        return getAns(dices[idx][2], idx + 1) + max(max(dices[idx][0], dices[idx][1]), max(dices[idx][3], dices[idx][5]));
      else if(i == 5)
        return getAns(dices[idx][0], idx + 1) + max(max(dices[idx][1], dices[idx][2]), max(dices[idx][3], dices[idx][4]));
    }
  }
}

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  cin >> N;
  dices.assign(N, vector<int>(6));
  for(int i = 0; i < N; i++)
    for(int j = 0; j < 6; j++)
      cin >> dices[i][j];
  
  int ans = 0;
  for(int i = 1; i <= 6; i++)
    ans = max(ans, getAns(i, 0));
  
  cout << ans;

  return 0;
}