////23.09.02
//1h 18m 04s

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int N, K, D;
vector<pair<int, vector<bool>>> student;


vector<int> curAlgo;
int curGroupEndInd = 0;

pair<int, int> getCurOrAnd(int studNum){
  pair<int, int> result;
  for(int i = 0; i < K; i++){
    if(curAlgo[i] != 0)
      result.first++;
    if(curAlgo[i] == studNum)
      result.second++;
  }
  return result;
}

void vectorSum(vector<int>& sum, vector<bool>& cur){
  for(int i = 0; i < sum.size(); i++){
    if(cur[i])
      sum[i]++;
  }
}

void vectorSub(vector<int>& sub, vector<bool>& cur){
  for(int i = 0; i < sub.size(); i++){
    if(cur[i])
      sub[i]--;
  }
}

int getCurGroupEfficiency(int ind){

  for(; curGroupEndInd < N && student[curGroupEndInd].first - student[ind].first <= D; curGroupEndInd++){
    vectorSum(curAlgo, student[curGroupEndInd].second);
  }

  pair<int, int> curOrAnd = getCurOrAnd(curGroupEndInd - ind);
  return (curOrAnd.first - curOrAnd.second) * (curGroupEndInd - ind);
}

int main(){
  cin >> N >> K >> D;
  student = vector<pair<int, vector<bool>>>(N, pair<int, vector<bool>>(0, vector<bool>(K, false)));
  for(int i = 0; i < N; i++){
    int M;
    cin >> M >> student[i].first;
    for(int j = 0; j < M; j++){
      int A;
      cin >> A;
      student[i].second[A - 1] = true;
    }
  }

  sort(student.begin(), student.end());

  // for(int i = 0; i < N; i++)
  //   cout << student[i].first << endl;

  curAlgo = vector<int>(K, 0);

  int maxEfficency = 0;
  for(int i = 0; i < N; i++){
    int curEfficency = getCurGroupEfficiency(i);
    if(maxEfficency < curEfficency)
      maxEfficency = curEfficency;
    vectorSub(curAlgo, student[i].second);
  }

  cout << maxEfficency;

  return 0;
}