#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#define ll long long

class Node{
public:
    ll lMaxSum;
    ll rMaxSum;
    ll maxSum;
    ll totSum;
};

int leafNum = 1;
vector<Node> segTree;

void segInit(int N){
    while(leafNum < N) leafNum *= 2;
    segTree = vector<Node>(leafNum * 2);
}

void segClear(){
    for(int i = 0; i < 2 * leafNum; i++){
        segTree[i].lMaxSum = 0;
        segTree[i].rMaxSum = 0;
        segTree[i].maxSum = 0;
        segTree[i].totSum = 0;
    }
}

void segUpdateValue(int target, ll val){
    
    int curIdx = leafNum + target;
    segTree[curIdx].lMaxSum += val;
    segTree[curIdx].rMaxSum += val;
    segTree[curIdx].maxSum += val;
    segTree[curIdx].totSum += val;
    curIdx >>= 1;

    while(curIdx > 0){
        segTree[curIdx].lMaxSum = max(segTree[2 * curIdx].lMaxSum, segTree[2 * curIdx].totSum + segTree[2 * curIdx + 1].lMaxSum);
        segTree[curIdx].rMaxSum = max(segTree[2 * curIdx + 1].rMaxSum, segTree[2 * curIdx + 1].totSum + segTree[2 * curIdx].rMaxSum);
        segTree[curIdx].maxSum = max(segTree[2 * curIdx].rMaxSum + segTree[2 * curIdx + 1].lMaxSum , max(segTree[2 * curIdx].maxSum , segTree[2 * curIdx + 1].maxSum));
        segTree[curIdx].totSum = segTree[2 * curIdx].totSum + segTree[2 * curIdx + 1].totSum;
        curIdx >>= 1;
    }

}

int main(){

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int n1, n2;
    ll c1, c2;
    vector<pair<pair<int, int>, ll>> P;

    cin >> n1;
    for(int i = 0; i < n1; i++){
        P.push_back({{0, 0}, 0});
        cin >> P[i].first.first >> P[i].first.second;
    }

    cin >> n2;
    for(int i = 0; i < n2; i++){
        P.push_back({{0, 0}, 0});
        cin >> P[n1 + i].first.first >> P[n1 + i].first.second;
    }

    cin >> c1 >> c2;

    for(int i = 0; i < n1; i++)
        P[i].second = c1;
    for(int i = 0; i < n2; i++)
        P[n1 + i].second = -1 * c2;

    sort(P.begin(), P.end());

    vector<pair<int, int> > yTrans(n1 + n2);
    vector<int> transedY(n1 + n2);
    for(int i = 0; i < n1 + n2; i++)
        yTrans[i] = {P[i].first.second, i};
    sort(yTrans.begin(), yTrans.end());
    for(int i = 0; i < n1 + n2; i++)
        transedY[yTrans[i].second] = i;
    

    segInit(n1 + n2);

    ll ans = 0;
    for(int i = 0; i < n1 + n2; i++){
        segClear();
        for(int j = i; j < n1 + n2; j++){
            segUpdateValue(transedY[j], P[j].second);
            ans = max(ans, segTree[1].maxSum);
        }
    }

    cout << ans;

    return 0;
}