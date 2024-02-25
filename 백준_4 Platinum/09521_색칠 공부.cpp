#include <iostream>
#include <vector>

using namespace std;

#define DIV 1000000007


int main(){

  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  long long N, K;
  
  cin >> N >> K;

  vector<int> f(N + 1);
  for(int i = 1; i < N + 1; i++)
    cin >> f[i];
  
  //그래프 돌며 사이클 체크하기
  vector<int> cycles;
  vector<pair<bool, int>> group;
  vector<int> gNum(N + 1, -1);
  vector<int> path;
  vector<int> pathIdx(N + 1, -1);

  vector<bool> visited(N + 1, false);
  for(int i = 1; i < N + 1; i++){
    if(visited[i]) continue;

    int pathCnt = 0;
    int curNode = i;

    int curGNum = -1;

    while(true){
      path.push_back(curNode);
      pathIdx[curNode] = pathCnt++;
      visited[curNode] = true;

      if(pathIdx[f[curNode]] != -1){
        if(pathCnt - pathIdx[f[curNode]] > 1){
          group.push_back({true, 0});
          cycles.push_back(pathCnt - pathIdx[f[curNode]]);
        } else {
          group.push_back({false, 0});
        }
        curGNum = group.size() - 1;
        break;
      }
      if(visited[f[curNode]]){
        curGNum = gNum[f[curNode]];
        break;
      };
      curNode = f[curNode];
    }

    if(curGNum != -1){
      for(auto e: path){
        gNum[e] = curGNum;
        group[curGNum].second++;
        pathIdx[e] = -1;
      }
      path.clear();
    } else {
      for(int i = 0; i < path.size() - 1; i++){
        gNum[path[i]] = curGNum;
        group[curGNum].second++;
        pathIdx[i] = -1;
      }
      path.clear();
      pathIdx[path.size() - 1] = -1;
    }
  }

  //태뷸레이션
  int tableSize = 0;
  for(auto e: cycles)
    tableSize = max(tableSize, e);
  vector<long long> dp;
  if(tableSize > 0){
    dp = vector<long long>(tableSize + 1, 0);

    dp[1] = K;
    dp[2] = (K * (K - 1)) % DIV;

    for(int i = 2; i < tableSize; i++){
      if(i == 1){
        dp[i + 2] += ((dp[i] * (K - 1)) % DIV);
      } else if(i == tableSize - 1){
        dp[i + 1] += ((dp[i] * (K - 2)) % DIV);
      } else{
        dp[i + 1] += ((dp[i] * (K - 2)) % DIV);
        dp[i + 2] += ((dp[i] * (K - 1)) % DIV);
      }
    }
  }

  long long ans = 1;
  
  //사이클 아닌 애들 개수에 해당하는 조합 구하기
  int nonCycles = 0;
  for(auto e: group){
    if(e.first) continue;
        
    ans = (ans * K) % DIV;
    for(int i = 0; i < e.second - 1; i++)
      ans = (ans * (K - 1)) % DIV;
    nonCycles += e.second;
  }
  
  //사이클 개수에 해당하는 조합 수 구하기
  int cyclesSum = 0;
  for(auto e: cycles){
    ans = (ans * dp[e]) % DIV;
    cyclesSum += e;
  }

  for(int i = 0; i < N - nonCycles - cyclesSum; i++)
    ans = (ans * (K - 1)) % DIV;

  cout << ans;

  return 0;
}