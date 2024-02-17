#include <iostream>
#include <vector>

using namespace std;

#define LL long long

int main(){

  LL N;
  cin >> N;
  vector<LL> arr(N);
  for(int i = 0; i < N; i++)
    cin >> arr[i];
  
  LL ans = N;
  LL curAscCnt = 1;
  for(int i = 1; i < N; i++){
    if(arr[i - 1] < arr[i]){
      curAscCnt++;
    } else {
      if(curAscCnt >= 2)
        ans += curAscCnt * (curAscCnt - 1) / 2;
      curAscCnt = 1;
    }
  }

  if(curAscCnt >= 2)
    ans += curAscCnt * (curAscCnt - 1) / 2;
  curAscCnt = 1;

  cout << ans;

  return 0;
}