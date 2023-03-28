#include <iostream>
#include <vector>

using namespace std;

vector<vector<int>> tree;
vector<pair<int, int>> parentAndLevel;

void initParent(int parentInd, int curLevel);
int findLCA(pair<int, int> pairs);

int main() {

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int N;
    cin >> N;

    tree = vector<vector<int>>(N + 1);
    parentAndLevel = vector<pair<int, int>>(N + 1);

    int st, ed;
    for (int i = 0; i < N - 1; i++) {
        cin >> st >> ed;
        tree[st].push_back(ed);
        tree[ed].push_back(st);
    }

    initParent(1, 1);

    int M;
    cin >> M;
    pair<int, int> curPair;
    for (int i = 0; i < M; i++) {
        cin >> curPair.first >> curPair.second;
        cout << findLCA(curPair) << '\n';
    }

    return 0;
}

void initParent(int parentInd, int curLevel) {
    for (auto iter = tree[parentInd].begin(); iter != tree[parentInd].end(); iter++) {
        if (*iter == parentAndLevel[parentInd].first) continue;
        parentAndLevel[*iter] = pair<int, int>(parentInd, curLevel);
        initParent(*iter, curLevel + 1);
    }
}

int findLCA(pair<int, int> pairs) {
    if(parentAndLevel[pairs.first].second > parentAndLevel[pairs.second].second){
        int difference = parentAndLevel[pairs.first].second - parentAndLevel[pairs.second].second;
        for(int i = 0; i < difference; i++)
            pairs.first = parentAndLevel[pairs.first].first;
    }
    else if(parentAndLevel[pairs.first].second < parentAndLevel[pairs.second].second){
        int difference = parentAndLevel[pairs.second].second - parentAndLevel[pairs.first].second;
        for(int i = 0; i < difference; i++)
            pairs.second = parentAndLevel[pairs.second].first;
    }

    while(pairs.first != pairs.second){
        pairs.first = parentAndLevel[pairs.first].first;
        pairs.second = parentAndLevel[pairs.second].first;
    }

    return pairs.first;
}