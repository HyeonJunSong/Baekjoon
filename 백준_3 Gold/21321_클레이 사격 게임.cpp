#include <iostream>
#include <vector>

using namespace std;

int N;
vector<pair<int, int>> clay;
vector<int> memo;

int getAns(int visited){
  
  int i = 1;
  for(int j = 0; j < N; j++)
    if((visited & (1 << j)) > 0) i++;

  if(i == N + 1) return 0;

  vector<int> curTimes;

  int ans = 0;

  for(int j = 0; j < N; j++){
    if((visited & (1 << j)) > 0) continue;

    bool ifPossible = true;
    for(auto e: curTimes){
      if(clay[j].first % e != 0) continue;
      ifPossible = false;
      break;
    }
    if(!ifPossible) continue;
    curTimes.push_back(clay[j].first);

    if(memo[visited | (1 << j)] == -1)
      memo[visited | (1 << j)] = getAns(visited | (1 << j));
    ans = max(ans, memo[visited | ( 1 << j)] + i * clay[j].second);
  }

  return ans;
}

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  cin >> N;
  clay.assign(N, {0, 0});
  for(int i = 0; i < N; i++)
    cin >> clay[i].first >> clay[i].second;
  
  memo.assign(1 << N, -1);
  cout << getAns(0);

  return 0;
}