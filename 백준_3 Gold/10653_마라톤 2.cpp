#include <iostream>
#include <vector>

using namespace std;
vector<pair<int, int>> checkpoints;
vector<vector<vector<int>>> cache;

int N, K;

#define MAX 987654321

int calcDis(int indA, int indB){
  return abs(checkpoints[indA].first - checkpoints[indB].first)
  + abs(checkpoints[indA].second - checkpoints[indB].second);
}

int calcDisLeft(int curInd){
  int disLeft = 0;
  for(int i = curInd; i < N - 1; i++)
    disLeft += calcDis(i, i + 1);
  return disLeft;
}

int retMinDis(int curInd, int nextInd, int Kleft){

  ////기저
  if(nextInd == N)
    return MAX;
  if(Kleft == 0){
    return calcDis(curInd, nextInd) + calcDisLeft(nextInd);
  }

  ////연산
  int minDistance = MAX;
  
  //다음 체크포인트를 건너뛸 때
  if(cache[curInd][nextInd + 1][Kleft - 1] == -1)
    cache[curInd][nextInd + 1][Kleft - 1] = retMinDis(curInd, nextInd + 1, Kleft - 1);
  
  if(minDistance > cache[curInd][nextInd + 1][Kleft - 1])
    minDistance = cache[curInd][nextInd + 1][Kleft - 1];
    

  //다음 체크포인트를 안 건너뛸 때
  if(cache[nextInd][nextInd + 1][Kleft] == -1)
    cache[nextInd][nextInd + 1][Kleft] = retMinDis(nextInd, nextInd + 1, Kleft);
  
  if(minDistance > cache[nextInd][nextInd + 1][Kleft] + calcDis(curInd, nextInd))
    minDistance = cache[nextInd][nextInd + 1][Kleft] + calcDis(curInd, nextInd);

  ////리턴
  return minDistance;
}

int main(){
  cin >> N >> K;

  checkpoints = vector<pair<int, int>>(N);

  for(int i = 0; i < N; i++)
    cin >> checkpoints[i].first >> checkpoints[i].second;
  
  cache = vector<vector<vector<int>>>(N, vector<vector<int>>(N + 1, vector<int>(K + 1, -1)));
  cout << retMinDis(0, 1, K);

  return 0;
}