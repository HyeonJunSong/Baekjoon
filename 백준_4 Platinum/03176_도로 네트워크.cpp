#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

#define LOG 17

int N;
vector<vector<pair<int, int>>> city;

int levelOf[100001];
int spTable[100001][LOG + 1];
int spTableMin[100001][LOG + 1];
int spTableMax[100001][LOG + 1];

void dfs(int cur, int prv, int level){
  levelOf[cur] = level;

  for(auto e: city[cur]){
    if(e.first == prv) continue;
    spTable[e.first][0] = cur;
    spTableMin[e.first][0] = e.second;
    spTableMax[e.first][0] = e.second;

    dfs(e.first, cur, level + 1);
  }
}

void spInit(){
  for(int j = 1; j <= LOG; j++){
  for(int i = 1; i <= N; i++){
      spTable[i][j] = spTable[spTable[i][j - 1]][j - 1];
      spTableMin[i][j] = min(spTableMin[i][j - 1], spTableMin[spTable[i][j - 1]][j - 1]);
      spTableMax[i][j] = max(spTableMax[i][j - 1], spTableMax[spTable[i][j - 1]][j - 1]);
    }
  }
}

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  cin >> N;
  city.assign(N + 1, {});
  for(int i = 0; i < N - 1; i++){
    int A, B, C;
    cin >> A >> B >> C;
    city[A].push_back({B, C});
    city[B].push_back({A, C});
  }

  dfs(1, 0, 1);
  spInit();

  int K;
  cin >> K;
  for(int k = 0; k < K; k++){
    int D, E;
    cin >> D >> E;

    int minVal = 987654321, maxVal = 0;

    while(levelOf[D] < levelOf[E]){
      int nextSp = (int)(log2(levelOf[E] - levelOf[D]));

      minVal = min(minVal, spTableMin[E][nextSp]);
      maxVal = max(maxVal, spTableMax[E][nextSp]);
      E = spTable[E][nextSp];
    }
    while(levelOf[D] > levelOf[E]){
      int nextSp = (int)(log2(levelOf[D] - levelOf[E]));
      minVal = min(minVal, spTableMin[D][nextSp]);
      maxVal = max(maxVal, spTableMax[D][nextSp]);
      D = spTable[D][nextSp];
    }

    while(E != D){
      int st = 1, ed = LOG;

      while(st <= ed){
        int mid = (st + ed) / 2;

        if(spTable[E][mid] == spTable[D][mid])
          ed = mid - 1;
        else
          st = mid + 1;
      }

      minVal = min(minVal, spTableMin[E][ed]);
      minVal = min(minVal, spTableMin[D][ed]);
      maxVal = max(maxVal, spTableMax[E][ed]);
      maxVal = max(maxVal, spTableMax[D][ed]);

      E = spTable[E][ed];
      D = spTable[D][ed];
    }

    cout << minVal << " " << maxVal << '\n';
  }


  return 0;
}