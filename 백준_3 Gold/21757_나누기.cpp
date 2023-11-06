#include <iostream>
#include <vector>
#include <map>

using namespace std;

int N;
vector<int> arr;
vector<int> targetIndexes;
vector<int> targetIndexesRev;
vector<int> midIndexes;
int target;

long long getNumof(int midInd){

  int st = 0;
  int ed = targetIndexes.size() - 1;
  while(st <= ed){
    int mid = (st + ed) / 2;
    if(targetIndexes[mid] < midInd)
      st = mid + 1;
    else
      ed = mid - 1;
  }

  if(ed == -1)
    return 0LL;
  int left = ed;


  st = 0;
  ed = targetIndexesRev.size() - 1;
  while(st <= ed){
    int mid = (st + ed) / 2;
    if(targetIndexesRev[mid] > midInd + 1)
      st = mid + 1;
    else
      ed = mid - 1;
  }

  if(ed == -1)
    return 0LL;
  
  return (long long)(left + 1) * (long long)(ed + 1);
}

int main(){
  cin >> N;
  arr = vector<int>(N);
  for(int i = 0; i < N; i++)
    cin >> arr[i];

  int tot = 0;
  for(int i = 0; i < N; i++)
    tot += arr[i];
  if(tot % 4 != 0){
    cout << 0;
    return 0;
  }
  target = (int)(tot / 4);

  tot = 0;
  for(int i = 0; i < N; i++){
    tot += arr[i];
    if(tot == target)
      targetIndexes.push_back(i);
    if(tot == target * 2)
      midIndexes.push_back(i);
  }

  tot = 0;
  for(int i = N - 1; i >= 0; i--){
    tot += arr[i];
    if(tot == target)
      targetIndexesRev.push_back(i);
  }

  long long ans = 0;
  for(auto e: midIndexes){
    ans += getNumof(e);
  }

  cout << ans;
  
  return 0;
}