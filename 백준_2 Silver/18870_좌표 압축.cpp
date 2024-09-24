#include <iostream>
#include <vector>
#include <map>

using namespace std;

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);
  int N;
  cin >> N;
  vector<int> nums(N);
  for(int i = 0; i < N; i++)
    cin >>  nums[i];
  
  map<int, int> numMap;
  for(int i = 0; i < N; i++)
    numMap[nums[i]] = 0;
  
  int mapSize = 0;
  for(auto e: numMap)
    numMap[e.first] = mapSize++;
  
  for(int i = 0; i < N; i++)
    cout << numMap[nums[i]] << " ";

  return 0;
}