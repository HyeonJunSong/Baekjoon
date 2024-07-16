#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

#define ll long long

class Node{
public:
    ll leftMaxSum;
    ll rightMaxSum;
    ll maxSum;
    ll totSum;
};

int leafNum = 1;
vector<Node> tree;

void segInit(int N){
    while(leafNum < N) leafNum *= 2;
    tree = vector<Node>(leafNum * 2);
}

void segClear(){
    for(int i = 0; i < 2 * leafNum; i++){
        tree[i].leftMaxSum = 0;
        tree[i].rightMaxSum = 0;
        tree[i].maxSum = 0;
        tree[i].totSum = 0;
    }
}

void segUpdate(int target, ll val){
    int curIdx = leafNum + target;

    tree[curIdx].leftMaxSum += val;
    tree[curIdx].rightMaxSum += val;
    tree[curIdx].maxSum += val;
    tree[curIdx].totSum += val;

    curIdx >>= 1;

    while(curIdx > 0){
        tree[curIdx].leftMaxSum = max(tree[2 * curIdx].leftMaxSum, tree[2 * curIdx].totSum + tree[2 * curIdx + 1].leftMaxSum);
        tree[curIdx].rightMaxSum  = max(tree[2 * curIdx + 1].rightMaxSum, tree[2 * curIdx + 1].totSum + tree[2 * curIdx].rightMaxSum);
        tree[curIdx].maxSum = max(tree[2 * curIdx].rightMaxSum + tree[2 * curIdx + 1].leftMaxSum, max(tree[2 * curIdx].maxSum, tree[2 * curIdx + 1].maxSum));
        tree[curIdx].totSum = tree[2 * curIdx].totSum + tree[2 * curIdx + 1].totSum;

        curIdx >>= 1;
    }
}

int main(){

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int N;
    cin >> N;

    vector<pair<pair<int, int>, ll>> golds(N);
    map<int, int> yMap;
    for(int i = 0; i < N; i++){
        cin >> golds[i].first.first >> golds[i].first.second >> golds[i].second;
        yMap[golds[i].first.second] = 0;
    }

    int yIdx = 0;
    for(auto e: yMap)
        yMap[e.first] = yIdx++;

    sort(golds.begin(), golds.end());
    vector<vector<pair<int, ll>>> xMap;
    for(int i = 0; i < N; i++){
        if(i == 0 || golds[i - 1].first.first != golds[i].first.first)
            xMap.push_back(vector<pair<int, ll>>(1, {golds[i].first.second, golds[i].second}));
        else
            xMap.back().push_back({golds[i].first.second, golds[i].second});
    }

    segInit(yMap.size());

    ll ans = 0;
    for(int i = 0; i < xMap.size(); i++){
        segClear();
        for(int j = i; j < xMap.size(); j++){
            for(auto e: xMap[j])
                segUpdate(yMap[e.first], e.second);
            ans = max(ans, tree[1].maxSum);
        }
    }

    cout << ans;

    return 0;
}