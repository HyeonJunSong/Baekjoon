#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
int N;
vector<pair<int, int>> points;

bool comp(pair<int, int> a, pair<int, int> b){
  if(a.first == b.first)
    return a.second > b.second;
  return a.first < b.first;
}

//{영역 개수, 다음 인덱스}
pair<int, int> getAns(int curIdx){

  // if(points[curIdx].second <= points[curIdx + 1].first) return {1, curIdx + 1};

  int ans = 0;
  int nextI = curIdx + 1;

  int curEndPoint = points[curIdx].first;
  while(nextI < N && points[nextI].second <= points[curIdx].second){
    if(points[nextI].first == curEndPoint)
      curEndPoint = points[nextI].second;

    pair<int, int> res = getAns(nextI);
    ans += res.first;
    nextI = res.second;
  }

  if(curEndPoint == points[curIdx].second)
    ans += 2;
  else
    ans += 1;
  return {ans, nextI};
}

int main(){

  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  cin >> N;
  int x, r;
  points = vector<pair<int, int>>(N);
  for(int i = 0; i < N; i++){
    cin >> x >> r;
    points[i] = {x - r, x + r};
  }
  sort(points.begin(), points.end(), comp);

  int ans = 1;
  int curI = 0;
  while(curI < N){
    pair<int, int> res = getAns(curI);
    ans += res.first;
    curI = res.second;
  }

  cout << ans;

  return 0;
}