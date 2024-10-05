#include <iostream>
#include <string>
#include <set>
#include <vector>

using namespace std;

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  vector<set<int>> locOfNum(10);
  int N, K;
  cin >> N >> K;
  string inp;
  cin >> inp;

  for(int i = 0; i < N; i++)
    locOfNum[inp[i] - '0'].insert(i);
  
  int idx = 0;
  while(idx < N){
    if(N - idx == K) break;
    for(int i = 9; i >= 0; i--){
      if((locOfNum[i].lower_bound(idx) == locOfNum[i].end()) || (*locOfNum[i].lower_bound(idx) - idx > K)) continue;
      cout << i;
      K -= *locOfNum[i].lower_bound(idx) - idx;
      idx = *locOfNum[i].lower_bound(idx) + 1;
      break;
    }
  }

  return 0;
}