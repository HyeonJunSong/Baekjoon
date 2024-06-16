#include <iostream>
#include <vector>
#include <string>

using namespace std;

string A;
string B;

vector<vector<int>> memo;

int getAns(int idx1, int idx2){
  if(idx1 == A.size()) return B.size() - idx2;
  if(idx2 == B.size()) return A.size() - idx1;

  if(A[idx1] == B[idx2]){
    if(memo[idx1 + 1][idx2 + 1] == -1)
      memo[idx1 + 1][idx2 + 1] = getAns(idx1 + 1, idx2 + 1);
    return memo[idx1 + 1][idx2 + 1] + 1;
  } else {
    if(memo[idx1 + 1][idx2] == -1)
      memo[idx1 + 1][idx2] = getAns(idx1 + 1, idx2);
    if(memo[idx1][idx2 + 1] == -1)
      memo[idx1][idx2 + 1] = getAns(idx1, idx2 + 1);

    return min(memo[idx1 + 1][idx2], memo[idx1][idx2 + 1]) + 1;
  }
}

int main(){

  cin >> A;
  cin >> B;

  memo = vector<vector<int>>(A.size() + 1, vector<int>(B.size() + 1, -1));
  cout << getAns(0, 0);

  return 0;
}