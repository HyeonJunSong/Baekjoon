#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <cmath>

using namespace std;

int bucketNum;
bool comp(pair<int, pair<int, int>> a, pair<int, pair<int, int>> b){
  if(a.second.first / bucketNum == b.second.first / bucketNum)
    return a.second.second < b.second.second;
  return a.second.first / bucketNum < b.second.first / bucketNum;
}

int main(){

  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  int N;
  cin >> N;
  vector<int> nums(N);
  for(int i = 0; i < N; i++)
    cin >> nums[i];


  int Q;
  cin >> Q;
  vector<pair<int, pair<int, int>>> queries(Q);
  for(int i = 0; i < Q; i++){
    queries[i].first = i;
    cin >> queries[i].second.first >> queries[i].second.second;
  }
  bucketNum = (int)(sqrt(Q));
  sort(queries.begin(), queries.end(), comp);


  vector<int> ans(Q);

  vector<int> segTree;
  for(int q = 0; q < Q; q++){
    if(q == 0 || (queries[q - 1].second.first / bucketNum < queries[q].second.first / bucketNum)){
      segTree = vector<int>(131072 * 2, 0);

      for(int i = queries[q].second.first; i <= queries[q].second.second; i++){
        int curNum = 131072 + nums[i - 1];
        segTree[curNum]++;
        curNum /= 2;
        while(curNum >= 1){
          segTree[curNum] = max(segTree[2 * curNum], segTree[2 * curNum + 1]);
          curNum /= 2;
        }
      }
    } else {

      if(queries[q - 1].second.first < queries[q].second.first){
        for(int i = queries[q - 1].second.first; i < queries[q].second.first; i++){
          int curNum = 131072 + nums[i - 1];
          segTree[curNum]--;
          curNum /= 2;
          while(curNum >= 1){
            segTree[curNum] = max(segTree[2 * curNum], segTree[2 * curNum + 1]);
            curNum /= 2;
          }
        }
      } else {
        for(int i = queries[q - 1].second.first - 1; i >= queries[q].second.first; i--){
          int curNum = 131072 + nums[i - 1];
          segTree[curNum]++;
          curNum /= 2;
          while(curNum >= 1){
            segTree[curNum] = max(segTree[2 * curNum], segTree[2 * curNum + 1]);
            curNum /= 2;
          }
        }
      }

      if(queries[q - 1].second.second <= queries[q].second.second){
        for(int i = queries[q - 1].second.second + 1; i <= queries[q].second.second; i++){
          int curNum = 131072 + nums[i - 1];
          segTree[curNum]++;
          curNum /= 2;
          while(curNum >= 1){
            segTree[curNum] = max(segTree[2 * curNum], segTree[2 * curNum + 1]);
            curNum /= 2;
          }
        }
      } else {
        for(int i = queries[q - 1].second.second; i > queries[q].second.second; i--){
          int curNum = 131072 + nums[i - 1];
          segTree[curNum]--;
          curNum /= 2;
          while(curNum >= 1){
            segTree[curNum] = max(segTree[2 * curNum], segTree[2 * curNum + 1]);
            curNum /= 2;
          }
        }
      }
    }

    ans[queries[q].first] = segTree[1];
  }

  for(auto e: ans)
    cout << e << "\n";
  

  


  return 0;
}