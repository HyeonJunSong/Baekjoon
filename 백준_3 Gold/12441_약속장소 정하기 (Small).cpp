////231031
//31m 04s

#include <iostream>
#include <vector>

using namespace std;

#define LL long long
#define INF 2147483648

LL testCase(){

  int N, P, M;
  cin >> N >> P >> M;

  vector<pair<int, int>> friends(P);
  for(int i = 0; i < P; i++)
    cin >> friends[i].first >> friends[i].second;
  
  vector<vector<LL>> city(N + 1, vector<LL>(N + 1, INF));

  for(int i = 0; i < M; i++){
    int D, L;
    cin >> D >> L;
    int prev, cur;
    cin >> prev;
    for(int j = 1; j < L; j++){
      cin >> cur;
      city[prev][cur] = D;
      city[cur][prev] = D;

      prev = cur;
    }
  }

  for(int i = 1; i < N + 1; i++)
    city[i][i] = 0;

  for(int k = 1; k < N + 1; k++)
    for(int i = 1; i < N + 1; i++)
      for(int j = 1; j < N + 1; j++)
        city[i][j] = min(city[i][j], city[i][k] + city[k][j]);
  

  LL minTime = INF;

  for(int i = 1; i < N + 1; i++){
    LL curTime = 0;

    for(auto f : friends){
      if(curTime < city[f.first][i] * f.second)
        curTime = city[f.first][i] * f.second;
    }
    if(minTime > curTime)
      minTime = curTime;
  }

  if(minTime == INF)
    return -1;
  else
    return minTime;
}

int main(){

  int T;
  cin >> T;
  for(int i = 0; i < T; i++){
    cout << "Case #" << i + 1 << ": " << testCase() << "\n";
  }

  return 0;
}