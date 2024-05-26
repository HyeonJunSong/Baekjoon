#include <iostream>
#include <vector>
#include <queue>

using namespace std;

vector<pair<pair<int, int>, pair<int, int>>> buses;

bool ifCross(int b1Idx, int b2Idx){
  if (buses[b1Idx].first.first == buses[b1Idx].second.first && buses[b2Idx].first.first == buses[b2Idx].second.first && buses[b1Idx].first.first == buses[b2Idx].first.first)
    return !( buses[b1Idx].second.second < buses[b2Idx].first.second || buses[b2Idx].second.second < buses[b1Idx].first.second);
  if (buses[b1Idx].first.second == buses[b1Idx].second.second && buses[b2Idx].first.second == buses[b2Idx].second.second && buses[b1Idx].first.second == buses[b2Idx].first.second)
    return !( buses[b1Idx].second.first < buses[b2Idx].first.first || buses[b2Idx].second.first < buses[b1Idx].first.first);
  return (buses[b1Idx].first.first <= buses[b2Idx].first.first && buses[b2Idx].first.first <= buses[b1Idx].second.first && buses[b2Idx].first.second <= buses[b1Idx].first.second && buses[b1Idx].first.second <= buses[b2Idx].second.second)
    || (buses[b2Idx].first.first <= buses[b1Idx].first.first && buses[b1Idx].first.first <= buses[b2Idx].second.first && buses[b1Idx].first.second <= buses[b2Idx].first.second && buses[b2Idx].first.second <= buses[b1Idx].second.second);
}

int main(){

  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int m, n;
  cin >> m >> n;

  int k;
  cin >> k;

  int tmp;
  buses.assign(k,{{0, 0}, {0, 0}});
  for(int i = 0; i < k; i++)
    cin >> tmp >> buses[i].first.first >> buses[i].first.second >> buses[i].second.first >> buses[i].second.second;
  
  int sx, sy, dx, dy;
  cin >> sx >> sy >> dx >> dy;

  for(int i = 0; i < k; i++){
    if(buses[i].first.first > buses[i].second.first) swap(buses[i].first.first, buses[i].second.first);
    if(buses[i].first.second > buses[i].second.second) swap(buses[i].first.second, buses[i].second.second);
  }

  vector<vector<int>> graph(k);
  for(int i = 0; i < k - 1; i++){
    for(int j = i + 1; j < k; j++){
      if(ifCross(i, j)){
        graph[i].push_back(j);
        graph[j].push_back(i);
      }
    }
  }

  vector<bool> ifEnd(k, false);
  for(int i = 0; i < k; i++)
      if(buses[i].first.second <= dy && dy <= buses[i].second.second && buses[i].first.first <= dx && dx <= buses[i].second.first)
        ifEnd[i] = true;

  queue<pair<int, int>> q;
  for(int i = 0; i < k; i++)
      if(buses[i].first.second <= sy && sy <= buses[i].second.second && buses[i].first.first <= sx && sx <= buses[i].second.first)
        q.push({i, 1});

  vector<bool> visited(k, false);
  while(!q.empty()){
    pair<int, int> cur = q.front();
    q.pop();
    if(ifEnd[cur.first]){
      cout << cur.second;
      return 0;
    }
    
    // if(visited[cur.first]) continue;
    visited[cur.first] = true;
    
    for(auto e : graph[cur.first]){
      if(visited[e]) continue;
      visited[e] = true;
      q.push({e, cur.second + 1});
    }
  }

  return 0;
}
