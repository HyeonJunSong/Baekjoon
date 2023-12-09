////231209
//9m 47s

#include <iostream>
#include <vector>

using namespace std;

int N;
vector<int> rices;
vector<vector<int>> memo;

int getMaxProfit(int st, int ed);
int main(){

  cin >> N;

  rices = vector<int>(N);
  for(int i = 0; i < N; i++)
    cin >> rices[i];
  
  memo = vector<vector<int>>(N, vector<int>(N, -1));
  cout << getMaxProfit(0, N - 1);


  return 0;
}

int getMaxProfit(int st, int ed){
  if(st == ed)
    return rices[st] * N;

  if(memo[st + 1][ed] == -1)
    memo[st + 1][ed] = getMaxProfit(st + 1, ed);
  if(memo[st][ed - 1] == -1)
    memo[st][ed - 1] = getMaxProfit(st, ed - 1);
  
  return max(memo[st + 1][ed] + (N - (ed - st + 1) + 1) * rices[st], memo[st][ed - 1] + (N - (ed - st + 1) + 1) * rices[ed]);
}