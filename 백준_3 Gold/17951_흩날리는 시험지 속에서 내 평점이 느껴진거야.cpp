#include <iostream>
#include <vector>

using namespace std;

int N, K;
vector<int> papers;

#define MAX 987654321

bool ifScorePossible(int score);

int main(){

  cin >> N >> K;
  papers = vector<int>(N);
  int tot = 0;
  for(int i = 0; i < N; i++){
    cin >> papers[i];
    tot += papers[i];
  }
  
  int st = 1;
  int ed = tot / K;
  while(st <= ed){
    int mid = (st + ed) / 2;
    if(ifScorePossible(mid))
      st = mid + 1;
    else
      ed = mid - 1;
  }

  cout << ed;
  return 0;
}

bool ifScorePossible(int score){
  int curSum = 0;
  int groupNum = 0;
  for(int i = 0; i < N; i++){
    if(curSum >= score){
      groupNum++;
      curSum = 0;
    }

    curSum += papers[i];
  }

  return curSum >= score || groupNum >= K;
}