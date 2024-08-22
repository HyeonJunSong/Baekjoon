#include <iostream>
#include <vector>

using namespace std;

int N, V;
vector<int> interest;

int ans;

void getAns(int idx, int minInterest, int maxInterest, int curAns){
  if(curAns >= ans) return;
  if(maxInterest - minInterest >= V){
    ans = min(ans, curAns);
    return;
  }
  if(idx == N){
    return;
  }
  int curMinInterest = min(minInterest, interest[idx]);
  int curMaxInterest = max(maxInterest, interest[idx]);

  getAns(idx + 1, curMinInterest, curMaxInterest, curAns + 1);

  if(idx < N - 2)
    getAns(idx + 2, curMinInterest, curMaxInterest, curAns + 1);

  return;
}

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  cin >> N >> V;
  interest.assign(N, 0);
  for(int i = 0; i < N; i++)
    cin >> interest[i];
  
  int maxInterest = interest[0];
  int minInterest = interest[0];
  for(int i = 1; i < N; i++){
    maxInterest = max(maxInterest, interest[i]);
    minInterest = min(minInterest, interest[i]);
  }
  if(maxInterest - minInterest < V){
    cout << N;
    return 0;
  }

  ans = N;
  getAns(0, interest[0], interest[0], 0);
  cout << ans;

  return 0;
}