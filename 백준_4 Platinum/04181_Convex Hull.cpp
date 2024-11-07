#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#define ll long long

bool ifCCW(pair<ll, ll> v1, pair<ll, ll> v2){
  return v1.first * v2.second - v1.second * v2.first >= 0;
}

pair<ll, ll> getVector(pair<ll, ll> a, pair<ll, ll> b){
  return {b.first - a.first, b.second - a.second};
}

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  int n;
  cin >> n;
  vector<pair<ll, ll>> points;
  for(int i = 0; i < n; i++){
    ll x, y;
    char ifIn;
    cin >> x >> y >> ifIn;
    if(ifIn == 'N') continue;
    points.push_back({x, y});
  }
  sort(points.begin(), points.end());

  vector<pair<ll, ll>> convexHull;
  convexHull.push_back(points[0]);
  convexHull.push_back(points[1]);

  for(int i = 2; i < points.size(); i++){
    while(!ifCCW(getVector(convexHull[convexHull.size() - 2], convexHull[convexHull.size() - 1]), getVector(convexHull[convexHull.size() - 1], points[i])))
      convexHull.pop_back();
    convexHull.push_back(points[i]);
  }

  sort(points.rbegin(), points.rend());
  for(int i = 1; i < points.size(); i++){
    while(!ifCCW(getVector(convexHull[convexHull.size() - 2], convexHull[convexHull.size() - 1]), getVector(convexHull[convexHull.size() - 1], points[i])))
      convexHull.pop_back();
    convexHull.push_back(points[i]);
  }
  convexHull.pop_back();

  cout << convexHull.size() << '\n';
  for(auto e: convexHull)
    cout << e.first << " " << e.second << '\n';




  return 0;
}