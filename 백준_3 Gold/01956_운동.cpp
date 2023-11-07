////231107
//34m 25s

#include <iostream>
#include <vector>

using namespace std;

#define INF 987654321

int main(){

  int V, E;
  cin >> V >> E;

  vector<vector<int>> city(V + 1, vector<int>(V + 1, INF));
  for(int i = 0; i < E; i++){
    int a, b, c;
    cin >> a >> b >> c;

    city[a][b] = c;
  }

  for(int k = 1; k < V + 1; k++)
    for(int i = 1; i < V + 1; i++)
      for(int j = 1; j < V + 1; j++)
        city[i][j] = min(city[i][j], city[i][k] + city[k][j]);
  
  int ans = INF;
  for(int i = 1; i < V + 1; i++)
    if(ans > city[i][i])
      ans = city[i][i];
  
  if(ans == INF)
    cout << -1;
  else
    cout << ans;

  return 0;
}