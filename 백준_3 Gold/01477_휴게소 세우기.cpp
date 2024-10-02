#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

int N, M, L;
vector<int> stops;

bool ifPossible(int val){
  int curMoreStopsCnt = 0;
  for(int i = 0; i < N - 1; i++)
    curMoreStopsCnt += (int)ceil((float)(stops[i + 1] - stops[i]) / (float)val) - 1;
  return curMoreStopsCnt <= M;
} 

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  cin >> N >> M >> L;


  stops.assign(N, 0);
  for(int i = 0; i < N; i++)
    cin >> stops[i];
  N += 2;
  stops.push_back(0);
  stops.push_back(L);
  sort(stops.begin(), stops.end());
  
  int st = 1;
  int ed = L;
  while(st <= ed){
    int mid = (st + ed) / 2;

    if(ifPossible(mid))
      ed = mid - 1;
    else
      st = mid + 1;
  }

  cout << st;

  return 0;
}