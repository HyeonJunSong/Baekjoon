#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  int N, Q;

  cin >> N >> Q;

  vector<pair<pair<int, int>, int>> logs(N);
  int y;
  for(int i = 0; i < N; i++){
    cin >> logs[i].first.first >> logs[i].first.second >> y;
    logs[i].second = i + 1;
  }
  
  sort(logs.begin(), logs.end());
  vector<int> logOf(N + 1);
  for(int i = 0; i < N; i++)
    logOf[logs[i].second] = i;

  vector<int> groupOf(N);

  int groupNum = 0;
  for(int i = 0; i < N; i++){
    int curEnd = logs[i].first.second;

    groupOf[i] = groupNum;
    for(int j = i + 1; j < N; j++){
      if(logs[j].first.first > curEnd) break;
      curEnd = max(curEnd, logs[j].first.second);
      groupOf[j] = groupNum;
      i = j;
    }
    groupNum++;
  }

  for(int i = 0; i < Q; i++){
    int st, ed;
    cin >> st >> ed;
    if(groupOf[logOf[st]] == groupOf[logOf[ed]])
      cout << "1\n";
    else
      cout << "0\n";
  }

  return 0;
}