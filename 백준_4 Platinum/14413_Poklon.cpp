#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <cmath>
#include <map>

using namespace std;

int bucketNum;
bool comp(pair<pair<int, int>, int> a, pair<pair<int, int>, int> b){
    if(a.first.first / bucketNum == b.first.first / bucketNum)
        return a.first.second < b.first.second;
    return a.first.first / bucketNum < b.first.first / bucketNum;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int N, Q;
    cin >> N >> Q;
    bucketNum = (int)(sqrt(N));

    vector<int> arr(N + 1);
    map<int, int> numMap;
    for(int i = 1; i <= N; i++){
        cin >> arr[i];
        numMap[arr[i]] = 0;
    }

    int numMapSize = 0;
    for(auto e: numMap)
        numMap[e.first] = numMapSize++;
    
    for(int i = 1; i <= N; i++)
        arr[i] = numMap[arr[i]];

    vector<pair<pair<int, int>, int>> query(Q);
    for(int i = 0; i < Q; i++){
        cin >> query[i].first.first >> query[i].first.second;
        query[i].second = i;
    }
    sort(query.begin(), query.end(), comp);

    vector<int> ans(Q, 0);

    vector<int> cntOfNum(numMapSize, 0);

    for(int i = query[0].first.first; i <= query[0].first.second; i++){
        if(cntOfNum[arr[i]] == 2) ans[query[0].second]--;
        cntOfNum[arr[i]]++;
        if(cntOfNum[arr[i]] == 2) ans[query[0].second]++;
    }

    for(int i = 1; i < Q; i++){

        ans[query[i].second] = ans[query[i - 1].second];

        for(int j = query[i - 1].first.first; j < query[i].first.first; j++){
            if(cntOfNum[arr[j]] == 2) ans[query[i].second]--;
            cntOfNum[arr[j]]--;
            if(cntOfNum[arr[j]] == 2) ans[query[i].second]++;
        }
        for(int j = query[i - 1].first.first - 1; j >= query[i].first.first; j--){
            if(cntOfNum[arr[j]] == 2) ans[query[i].second]--;
            cntOfNum[arr[j]]++;
            if(cntOfNum[arr[j]] == 2) ans[query[i].second]++;
        }

        for(int j = query[i - 1].first.second + 1; j <= query[i].first.second; j++){
            if(cntOfNum[arr[j]] == 2) ans[query[i].second]--;
            cntOfNum[arr[j]]++;
            if(cntOfNum[arr[j]] == 2) ans[query[i].second]++;
        }
        for(int j = query[i - 1].first.second; j > query[i].first.second; j--){
            if(cntOfNum[arr[j]] == 2) ans[query[i].second]--;
            cntOfNum[arr[j]]--;
            if(cntOfNum[arr[j]] == 2) ans[query[i].second]++;
        }

    }

    for(auto e: ans)
        cout << e << "\n";

    return 0;
}