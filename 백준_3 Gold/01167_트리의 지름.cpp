#include <iostream>
#include <vector>
#include <set>
#include <map>

using namespace std;

vector<map<int, int>> tree;

vector<map<int, int>> memo;

int getLongestPath(int st, int target, set<int> path);

int main() {
    int V;
    cin >> V;

    tree = vector<map<int, int>>(V, map<int, int>());

    vector<int> edgeNodes;


    for (int i = 0; i < V; i++) {
        int nodeNum;
        cin >> nodeNum;
        nodeNum--;

        int targetNode, edgeVal;
        cin >> targetNode;
        targetNode--;
        while (targetNode != -2) {
            cin >> edgeVal;
            tree[nodeNum][targetNode] = edgeVal;
            cin >> targetNode;
            targetNode--;
        }
        if (tree[nodeNum].size() == 1) edgeNodes.push_back(nodeNum);
    }

    memo = vector<map<int, int>>(V, map<int, int>());

    //edgeNode 돌면서 최장거리 구하기.
    int longest = 0;
    for (int i = 0; i < edgeNodes.size(); i++) {
        for (int j = i + 1; j < edgeNodes.size(); j++) {
            int res = getLongestPath(edgeNodes[i], edgeNodes[j], set<int>());
            if (res > longest) longest = res;
        }
    }

    cout << longest;

    return 0;
}

int getLongestPath(int st, int target, set<int> path) {
    if (tree[st].find(target) != tree[st].end()) return tree[st][target];

    int longest = 0;

    for (auto iter = tree[st].begin(); iter != tree[st].end(); iter++) {
        if (path.find(iter->first) == path.end()) {
            if (memo[iter->first].find(target) == memo[iter->first].end()) {
                path.insert(st);
                memo[iter->first][target] = getLongestPath(iter->first, target, path);
                path.erase(st);
            }

            if (memo[iter->first][target] + iter->second > longest) longest = memo[iter->first][target] + iter->second;
        }
    }

    return longest;
}