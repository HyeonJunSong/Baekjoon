#include <iostream>
#include <vector>
#include <set>

using namespace std;

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int N;
  cin >> N;
  vector<int> towers(N);
  for(int i = 0; i < N; i++)
    cin >> towers[i];

  int Diameter = 0;
  for(int i = 0; i < N; i++)
    Diameter += towers[i];
  
  Diameter /= 2;
  
  int ans = 0;

  set<int> clockWise;
  int accumSum = 0;
  for(int i = 0; i < N; i++){
    accumSum -= towers[i];
    clockWise.insert(accumSum);
  }
  for(int i = 0; i < N; i++){
    accumSum -= towers[i];
    clockWise.insert(accumSum);
  }

  accumSum = 0;
  for(int i = 0; i < N; i++){
    accumSum -= towers[i];
    ans = max(ans, accumSum - *clockWise.lower_bound(-Diameter + accumSum));
  }

  set<int> antiClockWise;
  accumSum = 0;
  for(int i = N - 1; i >= 0; i--){
    accumSum -= towers[i];
    antiClockWise.insert(accumSum);
  }
  for(int i = N - 1; i >= 0; i--){
    accumSum -= towers[i];
    antiClockWise.insert(accumSum);
  }

  accumSum = 0;
  for(int i = N - 1; i >= 0; i--){
    accumSum -= towers[i];
    ans = max(ans, accumSum - *antiClockWise.lower_bound(-Diameter + accumSum));
  }

  cout << ans;

  return 0;
}