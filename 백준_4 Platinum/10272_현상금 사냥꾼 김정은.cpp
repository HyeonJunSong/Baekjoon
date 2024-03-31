#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

int N;
vector<pair<int, int>> coords;

vector<vector<double>> memo;

double getDis(int a, int b){
  return sqrt(pow(coords[b].first - coords[a].first, 2) + pow(coords[b].second - coords[a].second, 2));
}

double getMinDis(int stIdx, int edIdx){

  if(stIdx == N - 1 || edIdx == N - 1) return getDis(stIdx, edIdx);

  if(memo[max(stIdx, edIdx) + 1][edIdx] == -1)
    memo[max(stIdx, edIdx) + 1][edIdx] = getMinDis(max(stIdx, edIdx) + 1, edIdx);
  
  if(memo[stIdx][max(stIdx, edIdx) + 1] == -1)
    memo[stIdx][max(stIdx, edIdx) + 1] = getMinDis(stIdx, max(stIdx, edIdx) + 1);
  
  return min(memo[max(stIdx, edIdx) + 1][edIdx] + getDis(stIdx, max(stIdx, edIdx) + 1), memo[stIdx][max(stIdx, edIdx) + 1] + getDis(max(stIdx, edIdx) + 1, edIdx));
}

void testCase(){

  cin >> N;
  coords = vector<pair<int, int>>(N, {0, 0});
  for(int i = 0; i < N; i++)
    cin >> coords[i].first >> coords[i].second;

  memo = vector<vector<double>>(N, vector<double>(N, -1));

  printf("%.5f\n", getMinDis(0, 0));
}

int main(){

  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  int T;
  cin >> T;

  for(int t = 0; t < T; t++)
    testCase();

  return 0;
}