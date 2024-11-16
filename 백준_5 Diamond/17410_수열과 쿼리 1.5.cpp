#include <iostream>
#include <vector>

using namespace std;

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  int N;
  cin >> N;

  vector<int> nums(N);
  for(int i = 0; i < N; i++)
    cin >> nums[i];
  
  

  return 0;
}