#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>
#include <cmath>

using namespace std;

int bucketNum;
int N, K;
bool comp(pair<pair<int, int>, int> a, pair<pair<int, int>, int> b){
    if(a.first.first / bucketNum == b.first.first / bucketNum)
        return a.first.second < b.first.second;
    return a.first.first / bucketNum < b.first.first / bucketNum;
}

int leafNum = 1;
vector<int> segTree;
void segInit(int k){
    while(leafNum < k) leafNum *= 2;
    segTree = vector<int>(leafNum * 2);
}
void segClear(){
    for(int i = 0; i < 2 * leafNum; i++)
        segTree[i] = 0;
}
void segUpdate(int target, int val){
    int curIdx = target + leafNum;
    
    segTree[curIdx] = val;
    curIdx /= 2;

    while(curIdx > 0){
        segTree[curIdx] = max(segTree[2 * curIdx], segTree[2 * curIdx + 1]);
        curIdx /= 2;
    }
}

int main(){

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> N >> K;
    bucketNum = (int)(sqrt(N));

    vector<int> A;
    A.assign(N + 1, 0);
    for(int i = 1; i <= N; i++)
        cin >> A[i];
    
    int M;
    cin >> M;
    vector<pair<pair<int, int>, int> > query;
    query.assign(M, {{0, 0}, 0});
    for(int i = 0; i < M; i++){
        cin >> query[i].first.first >> query[i].first.second;
        query[i].second = i;
    }
    vector<int> ans;
    ans.assign(M, 0);

    sort(query.begin(), query.end(), comp);
    // for(int i = 0; i < M; i++)
    //     cout << query[i].first.first << " " << query[i].first.second << endl;

    segInit(K + 1);
    vector<deque<int> > numIdxes(K + 1);


    for(int i = 0; i < M; i++){
        int curAns = 0;

        if(i == 0 || (query[i - 1].first.first / bucketNum) != (query[i].first.first / bucketNum)){
            for(int j = 0; j < K + 1; j++)
                numIdxes[j].clear();
            segClear();

            for(int j = query[i].first.first; j <= query[i].first.second; j++){
                numIdxes[A[j]].push_back(j);
                if(numIdxes[A[j]].size() >= 2 && segTree[leafNum + A[j]] < ((numIdxes[A[j]].back()) - (numIdxes[A[j]].front())))
                    segUpdate(A[j], ((numIdxes[A[j]].back()) - (numIdxes[A[j]].front())));
            }

            curAns = max(curAns, segTree[1]);
        } else{


            for(int j = query[i - 1].first.second + 1; j <= query[i].first.second; j++){
                numIdxes[A[j]].push_back(j);
                if(numIdxes[A[j]].size() >= 2 && segTree[leafNum + A[j]] < ((numIdxes[A[j]].back()) - (numIdxes[A[j]].front())))
                    segUpdate(A[j], ((numIdxes[A[j]].back()) - (numIdxes[A[j]].front())));
            }


            if(query[i - 1].first.first < query[i].first.first){
                for(int j = query[i - 1].first.first; j < query[i].first.first; j++){
                    numIdxes[A[j]].pop_front();
                    if(numIdxes[A[j]].size() <= 1){
                        if(segTree[leafNum + A[j]] != 0)
                            segUpdate(A[j], 0);
                    } else {
                        if(segTree[leafNum + A[j]] != ((numIdxes[A[j]].back()) - (numIdxes[A[j]].front())))
                            segUpdate(A[j], ((numIdxes[A[j]].back()) - (numIdxes[A[j]].front())));
                    }
                }
            } else {
                for(int j = query[i - 1].first.first - 1; j >= query[i].first.first; j--){
                    numIdxes[A[j]].push_front(j);
                    if(numIdxes[A[j]].size() >= 2 && segTree[leafNum + A[j]] < ((numIdxes[A[j]].back()) - (numIdxes[A[j]].front())))
                        segUpdate(A[j], ((numIdxes[A[j]].back()) - (numIdxes[A[j]].front())));
                }
            }

            curAns = max(curAns, segTree[1]);
        }

        ans[query[i].second] = curAns;
    }

    for(int e: ans)
        cout << e << "\n";

    return 0;
}