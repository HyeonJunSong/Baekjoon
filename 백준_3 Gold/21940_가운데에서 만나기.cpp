////231023
//17m 21s

#include <iostream>
#include <vector>

using namespace std;

#define INF 987654321

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int N, M;
  cin >> N >> M;
  vector<vector<int>> city(N + 1, vector<int>(N + 1, INF));
  for(int i = 0; i < M; i++){
    int st, ed, dur;
    cin >> st >> ed >> dur;
    city[st][ed] = dur;
  }
  for(int i = 1; i < N + 1; i++)
    city[i][i] = 0;

  for(int k = 1; k <= N; k++)
    for(int i = 1; i <= N; i++)
      for(int j = 1; j <= N; j++)
        city[i][j] = min(city[i][k] + city[k][j], city[i][j]);
  
  int K;
  cin >> K;
  vector<int> friends(K);
  for(int i = 0; i < K; i++)
    cin >> friends[i];
  
  int minVal = INF;
  vector<int> ansCity;
  
  for(int i = 1; i < N + 1; i++){
    int curMaxVal = 0;
    for(auto e : friends)
      if(curMaxVal < city[e][i] + city[i][e])
        curMaxVal = city[e][i] + city[i][e];
    
    if(minVal > curMaxVal){
      minVal = curMaxVal;
      ansCity.clear();
      ansCity.push_back(i);
    }
    else if(minVal == curMaxVal)
      ansCity.push_back(i);
  }

  for(auto e : ansCity)
    cout << e << ' ';


  return 0;
}