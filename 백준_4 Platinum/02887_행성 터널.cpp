#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

bool comp(pair<int, int> a, pair<int, int> b){
  return a.second < b.second;
}

class node{
public:
  int distance;
  int index;
  int type; //x:0, y:1, z:2

  bool operator<(node b) const{
    return distance < b.distance;
  }
};

vector<int> parent;
int getRootOfTree(int ind){
  int nextInd = ind;
  while(parent[nextInd] != nextInd){
    nextInd = parent[nextInd];
  }
  parent[ind] = nextInd;
  return nextInd;
}

int main(){
  int N;
  cin >> N;
  vector<vector<pair<int, int>>> planets(3, vector<pair<int, int>>(N));

  for(int i = 0; i < N; i++){
    cin >> planets[0][i].second >> planets[1][i].second >> planets[2][i].second;
    planets[0][i].first = i;
    planets[1][i].first = i;
    planets[2][i].first = i;
  }

  if(N == 1){
    cout << 0;
    return 0;
  }
  
  sort(planets[0].begin(), planets[0].end(), comp);
  sort(planets[1].begin(), planets[1].end(), comp);
  sort(planets[2].begin(), planets[2].end(), comp);

  vector<node> distances;

  //distance[i] = planets[i + 1] - planets[i];
  vector<vector<int>> distance(3,  vector<int>(N - 1));
  for(int i = 1; i < planets[0].size(); i++){
    distance[0][i - 1] = planets[0][i].second - planets[0][i - 1].second;
    distances.push_back({distance[0][i - 1], i - 1, 0});
  }
  for(int i = 1; i < planets[1].size(); i++){
    distance[1][i - 1] = planets[1][i].second - planets[1][i - 1].second;
    distances.push_back({distance[1][i - 1], i - 1, 1});
  }
  for(int i = 1; i < planets[2].size(); i++){
    distance[2][i - 1] = planets[2][i].second - planets[2][i - 1].second;
    distances.push_back({distance[2][i - 1], i - 1, 2});
  }

  sort(distances.begin(), distances.end());
  
  //
  parent = vector<int>(N);
  for(int i = 0; i < N; i++)
    parent[i] = i;

  int minDistanceSum = 0;
  int cnt = 0;

  for(int i = 0; cnt != N - 1 && i < distances.size(); i++){

    int root1 = getRootOfTree(planets[distances[i].type][distances[i].index + 1].first);
    int root2 = getRootOfTree(planets[distances[i].type][distances[i].index].first);
    if(root1 == root2)
      continue;
    parent[root1] = root2;
    cnt++;
    
    // cout << planets[distances[i].type][distances[i].index].first << ' ' << planets[distances[i].type][distances[i].index + 1].first << ' ' << distances[i].type << endl;

    minDistanceSum += distances[i].distance;
  }

  cout << minDistanceSum;

  return 0;
}