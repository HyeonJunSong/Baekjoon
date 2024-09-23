#include <iostream>
#include <vector>
#include <climits>

using namespace std;

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  int N, M;
  cin >> N >> M;
  vector<int> roomVals(N * M);
  for(int i = 0; i < N; i++)
    for(int j = 0; j < M; j++)
      cin >> roomVals[i * M + j];
  
  pair<int, int> lineSt, lineEd;
  cin >> lineSt.first >> lineSt.second >> lineEd.first >> lineEd.second;
  if(lineSt.first > lineEd.first || lineSt.second > lineEd.second) swap(lineSt, lineEd);

  vector<vector<int>> graph(N * M);
  for(int i = 0; i < N; i++){
    for(int j = 0; j < M; j++){
      if(i + 1 < N && (lineSt.first != lineEd.first || i != lineSt.first - 1 || !(lineSt.second <= j && j < lineEd.second) ))
        graph[i * M + j].push_back((i + 1) * M + j);
      if(j + 1 < M && (lineSt.second != lineEd.second || j != lineSt.second - 1 || !(lineSt.first <= i && i < lineEd.first) ))
        graph[i * M + j].push_back(i * M + (j + 1));
    }
  }

  vector<int> maxVal(N * M, INT32_MIN);
  maxVal[0] = roomVals[0];
  for(int i = 0; i < N; i++)
    for(int j = 0; j < M; j++)
      if(maxVal[i * M + j] != INT32_MIN)
        for(auto e: graph[i * M + j])
          maxVal[e] = max(maxVal[e], maxVal[i * M + j] + roomVals[e]);

    if(maxVal[N * M - 1] == INT32_MIN)
      cout << "Entity";
    else
      cout << maxVal[N * M - 1];


  return 0;
}