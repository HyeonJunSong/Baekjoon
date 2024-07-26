#include <iostream>
#include <vector>
#include <string>

using namespace std;

string str;

#define NANUM -987654321
#define NINF -2000000

vector<vector<int>> memo;

int getAns(int idx, int ifNeg){
  if(idx == str.size()) return NINF;
  if(idx == str.size() - 1){
    if(str[idx] == '+') return ifNeg ? -10 : 10;
    else return ifNeg? -1 : 1;
  }
  if(idx == str.size() - 2){
    if(str[idx] == '+' && str[idx + 1] == '-') return ifNeg ? -11 : 11;
    else return NINF;
  }

  int ans = NINF;
  if(str[idx] == '+'){
    if(idx < str.size() - 2 && str[idx + 1] == '-'){
      if(str[idx + 2] == '+'){
        if(memo[idx + 3][0] == NANUM)
          memo[idx + 3][0] = getAns(idx + 3, 0);
        
        if(ifNeg)
          ans = max(ans, -11 + memo[idx + 3][0]);
        else
          ans = max(ans, 11 + memo[idx + 3][0]);
      } else {
        if(memo[idx + 3][1] == NANUM)
          memo[idx + 3][1] = getAns(idx + 3, 1);
        
        if(ifNeg)
          ans = max(ans, -11 + memo[idx + 3][1]);
        else
          ans = max(ans, 11 + memo[idx + 3][1]);
      }
    }

    if(idx < str.size() - 1){
      if(str[idx + 1] == '+'){
        if(memo[idx + 2][0] == NANUM)
          memo[idx + 2][0] = getAns(idx + 2, 0);
        
        if(ifNeg)
          ans = max(ans, -10 + memo[idx + 2][0]);
        else
          ans = max(ans, 10 + memo[idx + 2][0]);
      } else {
        if(memo[idx + 2][1] == NANUM)
          memo[idx + 2][1] = getAns(idx + 2, 1);
        
        if(ifNeg)
          ans = max(ans, -10 + memo[idx + 2][1]);
        else
          ans = max(ans, 10 + memo[idx + 2][1]);
      }
    }
  } else {
    if(idx < str.size() - 1){
      if(str[idx + 1] == '+'){
        if(memo[idx + 2][0] == NANUM)
          memo[idx + 2][0] = getAns(idx + 2, 0);
        
        if(ifNeg)
          ans = max(ans, -1 + memo[idx + 2][0]);
        else
          ans = max(ans, 1 + memo[idx + 2][0]);
      } else {
        if(memo[idx + 2][1] == NANUM)
          memo[idx + 2][1] = getAns(idx + 2, 1);
        
        if(ifNeg)
          ans = max(ans, -1 + memo[idx + 2][1]);
        else
          ans = max(ans, 1 + memo[idx + 2][1]);
      }
    }
  }

  return ans;
}

int main(){

  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  cin >> str;

  memo = vector<vector<int>>(str.size() + 1, vector<int>(2, NANUM));
  cout << getAns(0, 0);

  return 0;
}