#include <iostream>
#include <vector>

using namespace std;

#define ll long long

int main(){

  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  int N;
  cin >> N;

  int M;
  cin >> M;
  vector<pair<int, int>> schedule(M);
  for(int i = 0; i < M; i++)
    cin >> schedule[i].first >> schedule[i].second;
  

  ll scheduleCounts[50002] = {0};
  for(int i = 0; i < M; i++){
    scheduleCounts[schedule[i].first]++;
    scheduleCounts[schedule[i].second + 1]--;
  }
  for(int i = 1; i < 50002; i++)
    scheduleCounts[i] += scheduleCounts[i - 1];  

  int curScheduleSum = 0;

  for(int i = 1; i <= 7 * N; i++)
    curScheduleSum += scheduleCounts[i];

  int maxScheduleSum = curScheduleSum;
  int maxScheduleSt = 1;

  for(int i = 2; i <= 50000 - 7 * N + 1; i++){
    curScheduleSum -= scheduleCounts[i - 1];
    curScheduleSum += scheduleCounts[i + 7 * N - 1];

    if(maxScheduleSum < curScheduleSum){
      maxScheduleSum = curScheduleSum;
      maxScheduleSt = i;
    }
  }

  int ans = 0;
  for(int i = 0; i < M; i++){
    if(schedule[i].second - maxScheduleSt < 0) continue;
    if((schedule[i].first - maxScheduleSt) / 7 > N - 1) continue;
    ans += min((schedule[i].second - maxScheduleSt) / 7, N - 1) - max((schedule[i].first - maxScheduleSt) / 7, 0) + 1;
  }
  
  cout << ans;


  return 0;
}