#include <iostream>
#include <vector>

using namespace std;

int main(){

  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int N, K, B;
  cin >> N >> K >> B;
  vector<bool> broken(N, false);
  for(int i = 0; i < B; i++){
    int brokenNum;
    cin >> brokenNum;
    brokenNum--;
    broken[brokenNum] = true;
  }

  //첫 K개 중 망가진거 개수 구하기
  int curBrokenNum = 0;
  for(int i = 0; i < K; i++)
    if(broken[i])
      curBrokenNum++;
  
  //그 뒤로 탐색
  int ans = curBrokenNum;
  for(int i = K; i < N; i++){
    if(broken[i - K])
      curBrokenNum--;
    if(broken[i])
      curBrokenNum++;
    
    ans = min(ans, curBrokenNum);
  }

  cout << ans;

  return 0;
}