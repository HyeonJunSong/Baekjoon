#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int N;
vector<pair<int, int>> spots;

bool ifSpotExists(pair<int, int> target){
  int st = 0;
  int ed = N - 1;

  while(st <= ed){
    int mid = (st + ed) / 2;

    if(spots[mid] < target)
      st = mid + 1;
    else if(spots[mid] > target)
      ed = mid - 1;
    else
      return true;
  }

  return false;
}

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  cin >> N;
  int A, B;
  cin >> A >> B;

  spots = vector<pair<int, int>>(N);
  for(int i = 0; i < N; i++)
    cin >> spots[i].first >> spots[i].second;

  sort(spots.begin(), spots.end());
  
  int cnt = 0;
  for(int i = 0; i < N; i++){
    if(ifSpotExists({spots[i].first + A, spots[i].second})
    && ifSpotExists({spots[i].first, spots[i].second + B})
    && ifSpotExists({spots[i].first + A, spots[i].second + B})
    )
    cnt++;
  }
  
  cout << cnt;

  return 0;
}