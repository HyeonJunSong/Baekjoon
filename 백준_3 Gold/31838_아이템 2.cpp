#include <iostream>
#include <vector>
#include <climits>

using namespace std;

#define ll long long
#define NINF INT64_MIN

int N, K;

vector<vector<ll>> memo;
vector<ll> accumSum;
ll getAns(int idx, int ifOnePossible){
  if(idx > N) return 0;

  ll ans = NINF;

  //안먹는 경우
  if(memo[idx + 1][0] == NINF)
    memo[idx + 1][0] = getAns(idx + 1, 0);
  ans = max(ans, memo[idx + 1][0]);

  if(ifOnePossible){
    //한개만 더 먹을 수 있을 때

    if(memo[idx + 1][1] == NINF)
      memo[idx + 1][1] = getAns(idx + 1, 1);
    ans = max(ans, memo[idx + 1][1] + accumSum[idx] - accumSum[idx - 1]);
  } else {
    //집게로 먹어야 할 때
    
    if(memo[idx + K][1] == NINF)
      memo[idx + K][1] = getAns(idx + K, 1);
    ans = max(ans, memo[idx + K][1] + accumSum[idx + K - 1] - accumSum[idx - 1]);
  }
  
  return ans;
}

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  cin >> N >> K;
  accumSum.assign(N + K + 1 , 0);
  for(int i = 1; i <= N; i++)
    cin >> accumSum[i];
  
  for(int i = 1; i < accumSum.size(); i++)
    accumSum[i] += accumSum[i - 1];
  
  memo.assign(N + K + 1, vector<ll>(2, NINF));
  
  cout << getAns(1, 1);

  return 0;
}
