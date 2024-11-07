#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <iterator>

using namespace std;

bool ifCCW(pair<int, int> a, pair<int, int> b){
  return (long long)(a.first) * (long long)(b.second) - (long long)a.second * (long long)b.first >= 0;
}

pair<int, int> getVector(pair<int, int> a, pair<int, int> b){
  return {b.first - a.first, b.second - a.second};
}

long long dis(pair<int, int> a, pair<int, int> b){
  return (long long)(b.first - a.first) * (long long)(b.first - a.first) + (long long)(b.second - a.second) * (long long)(b.second - a.second);
}

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  int n;
  cin >> n;

  vector<pair<int, int>> points;
  pair<int, int> point;
  set<pair<int, int>> curPoints;
  for(int i = 0; i < n; i++){
    cin >> point.first >> point.second;
    if(curPoints.find(point) != curPoints.end()) continue;
    curPoints.insert(point);
    points.push_back(point);
  }

  if(curPoints.size() == 1){
    cout << 0;
    return 0;
  }
  if(curPoints.size() == 2){
    cout << dis(*curPoints.begin(), *next(curPoints.begin()));
    return 0;
  }
  
  sort(points.begin(), points.end());

  vector<pair<int, int>> ConvexHull;
  ConvexHull.push_back(points[0]);
  ConvexHull.push_back(points[1]);
  for(int i = 2; i < points.size(); i++){
    while(ConvexHull.size() >= 2 && ifCCW(getVector(ConvexHull[ConvexHull.size() - 2], ConvexHull[ConvexHull.size() - 1]), getVector(ConvexHull[ConvexHull.size() - 1], points[i])))
      ConvexHull.pop_back();
    ConvexHull.push_back(points[i]);
  }

  sort(points.rbegin(), points.rend());
  vector<pair<int, int>> ConvexHull2;
  ConvexHull2.push_back(points[0]);
  ConvexHull2.push_back(points[1]);
  for(int i = 2; i < points.size(); i++){
    while(ConvexHull2.size() >= 2 && ifCCW(getVector(ConvexHull2[ConvexHull2.size() - 2], ConvexHull2[ConvexHull2.size() - 1]), getVector(ConvexHull2[ConvexHull2.size() - 1], points[i])))
      ConvexHull2.pop_back();
    ConvexHull2.push_back(points[i]);
  }

  for(int i = 1; i < ConvexHull2.size() - 1; i++)
    ConvexHull.push_back(ConvexHull2[i]);

  long long ans = 0;
  for(int i = 0; i < ConvexHull.size(); i++)
    for(int j = 0; j < ConvexHull.size(); j++)
      ans = max(ans, dis(ConvexHull[i], ConvexHull[j]));
  

  // int edIdx = 0;
  // pair<int, int> stVector = getVector(ConvexHull[0], ConvexHull[1]);
  // for(int i = 1; i < ConvexHull.size(); i++){
  //   if(!ifCCW(stVector, getVector(ConvexHull[i], ConvexHull[(i + 1) % ConvexHull.size()]))) continue;
  //   edIdx = i;
  //   break;
  // }

  // long long ans = dis(ConvexHull[0], ConvexHull[edIdx]);
  // for(int i = 1; i < ConvexHull.size(); i++){
  //   stVector = getVector(ConvexHull[i], ConvexHull[i + 1 % ConvexHull.size()]);
  //   while(!ifCCW(stVector, getVector(ConvexHull[edIdx], ConvexHull[(edIdx + 1) % ConvexHull.size()]))){
  //     edIdx++;
  //     edIdx %= ConvexHull.size();
  //   }    
  //   ans = max(ans, dis(ConvexHull[i], ConvexHull[edIdx]));
  // }

  cout << ans;

  return 0;
}