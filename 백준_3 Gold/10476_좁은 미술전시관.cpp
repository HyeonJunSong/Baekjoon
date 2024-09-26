#include <iostream>
#include <vector>

using namespace std;

int N, k;
vector<vector<int>> gallery;

vector<vector<vector<int>>> memo;

int getAns(int idx, int curLineStauts, int kLeft){

  if(idx == N) return 0;

  if(N - idx == kLeft){
    int ans = 0;
    if(curLineStauts & 1){
      int curSum = 0;
      for(int i = idx; i < N; i++)
        curSum += gallery[i][1];
      ans = max(ans, curSum);
    }
    if(curLineStauts & 2){
      int curSum = 0;
      for(int i = idx; i < N; i++)
        curSum += gallery[i][0];
      ans = max(ans, curSum);
    }
    return ans;
  }

  int ans = 0;

  if(memo[idx + 1][3][kLeft] == -1)
    memo[idx + 1][3][kLeft] = getAns(idx + 1, 3, kLeft);
  ans = max(ans, memo[idx + 1][3][kLeft] + gallery[idx][0] + gallery[idx][1]);

  if(kLeft > 0 && (curLineStauts & 1)){
    if(memo[idx + 1][1][kLeft - 1] == -1)
     memo[idx + 1][1][kLeft - 1] = getAns(idx + 1, 1, kLeft - 1);
    ans = max(ans, memo[idx + 1][1][kLeft - 1] + gallery[idx][1]);
  }

  if(kLeft > 0 && (curLineStauts & 2)){
    if(memo[idx + 1][2][kLeft - 1] == -1)
     memo[idx + 1][2][kLeft - 1] = getAns(idx + 1, 2, kLeft - 1);
    ans = max(ans, memo[idx + 1][2][kLeft - 1] + gallery[idx][0]);
  }
  return ans;
}

int main(){

  cin >> N >> k;

  gallery.assign(N, vector<int>(2, 0));
  for(int i = 0; i < N; i++)
    cin >> gallery[i][0] >> gallery[i][1];
  
  memo.assign(N + 1, vector<vector<int>>(4, vector<int>(k + 1, -1)));
  cout << getAns(0, 3, k);

  return 0;
}