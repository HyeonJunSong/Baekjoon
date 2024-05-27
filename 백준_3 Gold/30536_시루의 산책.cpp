#include <iostream>
#include <cmath>
#include <vector>
#include <queue>

using namespace std;

int main(){

  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int N, M;
  cin >> N >> M;
  vector<pair<int, int>> pillars(N);
  for(int i = 0; i < N; i++)
    cin >> pillars[i].first >> pillars[i].second;
  
  vector<int> P(M + 1);
  for(int i = 1; i <= M; i++){
    cin >> P[i];
    P[i]--;
  }
  
  vector<int> R(M + 1);
  for(int i = 0; i < M + 1; i++)
    cin >> R[i];
  

  vector<bool> ifPossible(N, true);
  for(int i = 1; i <= M; i++)
    for(int j = 0; j < N; j++)
      if(pow(pillars[P[i]].first - pillars[j].first, 2) + pow(pillars[P[i]].second - pillars[j].second, 2) <= pow(R[i], 2))
        ifPossible[j] = false;
  
  queue<int> Q;
  for(int i = 0; i < N; i++)
    if(ifPossible[i])
      Q.push(i);
  
  while(!Q.empty()){
    int cur = Q.front();
    Q.pop();

    for(int i = 0; i < N; i++){
      if(ifPossible[i]) continue;
      if(pow(pillars[cur].first - pillars[i].first, 2) + pow(pillars[cur].second - pillars[i].second, 2) <= pow(R[0], 2)){
        ifPossible[i] = true;
        Q.push(i);
      }
    }
  }

  int ans = 0;
  for(int i = 0; i < N; i++)
    if(ifPossible[i]) ans++;
  cout << ans;


  return 0;
}