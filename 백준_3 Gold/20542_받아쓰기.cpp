#include <iostream>
#include <vector>
#include <string>

using namespace std;

int n, m;
string sy, ans;

vector<vector<int>> cache;

int commonCnt(int syInd, int ansInd){

  if(syInd == n)
    return m - ansInd;
  if(ansInd == m)
    return n - syInd;

if((sy[syInd] == ans[ansInd])
|| (sy[syInd] == 'i' && (ans[ansInd] == 'j' || ans[ansInd] == 'l'))
|| (sy[syInd] == 'v' && (ans[ansInd] == 'w'))){
    if(cache[syInd + 1][ansInd + 1] == -1)
      cache[syInd + 1][ansInd + 1] = commonCnt(syInd + 1, ansInd + 1);
    return cache[syInd + 1][ansInd + 1];
  }

  if(cache[syInd + 1][ansInd] == -1)
    cache[syInd + 1][ansInd] = commonCnt(syInd + 1, ansInd);
  if(cache[syInd + 1][ansInd + 1] == -1)
    cache[syInd + 1][ansInd + 1] = commonCnt(syInd + 1, ansInd + 1);
  if(cache[syInd][ansInd + 1] == -1)
    cache[syInd][ansInd + 1] = commonCnt(syInd, ansInd + 1);
  
  if(cache[syInd + 1][ansInd] < cache[syInd + 1][ansInd + 1]){
    if(cache[syInd + 1][ansInd] < cache[syInd][ansInd + 1])
      return cache[syInd + 1][ansInd] + 1;
    else
      return cache[syInd][ansInd + 1] + 1;
  }
  else{
    if(cache[syInd + 1][ansInd + 1] < cache[syInd][ansInd + 1])
      return cache[syInd + 1][ansInd + 1] + 1;
    else
      return cache[syInd][ansInd + 1] + 1;
  }
}

int main(){
  cin >> n >> m;

  cin >> sy >> ans;

  cache = vector<vector<int>>(n + 1, vector<int>(m + 1, -1));

  cout << abs(commonCnt(0, 0));

  return 0;
}