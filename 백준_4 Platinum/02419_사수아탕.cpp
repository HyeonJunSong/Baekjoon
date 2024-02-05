#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

typedef long long ll;

int n, m;
vector<ll> candy;
vector<vector<vector<vector<ll>>>> memo;

ll getMinCandyLoseCnt(int leftIdx, int rightIdx, int pos, int candyLeft);

int main(){
  cin >> n >> m;

  if(n == 0){
    cout << 0;
    return 0;
  }

  candy = vector<ll>(n);
  for(int i = 0; i < n; i++)
    cin >> candy[i];
  sort(candy.begin(), candy.end());

  if(candy.front() > 0){
    int ans = m - candy[0];
    if(ans < 0){
      cout << 0;
      return 0;
    }
    m -= candy[0];
    int curIdx = 0;
    
    while(curIdx + 1 < n && m - (candy[curIdx + 1] - candy[curIdx]) > 0){
      m -= (candy[curIdx + 1] - candy[curIdx]);
      ans += m;
      curIdx++;
    }
    cout << ans;
    return 0;
  } else if(candy.back() < 0){
    int ans = m + candy[n - 1];
    if(ans < 0){
      cout << 0;
      return 0;
    }
    m += candy[n - 1];
    int curIdx = n - 1;
    
    while(curIdx - 1 >= 0 && m - (candy[curIdx] - candy[curIdx - 1]) > 0){
      m -= (candy[curIdx] - candy[curIdx - 1]);
      ans += m;
      curIdx--;
    }
    cout << ans;
    return 0;
  }

  memo = vector<vector<vector<vector<ll>>>>(n, vector<vector<vector<ll>>>(n, vector<vector<ll>>(2, vector<ll>(n, -1))));

  int left, right;
  for(int i = 0; i < n - 1; i++){
    if(candy[i] <= 0 && candy[i + 1] > 0){
      left = i;
      right = i + 1;
      break;
    }
  }

  ll ans = 0;

  for(int i = 0; i < n; i++){
    if(memo[left][right][0][i] == -1)
      memo[left][right][0][i] = getMinCandyLoseCnt(left, right, 0, i);
    if(memo[left][right][1][i] == -1)
      memo[left][right][1][i] = getMinCandyLoseCnt(left, right, 1, i);
    if(ans < (i + 1) * m - memo[left][right][0][i] + (i + 1) * candy[left])
      ans = (i + 1) * m - memo[left][right][0][i] + (i + 1) * candy[left];
    if(ans < (i + 1) * m - memo[left][right][1][i] - (i + 1) * candy[right])
      ans = (i + 1) * m - memo[left][right][1][i] - (i + 1) * candy[right];
  }

  cout << ans;

  return 0;
}

ll getMinCandyLoseCnt(int leftIdx, int rightIdx, int pos, int candyLeft){

  if(candyLeft == 0)
    return 0;

  ll curCandyLoseCnt = LLONG_MAX;

  //내가 현재 왼쪽
  if(pos == 0){
    if(leftIdx - 1 >= 0){
      //왼쪽 먹기
      if(memo[leftIdx - 1][rightIdx][0][candyLeft - 1] == -1)
        memo[leftIdx - 1][rightIdx][0][candyLeft - 1] = getMinCandyLoseCnt(leftIdx - 1, rightIdx, 0, candyLeft - 1);
      if(curCandyLoseCnt > memo[leftIdx - 1][rightIdx][0][candyLeft - 1] + (candyLeft * (candy[leftIdx] - candy[leftIdx - 1])))
        curCandyLoseCnt = memo[leftIdx - 1][rightIdx][0][candyLeft - 1] + (candyLeft * (candy[leftIdx] - candy[leftIdx - 1]));

      //오른쪽 먹기
      if(memo[leftIdx - 1][rightIdx][1][candyLeft - 1] == -1)
        memo[leftIdx - 1][rightIdx][1][candyLeft - 1] = getMinCandyLoseCnt(leftIdx - 1, rightIdx, 1, candyLeft - 1);
      if(curCandyLoseCnt > memo[leftIdx - 1][rightIdx][1][candyLeft - 1] + (candyLeft * (candy[rightIdx] - candy[leftIdx])))
        curCandyLoseCnt = memo[leftIdx - 1][rightIdx][1][candyLeft - 1] + (candyLeft * (candy[rightIdx] - candy[leftIdx]));
    } else {
      curCandyLoseCnt = (candy[rightIdx] - candy[leftIdx]) * candyLeft;
      for(int i = 0; i < candyLeft - 1; i++)
        curCandyLoseCnt += (candy[rightIdx + i + 1] - candy[rightIdx + i]) * (candyLeft - (i + 1));
    }
  } else{
    if(rightIdx + 1 < n){
      //왼쪽 먹기
      if(memo[leftIdx][rightIdx + 1][0][candyLeft - 1] == -1)
        memo[leftIdx][rightIdx + 1][0][candyLeft - 1] = getMinCandyLoseCnt(leftIdx, rightIdx + 1, 0, candyLeft - 1);
      if(curCandyLoseCnt > memo[leftIdx][rightIdx + 1][0][candyLeft - 1] + (candyLeft * (candy[rightIdx] - candy[leftIdx])))
        curCandyLoseCnt = memo[leftIdx][rightIdx + 1][0][candyLeft - 1] + (candyLeft * (candy[rightIdx] - candy[leftIdx]));

      //오른쪽 먹기
      if(memo[leftIdx][rightIdx + 1][1][candyLeft - 1] == -1)
        memo[leftIdx][rightIdx + 1][1][candyLeft - 1] = getMinCandyLoseCnt(leftIdx, rightIdx + 1, 1, candyLeft - 1);
      if(curCandyLoseCnt > memo[leftIdx][rightIdx + 1][1][candyLeft - 1] + (candyLeft * (candy[rightIdx + 1] - candy[rightIdx])))
        curCandyLoseCnt = memo[leftIdx][rightIdx + 1][1][candyLeft - 1] + (candyLeft * (candy[rightIdx + 1] - candy[rightIdx]));
    } else {
      curCandyLoseCnt = (candy[rightIdx] - candy[leftIdx]) * candyLeft;
      for(int i = 0; i < candyLeft - 1; i++)
        curCandyLoseCnt += (candy[leftIdx - i] - candy[leftIdx - i - 1]) * (candyLeft - (i + 1));
    }
  }

  if(curCandyLoseCnt < 0)
    return LLONG_MAX;
  else
    return curCandyLoseCnt;
}