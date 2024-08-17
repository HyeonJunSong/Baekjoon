#include <iostream>
#include <vector>
#include <map>

using namespace std;

int main(){

  int N, M, L, K;
  cin >> N >> M >> L >> K;
  multimap<int, int> stars;
  for(int i = 0; i < K; i++){
    int x, y;
    cin >> x >> y;
    stars.insert({x, y});
  }

  int ans = 0;
  for(auto iter1 = stars.begin(); iter1 != stars.end(); iter1++){
    auto iterEnd = stars.upper_bound(iter1->first + L);
    multimap<int, int> curStars;
    for(auto iter2 = iter1; iter2 != iterEnd; iter2++)
      curStars.insert({iter2->second, 0});
    
    multimap<int, int> curStars2;
    int curStarsSize = 0;
    for(auto iter2 = curStars.begin(); iter2 != curStars.end(); iter2++){
      curStars2.insert({iter2->first, curStarsSize++});
    }
    for(map<int, int>::iterator iter2 = curStars2.begin(); iter2 != curStars2.end(); iter2++){
      if(curStars2.upper_bound(iter2->first + L) == curStars2.end())
        ans = max(ans, curStarsSize - iter2->second);
      else
        ans = max(ans, curStars2.upper_bound(iter2->first + L)->second - iter2->second);
    }
  }
  ans = K - ans;

  cout << ans;

  return 0;
}