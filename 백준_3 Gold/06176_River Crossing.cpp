#include <iostream>
#include <vector>

using namespace std;

int N, M;
vector<int> M_i;

vector<int> memo;
int getAns(int cowsLeft){

  if(cowsLeft == 0) return 0;
  
  int ans = 987654321;
  for(int i = 1; i <= cowsLeft; i++){
    if(memo[cowsLeft - i] == -1)
      memo[cowsLeft - i] = getAns(cowsLeft - i);
    
    ans = min(ans, memo[cowsLeft - i] + M_i[i]);
  }

  return ans;
}

int main(){

  cin >> N >> M;
  M_i = vector<int>(N + 1);
  for(int i = 1; i <= N; i++)
    cin >> M_i[i];
  
  M_i[0] = 2 * M;
  for(int i = 1; i <= N; i++)
    M_i[i] += M_i[i - 1];

  memo = vector<int>(N + 1, -1);
  cout << getAns(N) - M;

  cout << endl;

  return 0;
}