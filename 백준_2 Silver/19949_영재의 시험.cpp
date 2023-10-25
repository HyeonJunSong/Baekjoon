////231025
//16m 52s

#include <iostream>
#include <vector>

using namespace std;

vector<int> ans(10);

int totAns = 0;

bool ifOver5(vector<int>& possible){
  int cnt = 0;
  for(int i = 0; i < 10; i++)
    if(possible[i] == ans[i])
      cnt++;
  return cnt >= 5;
}

void getPossibleSet(int prev, int cur, vector<int>& res){
  if(res.size() == 10){
    if(ifOver5(res))
      totAns++;
    return;
  }

  for(int i = 1; i <= 5; i++){
    if(prev == cur && cur == i) continue;
    res.push_back(i);
    getPossibleSet(cur, i, res);
    res.pop_back();
  }
}


int main(){

  for(int i = 0; i < 10; i++)
    cin >> ans[i];
  
  vector<int> cur;
  getPossibleSet(-1, -1, cur);
  
  cout << totAns;
  return 0;
}