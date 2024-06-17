#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

vector<bool> ifPrime;
vector<int> primeAccum;
void initIfPrime(){
  ifPrime = vector<bool>(2001, false);
  for(int i = 2; i <= 2000; i++){
    bool curIfPrime = true;
    for(int j = 2; j <= (int)(sqrt(i)); j++){
      if(i % j == 0){
        curIfPrime = false;
        break;
      }
    }
    ifPrime[i] = curIfPrime;
  }

  primeAccum = vector<int>(2001, 0);
  for(int i = 1; i <= 2000; i++)
    primeAccum[i] = primeAccum[i - 1] + (ifPrime[i] ? 1 : 0);
}

int A, B;

vector<vector<vector<int>>> memo;

vector<int> getAns(int turn, int bellCnt){

  if(B - bellCnt <= A){
    vector<int> ans(2, 0);
    ans[turn] = primeAccum[B] - primeAccum[bellCnt];
    return ans;
  }

  vector<int> ans(2);
  if(memo[(turn + 1) % 2][bellCnt + 1][0] == -1)
    memo[(turn + 1) % 2][bellCnt + 1] = getAns((turn + 1) % 2, bellCnt + 1);
  ans = memo[(turn + 1) % 2][bellCnt + 1];
  ans[turn] += primeAccum[bellCnt + 1] - primeAccum[bellCnt];


  for(int i = 2; i <= A; i++){
    if(bellCnt + i > B) break;
    if(memo[(turn + 1) % 2][bellCnt + i][0] == -1)
      memo[(turn + 1) % 2][bellCnt + i] = getAns((turn + 1) % 2, bellCnt + i);

    if(ans[turn] < memo[(turn + 1) % 2][bellCnt + i][turn] + primeAccum[bellCnt + i] - primeAccum[bellCnt]){
      ans = memo[(turn + 1) % 2][bellCnt + i];
      ans[turn] += primeAccum[bellCnt + i] - primeAccum[bellCnt];
    }
  }

  return ans;
}

void testCase(){
  cin >> A >> B;
  memo = vector<vector<vector<int>>>(2, vector<vector<int>>(4001, vector<int>(2, -1)));
  vector<int> ans = getAns(0, 0);
  if(ans[0] > ans[1]) cout << "kuro\n";
  else if(ans[0] < ans[1]) cout << "siro\n";
  else cout << "draw\n";
}

int main(){

  initIfPrime();

  int T;
  cin >> T;
  for(int t = 0; t < T; t++) testCase();

  return 0;
}