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

int leafNum = 262144;
vector<int> segTree(2 * leafNum, 0);

void segUpdate(int idx, int val){
  idx += leafNum;

  segTree[idx] = val;
  idx /= 2;
  while(idx > 0){
    segTree[idx] = max(segTree[2 * idx], segTree[2 * idx + 1]);
    idx /= 2;
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
    dqList[100000 + nums[i]].push_back(i);
    segUpdate(100000 + nums[i], i - dqList[100000 + nums[i]].front());
  }
  ans[queries[0].second] = segTree[1];


  for(int q = 1; q < M; q++){

    if(queries[q - 1].first.first > queries[q].first.first){
      for(int i = queries[q - 1].first.first - 2; i >= queries[q].first.first - 1; i--){
        dqList[100000 + nums[i]].push_front(i);
        segUpdate(100000 + nums[i], dqList[100000 + nums[i]].back() - i);
      }
    }

    if(queries[q - 1].first.second < queries[q].first.second){
      for(int i = queries[q - 1].first.second + 1; i <= queries[q].first.second; i++){
        dqList[100000 + nums[i]].push_back(i);
        segUpdate(100000 + nums[i], i - dqList[100000 + nums[i]].front());
      }
    }

    if(queries[q - 1].first.first < queries[q].first.first){
      for(int i = queries[q - 1].first.first - 1; i < queries[q].first.first - 1; i++){
        dqList[100000 + nums[i]].pop_front();
        if(dqList[100000 + nums[i]].size() > 0)
          segUpdate(100000 + nums[i], dqList[100000 + nums[i]].back() - dqList[100000 + nums[i]].front());
      }
    }

    if(queries[q - 1].first.second > queries[q].first.second){
      for(int i = queries[q - 1].first.second; i > queries[q].first.second; i--){
        dqList[100000 + nums[i]].pop_back();
        if(dqList[100000 + nums[i]].size() > 0)
          segUpdate(100000 + nums[i], dqList[100000 + nums[i]].back() - dqList[100000 + nums[i]].front());
      }
    }

    ans[queries[q].second] = segTree[1];
  }

  for(auto e: ans)
    cout << e << '\n';


  return 0;
}