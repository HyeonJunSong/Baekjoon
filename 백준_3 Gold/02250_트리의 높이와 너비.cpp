#include <iostream>
#include <vector>

using namespace std;

vector<pair<int,int>> tree;
vector<vector<int>> levels;

int curInd = 0;

void LVR(int curNode, int level);

int main(){
    int N;
    cin >> N;

    tree = vector<pair<int,int>>(N + 1, pair<int, int>(-1, -1));
    vector<bool> ifParentExist(N + 1, false);
    int node, left, right;
    for(int i = 0; i < N; i++){
        cin >> node >> left >> right;
        tree[node].first = left;
        tree[node].second = right;

        if(left != -1)
            ifParentExist[left] = true;
        if(right != -1)
            ifParentExist[right] = true;
    }

    levels = vector<vector<int>>(N + 1, vector<int>());

    int root;
    for(int i = 1; i <= N; i++)
        if(!ifParentExist[i]){
            root = i;
            break;
        }
    
    LVR(root, 1);

    int maxLevel = 0;
    int maxWidth = 0;

    for(int i = 1; i <= N; i++){
        if(levels[i].size() == 0) continue;
        int curWidth = levels[i].back() - levels[i].front() + 1;
        if(maxWidth < curWidth){
            maxWidth = curWidth;
            maxLevel = i;
        }
    }

    cout << maxLevel << ' ' << maxWidth;

    return 0;
}

void LVR(int curNode, int level){
    if(tree[curNode].first != -1)
        LVR(tree[curNode].first, level + 1);

    curInd++;
    levels[level].push_back(curInd);

    if(tree[curNode].second != -1)
        LVR(tree[curNode].second, level + 1);
}