#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main(){

  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  int L;
  cin >> L;

  vector<int> S(L);
  for(int i = 0; i < L; i++)
    cin >> S[i];
  
  int n;
  cin >> n;

  sort(S.begin(), S.end());

  int leftNum = -1;
  int rightNum = 987654321;

  for(int i = 0; i < L - 1; i++){
    if(S[i] < n && n < S[i + 1]){
      leftNum = S[i];
      rightNum = S[i + 1];
    }
  }

  if(leftNum == -1){
    if(n < S[0]){
      leftNum = 0;
      rightNum = S[0];
    } else{
      cout << 0;
      return 0;
    }
  }
  cout << (n - (leftNum + 1)) * ((rightNum - 1) - n + 1) + (rightNum - 1) - n;

  return 0;
}