#include <iostream>
#include <vector>

using namespace std;

int N, D;
vector<long long> T;
vector<long long> V;

long long getAns(int st, int ed, int optSt, int optEd);

int main(){

  cin >> N >> D;
  T = vector<long long>(N);
  V = vector<long long>(N);

  for(int i = 0; i < N; i++)
    cin >> T[i];
  for(int i = 0; i < N; i++)
    cin >> V[i];

  cout << getAns(0, N - 1, 0, N - 1);

  return 0;
}

long long getAns(int st, int ed, int optSt, int optEd){
  if(st > ed)
    return 0;

  int mid = (st + ed) / 2;

  long long ans = 0;
  int optPoint;
  //mid일에 d 만큼 숙성시켰을 때
  for(int d = max(optSt - mid, 0); d <= min(optEd - mid, D); d++){

    if(ans < d * T[mid + d] + V[mid]){
      ans = d * T[mid + d] + V[mid];
      optPoint = mid + d;
    }
  }

  long long left = getAns(st, mid - 1, optSt, optPoint);
  ans = max(ans, left);
  long long right = getAns(mid + 1, ed, optPoint, optEd);
  ans = max(ans, right);

  return ans;
}