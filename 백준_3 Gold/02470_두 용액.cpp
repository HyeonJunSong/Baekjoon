#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main(){

  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int N;
  cin >> N;
  vector<int> arr(N);
  for(int i = 0; i < N; i++)
    cin >> arr[i];
  
  sort(arr.begin(), arr.end());

  int st = 0;
  int ed = arr.size() - 1;

  int minSum = 2000000001;
  int minSumSt;
  int minSumEd;

  while (st < ed){
    if(minSum > abs(arr[st] + arr[ed])){
      minSum = abs(arr[st] + arr[ed]);
      minSumSt = arr[st];
      minSumEd = arr[ed];
    }

    if(abs(arr[st + 1] + arr[ed]) > abs(arr[st] + arr[ed - 1]))
      ed -= 1;
    else
      st += 1;
  }

  cout << minSumSt << ' ' << minSumEd;

  return 0;
}