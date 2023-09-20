#include <iostream>
#include <vector>

using namespace std;

vector<vector<int>> possibleTasks;

vector<int> personInChargeOf;
vector<vector<bool>> visited;

bool ifCanTakeCharge(int person, vector<bool>& ifAvailable){

  for(int i = 0; i < possibleTasks[person].size(); i++){
    if(!ifAvailable[possibleTasks[person][i]]) continue;
    if(visited[person][i]) continue;

    if(personInChargeOf[possibleTasks[person][i]] != -1){

      ifAvailable[possibleTasks[person][i]] = false;
      if(ifCanTakeCharge(personInChargeOf[possibleTasks[person][i]], ifAvailable)){
        personInChargeOf[possibleTasks[person][i]] = person;
        return true;
      }
      visited[person][i] = true;
      ifAvailable[possibleTasks[person][i]] = true;

    }
    else{
      personInChargeOf[possibleTasks[person][i]] = person;
      return true;
    }

  }

  return false;
}

int main(){

  int N, M;
  cin >> N >> M;

  possibleTasks = vector<vector<int>>(N);
  visited = vector<vector<bool>>(N);
  for(int i = 0; i < N; i++){
    int taskCnt;
    cin >> taskCnt;
    visited[i] = vector<bool>(taskCnt, false);

    possibleTasks[i] = vector<int>(taskCnt);
    for(int j = 0; j < taskCnt; j++)
      cin >> possibleTasks[i][j];
  }

  personInChargeOf = vector<int>(M + 1, -1);

  for(int i = 0; i < N; i++){
    vector<bool> ifAvailable(N, true);
    ifCanTakeCharge(i, ifAvailable);
  }

  int cnt = 0;
  for(int i = 1; i <= M; i++)
    if(personInChargeOf[i] != -1)
      cnt++;
  
  cout << cnt;



  return 0;
}