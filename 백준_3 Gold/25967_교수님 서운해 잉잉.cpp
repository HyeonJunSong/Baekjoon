////231102
//1h 03m 52s

#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>

using namespace std;

string T;
string comp;

vector<vector<int>> memo;

#define INF 987654321

vector<pair<int, int>> loc = {
  {3, 6},
  {21, 10},
  {13, 10},
  {11, 6},
  {10, 2},
  {15, 6},
  {19, 6},
  {23, 6},
  {30, 2},
  {27, 6},
  {31, 6},
  {35, 6},
  {29, 10},
  {25, 10},
  {34, 2},
  {38, 2},
  {2, 2},
  {14, 2},
  {7, 6},
  {18, 2},
  {26, 2},
  {17, 10},
  {6, 2},
  {9, 10},
  {22, 2},
  {5, 10},
};

int getSimilarity(char a, char b){
  return pow(loc[a - 'A'].first - loc[b - 'A'].first, 2) + pow(loc[a - 'A'].second - loc[b - 'A'].second, 2);
}

int getMinSimilarity(int TInd, int compInd){

  if(TInd == T.size())
    return 1600 * (comp.size() - compInd);
  else if(compInd == comp.size())
    return 1600 * (T.size() - TInd);

  if(memo[TInd + 1][compInd + 1] == -1)
    memo[TInd + 1][compInd + 1] = getMinSimilarity(TInd + 1, compInd + 1);
  if(memo[TInd + 1][compInd] == -1)
    memo[TInd + 1][compInd] = getMinSimilarity(TInd + 1, compInd);
  if(memo[TInd][compInd + 1] == -1)
    memo[TInd][compInd + 1] = getMinSimilarity(TInd, compInd + 1);


  int curMin = memo[TInd + 1][compInd + 1] + getSimilarity(T[TInd], comp[compInd]);

  if(curMin > memo[TInd + 1][compInd] + 1600)
    curMin = memo[TInd + 1][compInd] + 1600;

  if(curMin > memo[TInd][compInd + 1] + 1600)
    curMin = memo[TInd][compInd + 1] + 1600;
  
  return curMin;
}

int getCurSimilarity(){

  memo = vector<vector<int>>(T.size() + 1, vector<int>(comp.size() + 1, -1));

  return getMinSimilarity(0, 0);
}


int main(){

  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  int N;
  cin >> N;

  vector<string> inpStr(N);
  for(int i = 0; i < N; i++)
    cin >> inpStr[i];
  
  cin >> T;

  int minSim = INF;
  vector<string> ans;
  for(auto e : inpStr){
    comp = e;
    int curSimilarity = getCurSimilarity();

    if(minSim > curSimilarity){
      minSim = curSimilarity;
      ans.clear();
      ans.push_back(e);
    }
    else if(minSim == curSimilarity){
      ans.push_back(e);
    }
  }

  sort(ans.begin(), ans.end());
  for(auto e : ans)
    cout << e << "\n";

}