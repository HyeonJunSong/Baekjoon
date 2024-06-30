#include <iostream>
#include <vector>

using namespace std;

#define ll long long

vector<vector<vector<int>>> willshi = {
  {
    {1}
  },
  {
    {1, 1},
    {1, -1},
  },
  {
    {1, 1, 1, 1},
    {1, -1, 1, -1},
    {1, 1, -1, -1},
    {1, -1, -1, 1},
  }
};

int getAns(int N, ll R, ll S, ll E, ll curSize){
  if(N <= 2){
    int ans = 0;
    for(int i = S; i <= E; i++)
      ans += willshi[N][R][i];
    return ans;
  }

  curSize >>= 1;
  if(R < curSize){
    if(E < curSize)
      return getAns(N - 1, R, S, E, curSize);
    else if(curSize <= S)
      return getAns(N - 1, R, S - curSize, E - curSize, curSize);
    else
      return getAns(N - 1, R, S, curSize - 1, curSize) + getAns(N - 1, R, 0, E - curSize, curSize);
  } else {
    if(E < curSize)
      return getAns(N - 1, R - curSize, S, E, curSize);
    else if(curSize <= S)
      return -1 * getAns(N - 1, R - curSize, S - curSize, E - curSize, curSize);
    else
      return getAns(N - 1, R - curSize, S, curSize - 1, curSize) - getAns(N - 1, R - curSize, 0, E - curSize, curSize);
  }
}

int main(){

  int N;
  ll R, S, E;
  while(true){
    cin >> N >> R >> S >> E;
    if(N == -1) break;
    cout << getAns(N, R, S, E, (1LL << N)) << "\n";
  }

  return 0;
}