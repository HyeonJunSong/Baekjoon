#include <iostream>
#include <vector>

using namespace std;

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  int N;
  cin >> N;
  vector<int> bulbs(N);
  for(int i = 0; i < N; i++){
    char bulb;
    cin >> bulb;
    switch(bulb){
      case 'R':
        bulbs[i] = 0;
      break;
      case 'G':
        bulbs[i] = 1;
      break;
      case 'B':
        bulbs[i] = 2;
      break;
    }
  }

  int ans = 987654321;
  for(int i = 0; i < 3; i++){
    vector<int> curBulbs = bulbs;
    for(int j = 0; j < 3; j++)
      curBulbs[j] = (curBulbs[j] + i) % 3;
    
    int curAns = i;
    for(int j = 1; j < N - 2; j++){
      for(int k = 0; k < 3; k++){
        if(curBulbs[j - 1] == curBulbs[j]) break;
        for(int l = 0; l < 3; l++)
          curBulbs[j + l] = (curBulbs[j + l] + 1) % 3;
        curAns++;
      }
    }

    if(!(curBulbs[N - 3] == curBulbs[N - 2] && curBulbs[N - 2] == curBulbs[N - 1])) continue;
    ans = min(ans, curAns);
  }

  if(ans == 987654321)
    cout << -1;
  else
    cout << ans;

  return 0;
}