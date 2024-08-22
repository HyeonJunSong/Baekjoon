#include <iostream>
#include <vector>
#include <string>

using namespace std;

int N;

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  cin >> N;
  vector<string> adjGraph(N);
  for(int i = 0; i < N; i++)
    cin >> adjGraph[i];
  
  for(int i = 0; i < N; i++)
    for(int j = 0; j < N; j++)
      if(adjGraph[i][j] == '1') adjGraph[j][i] = '1';
  
  int ans = 0;
  vector<int> curStatus(N, 0);
  for(int i = 0; i < N; i++){
    if(curStatus[i] != 0) continue;
    curStatus[i] = 2;

    int curTotCnt = 1;
    int curHunCnt = 1;
    vector<int> stack(1, i);
    while(!stack.empty()){
      int curNode = stack.back();
      stack.pop_back();

      for(int j = 0; j < N; j++){
        if(curStatus[j] != 0) continue;
        if(adjGraph[curNode][j] == '0') continue;

        if(curStatus[curNode] == 1){
          curStatus[j] = 2;
          curHunCnt++;
        } else {
          curStatus[j] = 1;
        }
        stack.push_back(j);

        curTotCnt++;
      }
    }

    ans += max(curHunCnt, curTotCnt - curHunCnt);
  }

  cout << ans;

  return 0;
}