#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#define NINF -1000000001

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int N;
  cin >> N;

  vector<pair<int, int>> spots(N);
  for(int i = 0; i < N; i++)
    cin >> spots[i].first >> spots[i].second;
  
  int st;

  int leftBottomIdx = 0;
  for(int i = 1; i < N; i++){
    if(spots[leftBottomIdx].first == spots[i].first){
      if(spots[leftBottomIdx].second > spots[i].second)
        leftBottomIdx = i;
    } else if(spots[leftBottomIdx].first > spots[i].first)
        leftBottomIdx = i;
  }

  vector<pair<int, int>> peeks;
  for(int i = 1; i < N; i++){

    if(spots[((leftBottomIdx + i - 1) + N) % N].second < 0 && spots[((leftBottomIdx + i) + N) % N].second > 0)
      st = spots[((leftBottomIdx + i) + N) % N].first;
    else if(spots[((leftBottomIdx + i - 1) + N) % N].second > 0 && spots[((leftBottomIdx + i) + N) % N].second < 0)
      peeks.emplace_back(min(st, spots[((leftBottomIdx + i) + N) % N].first), max(st, spots[((leftBottomIdx + i) + N) % N].first));
  }

  sort(peeks.begin(), peeks.end());

  int outer = 0;
  int inner = 0;

  int curEndSpot = NINF;

  for(int i = 0; i < peeks.size(); i++){
    if(i == peeks.size() - 1 || peeks[i].second < peeks[i + 1].first){
      inner++;
    }
    if(curEndSpot < peeks[i].first){
      outer++;
      curEndSpot = peeks[i].second;
    }
  }

  cout << outer << " " << inner;

  return 0;
}