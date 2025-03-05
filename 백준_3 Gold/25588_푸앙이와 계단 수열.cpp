#include <iostream>
#include <vector>

using namespace std;


int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int N, K;
  cin >> N >> K;

  vector<int> nums(N);
  for(int i = 0; i < N; i++)
    cin >> nums[i];

  int curStairSize;

  vector<bool> ifErasableToR(N, false);
  for(int i = 0; i < N; i++){
    if(i > 0 && abs(nums[i - 1] - nums[i]) == 1)
      curStairSize++;
    else
      curStairSize = 1;
    
    if(curStairSize >= K)
      ifErasableToR[i - K + 1] = true;
  }

  vector<bool> ifErasableToL(N, false);
  for(int i = N - 1; i >= 0; i--){
    if(i < N - 1 && abs(nums[i] - nums[i + 1]) == 1)
      curStairSize++;
    else
      curStairSize = 1;
    
    if(curStairSize >= K)
      ifErasableToL[i + K - 1] = true;
  }

  vector<int> dpToR(N, 987654321);
  dpToR[0] = 1;
  dpToR[1] = 1;
  dpToR[2] = 1;
  if(ifErasableToR[0]) dpToR[K - 1] = 1;

  for(int i = 0; i < N; i++){
    if(i + 1 < N) dpToR[i + 1] = min(dpToR[i + 1], dpToR[i] + 1);
    if(i + 2 < N) dpToR[i + 2] = min(dpToR[i + 2], dpToR[i] + 1);
    if(i + 3 < N) dpToR[i + 3] = min(dpToR[i + 3], dpToR[i] + 1);
    if(i + 1 < N && ifErasableToR[i + 1]) dpToR[i + K] = min(dpToR[i + K], dpToR[i] + 1);
  }
 
  vector<int> dpToL(N, 987654321);
  dpToL[N - 1] = 1;
  dpToL[N - 2] = 1;
  dpToL[N - 3] = 1;
  if(ifErasableToL[N - 1]) dpToL[N - K] = 1;

  for(int i = N - 1; i >= 0; i--){
    if(i - 1 >= 0) dpToL[i - 1] = min(dpToL[i - 1], dpToL[i] + 1);
    if(i - 2 >= 0) dpToL[i - 2] = min(dpToL[i - 2], dpToL[i] + 1);
    if(i - 3 >= 0) dpToL[i - 3] = min(dpToL[i - 3], dpToL[i] + 1);
    if(i - 1 >= 0 && ifErasableToL[i - 1]) dpToL[i - K] = min(dpToL[i - K], dpToL[i] + 1);
  }

  int ans = min(dpToL[0], dpToR[N - 1]);

  for(int i = 1; i < N - 1; i++)
    ans = min(ans, dpToR[i] + dpToL[i + 1]);
  
  cout << ans;

  return 0;
}