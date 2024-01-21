////240121
//1h 13m

#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

int main(){

  int N;
  cin >> N;
  vector<int> school(N);
  for(int i = 0; i < N; i++)
    cin >> school[i];
  sort(school.begin(), school.end());

  vector<pair<int, long long>> newSchool;
  newSchool.push_back({school[0], 1});
  
  for(int i = 1; i < school.size(); i++){
    if(newSchool.back().first == school[i])
      newSchool.back().second++;
    else
      newSchool.push_back({school[i], 1});
  }

  vector<long long> numOfSchools((int)(newSchool.back().first / 2) + 1, 0);
  for(auto e : newSchool){
    for(int i = 1; i <= (int)(sqrt(e.first)); i++){
      if(e.first % i == 0){
        numOfSchools[i] += e.second;
        if((int)(e.first / i) <= (int)(newSchool.back().first / 2))
          numOfSchools[(int)(e.first / i)] += e.second;
      }
    }
    if((int)(sqrt(e.first)) * (int)(sqrt(e.first)) == e.first)
      numOfSchools[(int)(sqrt(e.first))] -= e.second;
  }
  long long ans = 0;

  for(long long i = 1; i <= (int)(newSchool.back().first / 2); i++){
    if(numOfSchools[i] <= 1) continue;

    if(ans < i * numOfSchools[i])
      ans = i * numOfSchools[i];
  }
  for(auto e : newSchool){
    if(e.second <= 1) continue;
    if(ans < (long long)(e.first) * e.second)
      ans = (long long)(e.first) * e.second;
  }

  cout << ans;

  return 0;
}