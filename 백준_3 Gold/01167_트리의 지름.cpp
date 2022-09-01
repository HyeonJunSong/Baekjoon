#include <iostream>
#include <map>
#include <vector>

using namespace std;

vector<vector<int>> memo;
vector<map<int, int>> tree;
int V;

void DFS(map<int, int> byCur, int st, int ed);

int main() {
    cin >> V;
    tree = vector<map<int, int>>(V, map<int, int>());
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
    }

    memo = vector<vector<int>>(V, vector<int>(V, -1));

    int ans = -1;
    for (int i = 0; i < V; i++) {
        for (int j = i + 1; j < V; j++) {
            if (memo[i][j] == -1) DFS(map<int, int>(), i, j);
            if (ans < memo[i][j]) ans = memo[i][j];
        }
    }

    cout << ans;

    return 0;
}

void DFS(map<int, int> byCur, int st, int ed) {
    if (st == ed) return;

    for (auto iter = tree[st].begin(); iter != tree[st].end(); iter++) {
        if (memo[st][iter->first] != -1) continue;

        map<int, int> temp = byCur;
        temp.emplace(iter->first, 0);
        for (auto iter2 = temp.begin(); iter2 != temp.end(); iter2++) {
            temp[iter2->first] += iter->second;
            memo[iter->first][iter2->first] = iter2->second;
            memo[iter2->first][iter->first] = iter2->second;
        }
        DFS(temp, iter->first, ed);
    }

    return;
}