////230814
//49m 47s

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

bool comp(pair<int, pair<int, int>> a, pair<int, pair<int, int>> b){
  return a.first < b.first;
}

int main(){

  int N;
  cin >> N;
  vector<int> snowballs(N);
  for(int i = 0; i < N; i++)
    cin >> snowballs[i];
  
  vector<pair<int, pair<int, int>>> combinations;
  for(int i = 0; i < N - 1; i++)
    for(int j = i + 1; j < N; j++)
      combinations.push_back({snowballs[i] + snowballs[j], {i, j}});
  
  sort(combinations.begin(), combinations.end(), comp);

  int smallestGap = -1;

  for(int i = 0; i < combinations.size() - 1; i++){

    pair<int, int> curComb = combinations[i].second;
    int j = i + 1;
    while(j != combinations.size()
    && (curComb.first == combinations[j].second.first || curComb.first == combinations[j].second.second
    || curComb.second == combinations[j].second.first || curComb.second == combinations[j].second.second))
    j++;

    if(j == combinations.size()) continue;

    if(smallestGap == -1 || smallestGap > combinations[j].first - combinations[i].first)
      smallestGap = combinations[j].first - combinations[i].first;

  }

  cout << smallestGap;

  return 0;
}