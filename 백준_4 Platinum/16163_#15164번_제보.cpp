#include <iostream>
#include <vector>
#include <string>

using namespace std;

vector<int> radiusArr;
//CLP : current Longest Palindrome
int CLPEnd;
int CLPCenterInd;

int strLen;
vector<char> str;
int findPalinRadius(int ind) {

  /*매니처 알고리즘의 핵심 파트_저장된 반지름 가져오기*/
  ////두 가지만 보면 된다
  //1. CLP의 범위 안인가? -> 아니면 못가져오므로 r 0으로
  //2. 남은 CLP 끝까지의 거리와 반대편에서 이미 탐색한 반지름 중 더 작은 값.
  int r = 0;
  if (CLPEnd >= ind) {
      if (radiusArr[CLPCenterInd] - (ind - CLPCenterInd) < radiusArr[CLPCenterInd - (ind - CLPCenterInd)])
          r = radiusArr[CLPCenterInd] - (ind - CLPCenterInd);
      else
          r = radiusArr[CLPCenterInd - (ind - CLPCenterInd)];
  }


  while (ind + (r + 1) < strLen && ind - (r + 1) >= 0
      && str[ind + (r + 1)] == str[ind - (r + 1)]
      ) r++;

  return r;
}

int calcPalinNum(int ind) {
  if (ind % 2 == 0) {
    return (int)(radiusArr[ind] / 2) + 1;
  }
  else {
    if (radiusArr[ind] % 2 == 1) return (int)(radiusArr[ind] / 2) + 1;
    else return (int)(radiusArr[ind] / 2);
  }
}

int main() {
  string inpStr;
  cin >> inpStr;

  str.push_back(inpStr[0]);
  for (int i = 1; i < inpStr.size(); i++) {
    str.push_back('#');
    str.push_back(inpStr[i]);
  }
  strLen = str.size();

  radiusArr = vector<int>(strLen, 0);

  CLPEnd = 0;
  CLPCenterInd = 0;
  for (int i = 0; i < strLen; i++) {
    radiusArr[i] = findPalinRadius(i);
    if (CLPEnd < i + radiusArr[i]) {
      CLPEnd = i + radiusArr[i];
      CLPCenterInd = i;
    }
  }

  long long palinCnt = 0;

  for (int i = 0; i < strLen; i++) {
    // cout << str[i] << ' ' << radiusArr[i] << " : " << calcPalinNum(i) << endl;
    palinCnt += calcPalinNum(i);
  }

  cout << palinCnt;

  return 0;
}