////230918
//24m 45s

#include <iostream>
#include <vector>

using namespace std;


vector<int> wishes;
vector<int> ifHasTeam;

void findTeam(int curInd, vector<int>& before, vector<bool>& ifSelected){

  if(ifHasTeam[wishes[curInd]] != -1){
    for(int i = 0; i < before.size(); i++)
      ifHasTeam[before[i]] = 0;
    return;
  }

  if(ifSelected[wishes[curInd]] == true){
    int i = 0;
    while(before[i] != wishes[curInd]){
      ifHasTeam[before[i]] = 0;
      i++;
    }
    for(; i < before.size(); i++)
      ifHasTeam[before[i]] = 1;
  }
  else{
    before.push_back(wishes[curInd]);
    ifSelected[wishes[curInd]] = true;
    findTeam(wishes[curInd], before, ifSelected);
  }

}

void testCase(){
  int n;
  cin >> n;
  wishes = vector<int>(n);
  for(int i = 0; i < n; i++){
    int inp;
    cin >> inp;
    wishes[i] = inp - 1;
  }
  
  ifHasTeam = vector<int>(n, -1);

  for(int i = 0; i < n; i++){
    if(ifHasTeam[i] != -1) continue;
    vector<int> before;
    vector<bool> ifSelected(n, false);
    before.push_back(i);
    ifSelected[i] = true;
    findTeam(i, before, ifSelected);
  }

  int cnt = 0;
  for(int i = 0; i < n; i++)
    if(ifHasTeam[i] == 0) cnt++;
  
  cout << cnt << '\n';
}

int main(){
  int T;
  cin >> T;

  for(int i = 0; i < T; i++){
    testCase();
  }
  
  return 0;
}