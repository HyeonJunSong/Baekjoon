#include <iostream>
#include <map>
#include <vector>
#include <set>

using namespace std;

vector<vector<int>> memo;
vector<map<int, int>> tree;
int V;
int DFS(int byCur, set<int>& passed, int curNode);

int main() {
    cin >> V;
    tree = vector<map<int, int>>(V, map<int, int>());
    vector<int> leaves;
    for (int i = 0; i < V; i++) {
        int ver;
        cin >> ver;
        ver--;
        int target, val;
        cin >> target;
        while (target != -1) {
            target--;
            cin >> val;
            tree[ver].insert(make_pair(target, val));
            cin >> target;
        }

        if(tree[ver].size() == 1) leaves.push_back(ver);
    }

    int ans = 0;
    for(int i = 0; i < leaves.size(); i++){
        for(int j = i + 1; j < leaves.size(); j++){
            set<int> passed;
            int ret = DFS(0, passed, leaves[i]);
            if(ans < ret) ans = ret;
        }
    }

    cout << ans;

    return 0;
}

int DFS(int byCur, set<int>& passed, int curNode){
    int ans = 0;

    if(tree[curNode].size() == 1) return tree[curNode].begin()->second;

    passed.insert(curNode);
    for(auto iter = tree[curNode].begin(); iter != tree[curNode].end(); iter++){
        if(passed.find(iter->first) != passed.end()) continue;
        int res = DFS(byCur + iter->second, passed, iter->first);
        if(res > ans) ans = res;
    }
    passed.erase(curNode);
    return ans;
}