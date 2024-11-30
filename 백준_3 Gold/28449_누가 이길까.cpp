#include <iostream>
#include <vector>
#include <map>
#include <iterator>

using namespace std;

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int N, M;
  cin >> N >> M;

  vector<int> HI(N);
  for(int i = 0; i < N; i++)
    cin >> HI[i];
  
  map<int, long long> ARC;
  for(int i = 0; i < M; i++){
    int skill;
    cin >> skill;
    if(ARC.find(skill) == ARC.end())
      ARC[skill] = 0;
    ARC[skill]++;
  }

  ARC[0] = 0;
  ARC[100001] = 0;
  for(auto iter = next(ARC.begin()); iter != ARC.end(); iter++)
    ARC[iter->first] += prev(iter)->second;
  
  long long tot = ARC.rbegin()->second;
  
  long long win = 0;
  long long tie = 0;
  long long lose = 0;

  for(auto e: HI){
    auto iter1 = prev(ARC.lower_bound(e));
    auto iter2 = prev(ARC.upper_bound(e));
    
      win += iter1->second;
      tie += iter2->second - iter1->second;
      lose += tot - iter2->second;
  }

  cout << win << " " << lose << " " << tie;

  return 0;
}