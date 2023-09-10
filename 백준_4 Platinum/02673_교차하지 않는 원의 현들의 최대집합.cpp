#include <iostream>
#include <vector>

using namespace std;

int N;
vector<pair<int, int>> chords;

bool ifCross(int i, int j) {
    return (chords[i].first < chords[j].first&& chords[j].first < chords[i].second)
        ^ (chords[i].first < chords[j].second&& chords[j].second < chords[i].second);
}

vector<long long> possibleSet;

int maxCnt = 0;

int getCurPossibleSetNum(long long curSet){
  int cnt = 0;
  while(curSet != 0){
    if(curSet % 2 == 1)
      cnt++;
    curSet >>= 1;
  }
  return cnt;
}

void getMaxChordsNum(int curInd, int curNumOfSet, long long curPossibleSet) {

  if(getCurPossibleSetNum(curPossibleSet) <= maxCnt)
    return;

  for (int i = curInd + 1; i < N; i++) {
      if ((curPossibleSet & (1LL << i)) == 0) continue;
      getMaxChordsNum(i, curNumOfSet + 1, curPossibleSet & possibleSet[i]);
  }

  if(maxCnt < curNumOfSet)
    maxCnt = curNumOfSet;
}

int main() {
    cin >> N;
    chords = vector<pair<int, int>>(N);
    for (int i = 0; i < N; i++) {
        int p1, p2;
        cin >> p1 >> p2;
        if (p1 < p2) {
            chords[i].first = p1;
            chords[i].second = p2;
        }
        else {
            chords[i].first = p2;
            chords[i].second = p1;
        }
    }

    possibleSet = vector<long long>(N);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (ifCross(i, j)) continue;
            possibleSet[i] |= (1LL << j);
        }
    }

    for (int i = 0; i < N; i++) {
      getMaxChordsNum(i, 1, possibleSet[i]);
    }

    cout << maxCnt;

    return 0;
}