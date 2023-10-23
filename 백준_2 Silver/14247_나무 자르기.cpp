////231022
//17m 20s

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main(){
  int n;
  cin >> n;
  vector<long long> H(n);
  for(int i = 0; i < n; i++)
    cin >> H[i];
  vector<pair<long long, int>> A(n);
  for(int i = 0; i < n; i++){
    cin >> A[i].first;
    A[i].second = i;
  }

  sort(A.begin(), A.end());

  long long ans = 0;

  for(long long i = 0; i < n; i++)
    ans += H[A[i].second] + A[i].first * i;
  
  cout << ans;

  return 0;
}