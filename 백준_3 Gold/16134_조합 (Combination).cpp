#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

#define M 1000000007
#define LL long long

LL invol2(LL num, LL invNum);

int main(){

  LL N, R;
  cin >> N >> R;

  //분자 구하기
  LL ans = 1;
  for(LL i = N; i > N - R; i--){
    ans *= i;
    ans %= M;
  }

  //R팩토리얼 구하기
  LL Rfact = 1;
  for(LL i = 1; i <= R; i++){
    Rfact *= i;
    Rfact %= M;
  }

  //R팩토리얼의 1 000 000 005 구하기
  LL curInvol = 1000000005;
  while(curInvol > 0){
    ans *= invol2(Rfact, (LL)(floor(log2(curInvol))));
    ans %= M;
    curInvol -= (LL)(pow(2, floor(log2(curInvol))));
  }

  cout << ans;

  return 0;
}

vector<LL> memo(30, -1);

LL invol2(LL num, LL invNum){

  if(invNum == 0)
    return num;

  
  if(memo[invNum - 1] == -1)
    memo[invNum - 1] = invol2(num, invNum - 1);

  return (memo[invNum - 1] * memo[invNum - 1]) % M;
}