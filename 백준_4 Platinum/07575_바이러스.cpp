#include <iostream>
#include <vector>

using namespace std;

int main(){

  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int N, K;
  cin >> N >> K;

  vector<vector<int>> programCodes(N);
  for(int i = 0; i < N; i++){
    int M;
    cin >> M;

    if(M < K){
      cout << "NO";
      exit(0);
    }

    programCodes[i] = vector<int>(M);
    for(int j = 0; j < M; j++)
      cin >> programCodes[i][j];
  }


  for(int patternSt = programCodes[0].size() - K; patternSt > -1; patternSt--){

    //p배열 설정하기
    vector<int> p(K, 0);
    int curCompIdx = 0;
    for(int j = 1; j < K; j++){
      while(curCompIdx > 0 && programCodes[0][patternSt + curCompIdx] != programCodes[0][patternSt + j])
        curCompIdx = p[curCompIdx - 1];
      if(programCodes[0][patternSt + curCompIdx] == programCodes[0][patternSt + j])
        p[j] = ++curCompIdx;
    }

    //나머지 프로그램 코드들 돌며 바이러스 여부 판단
    int minSameLength = K;
    for(int j = 1; j < N; j++){
      
      int curPatternIdx = 0;
      int curMaxSameLength = 0;

      for(int k = 0; k < programCodes[j].size(); k++){
        curMaxSameLength = max(curMaxSameLength, curPatternIdx);

        if(curPatternIdx == K) break;

        while(curPatternIdx > 0 && programCodes[j][k] != programCodes[0][patternSt + curPatternIdx])
          curPatternIdx = p[curPatternIdx - 1];

        if(programCodes[0][patternSt + curPatternIdx] == programCodes[j][k])
          curPatternIdx++;
        else
          curPatternIdx = 0;
      }

      if(curPatternIdx == K) continue;
      
      curPatternIdx = 0;

      for(int k = programCodes[j].size() - 1; k > -1 ; k--){
        curMaxSameLength = max(curMaxSameLength, curPatternIdx);

        if(curPatternIdx == K) break;

        while(curPatternIdx > 0 && programCodes[j][k] != programCodes[0][patternSt + curPatternIdx])
          curPatternIdx = p[curPatternIdx - 1];

        if(programCodes[0][patternSt + curPatternIdx] == programCodes[j][k])
          curPatternIdx++;
        else
          curPatternIdx = 0;
      }

      if(curPatternIdx == K) continue;

      minSameLength = min(minSameLength, curMaxSameLength);
    }

    if(minSameLength >= K){
      cout << "YES";
      exit(0);
    }
    
    // patternSt -= K - minSameLength - 1;
  }
  cout << "NO";

  return 0;
}

