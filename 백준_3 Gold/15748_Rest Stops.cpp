#include <iostream>
#include <vector>

using namespace std;

#define ll long long

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  int L, N;
  ll rF, rB;
  cin >> L >> N >> rF >> rB;

  vector<pair<ll, ll>> restStops(N + 1, {0, 0});
  for(int i = 1; i <= N; i++)
    cin >> restStops[i].first >> restStops[i].second;
  
  vector<int> nextStop(N + 1);
  nextStop[N] = N;
  for(int i = N - 1; i >= 0; i--){
    if(restStops[nextStop[i + 1]].second <= restStops[i + 1].second)
      nextStop[i] = i + 1;
    else
      nextStop[i] = nextStop[i + 1];
  }

  ll ans = 0;
  int curPos = 0;
  while(curPos != N){
    ans += (((restStops[nextStop[curPos]].first - restStops[curPos].first) * rF) - ((restStops[nextStop[curPos]].first - restStops[curPos].first) * rB)) * restStops[nextStop[curPos]].second;
    curPos = nextStop[curPos];
  }
  cout << ans;


  return 0;
}