#include <iostream>
#include <deque>
#include <cmath>
#include <algorithm>
#include <map>
#include <vector>

using namespace std;

int bucketNum;
bool comp(pair<pair<int, int>, int> a, pair<pair<int, int>, int> b){
  if(a.first.first / bucketNum == b.first.first / bucketNum)
    return a.first.second < b.first.second;
  return a.first.first < b.first.first;
}


#define SQRT 320
int len[SQRT * SQRT + 1] = {0};
int lenSqrt[SQRT + 1] = {0};

int getAns(){
  for(int i = SQRT - 1; i >= 0; i--){
    if(lenSqrt[i] == 0) continue;
    for(int j = SQRT - 1; j >= 0; j--){
      if(len[SQRT * i + j] == 0) continue;
      return SQRT * i + j;
    }
  }
}

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  int N;
  cin >> N;

  vector<int> nums(N + 1, 0);
  for(int i = 1; i <= N; i++) cin >> nums[i];
  for(int i = 1; i <= N; i++) nums[i] += nums[i - 1];

  int M;
  cin >> M;
  vector<pair<pair<int, int>, int>> queries(M);
  for(int i = 0; i < M; i++){
    cin >> queries[i].first.first >> queries[i].first.second;
    queries[i].second = i;
  }

  bucketNum = (int)(sqrt(N));
  sort(queries.begin(), queries.end(), comp);


  vector<int> ans(M);

  vector<deque<int>> dqList(200001);

  for(int i = queries[0].first.first - 1; i <= queries[0].first.second; i++){
    if(dqList[100000 + nums[i]].size() > 0){
      len[dqList[100000 + nums[i]].back() - dqList[100000 + nums[i]].front()]--;
      lenSqrt[(dqList[100000 + nums[i]].back() - dqList[100000 + nums[i]].front()) / SQRT]--;
    }

    dqList[100000 + nums[i]].push_back(i);

    len[i - dqList[100000 + nums[i]].front()]++;
    lenSqrt[(i - dqList[100000 + nums[i]].front()) / SQRT]++;
  }
  ans[queries[0].second] = getAns();


  for(int q = 1; q < M; q++){

    if(queries[q - 1].first.first > queries[q].first.first){
      for(int i = queries[q - 1].first.first - 2; i >= queries[q].first.first - 1; i--){

        if(dqList[100000 + nums[i]].size() > 0){
          len[dqList[100000 + nums[i]].back() - dqList[100000 + nums[i]].front()]--;
          lenSqrt[(dqList[100000 + nums[i]].back() - dqList[100000 + nums[i]].front()) / SQRT]--;
        }

        dqList[100000 + nums[i]].push_front(i);
        len[dqList[100000 + nums[i]].back() - dqList[100000 + nums[i]].front()]++;
        lenSqrt[(dqList[100000 + nums[i]].back() - dqList[100000 + nums[i]].front()) / SQRT]++;
      }
    }

    if(queries[q - 1].first.second < queries[q].first.second){
      for(int i = queries[q - 1].first.second + 1; i <= queries[q].first.second; i++){
        if(dqList[100000 + nums[i]].size() > 0){
          len[dqList[100000 + nums[i]].back() - dqList[100000 + nums[i]].front()]--;
          lenSqrt[(dqList[100000 + nums[i]].back() - dqList[100000 + nums[i]].front()) / SQRT]--;
        }

        dqList[100000 + nums[i]].push_back(i);

        len[dqList[100000 + nums[i]].back() - dqList[100000 + nums[i]].front()]++;
        lenSqrt[(dqList[100000 + nums[i]].back() - dqList[100000 + nums[i]].front()) / SQRT]++;
      }
    }

    if(queries[q - 1].first.first < queries[q].first.first){
      for(int i = queries[q - 1].first.first - 1; i < queries[q].first.first - 1; i++){
        len[dqList[100000 + nums[i]].back() - dqList[100000 + nums[i]].front()]--;
        lenSqrt[(dqList[100000 + nums[i]].back() - dqList[100000 + nums[i]].front()) / SQRT]--;

        dqList[100000 + nums[i]].pop_front();

        if(dqList[100000 + nums[i]].size() > 0){
          len[dqList[100000 + nums[i]].back() - dqList[100000 + nums[i]].front()]++;
          lenSqrt[(dqList[100000 + nums[i]].back() - dqList[100000 + nums[i]].front()) / SQRT]++;
        }
      }
    }

    if(queries[q - 1].first.second > queries[q].first.second){
      for(int i = queries[q - 1].first.second; i > queries[q].first.second; i--){
        len[dqList[100000 + nums[i]].back() - dqList[100000 + nums[i]].front()]--;
        lenSqrt[(dqList[100000 + nums[i]].back() - dqList[100000 + nums[i]].front()) / SQRT]--;

        dqList[100000 + nums[i]].pop_back();

        if(dqList[100000 + nums[i]].size() > 0){
          len[dqList[100000 + nums[i]].back() - dqList[100000 + nums[i]].front()]++;
          lenSqrt[(dqList[100000 + nums[i]].back() - dqList[100000 + nums[i]].front()) / SQRT]++;
        }
      }
    }

    ans[queries[q].second] = getAns();
  }

  for(auto e: ans)
    cout << e << '\n';


  return 0;
}