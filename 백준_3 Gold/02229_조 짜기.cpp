#include <iostream>
#include <vector>

using namespace std;

int N;
vector<int> students;
vector<int> memo;

int getMAXGroupNum(int curIdx){

  if(curIdx == N)
    return 0;

  int curGroupMax = students[curIdx];
  int curGroupMin = students[curIdx];

  int ans = 0;
  for(int i = curIdx + 1; i <= N; i++){
    if(memo[i] == -1)
      memo[i] = getMAXGroupNum(i);
    ans = max(ans, curGroupMax - curGroupMin + memo[i]);
    curGroupMax = max(curGroupMax, students[i]);
    curGroupMin = min(curGroupMin, students[i]);
  }

  return ans;
}

int main(){

  cin >> N;
  students = vector<int>(N);
  for(int i = 0; i < N; i++)
    cin >> students[i];
  
  memo = vector<int>(N + 1, -1);
  cout << getMAXGroupNum(0);

  return 0;
}