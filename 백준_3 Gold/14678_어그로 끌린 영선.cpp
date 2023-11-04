////231103
//41m 25s

#include <iostream>
#include <vector>

using namespace std;

int N;

vector<vector<int>> tree;

vector<bool> visited;

int evenLeaves = 0;
int oddLeaves = 0;

bool evenMid = false;
bool oddMid = false;

void findLeaves(int curInd, int level) {
    visited[curInd] = true;

    if (tree[curInd].size() == 1) {
        if (level % 2 == 0)
            evenLeaves++;
        else
            oddLeaves++;
    }
    else {
        if (level % 2 == 0)
            evenMid = true;
        else
            oddMid = true;
    }

    for (auto e : tree[curInd]) {
        if (visited[e]) continue;

        findLeaves(e, level + 1);
    }

    visited[curInd] = false;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N;

    if(N == 1){
      cout << 1;
      return 0;
    }

    tree = vector<vector<int>>(N + 1);
    for (int i = 0; i < N - 1; i++) {
        int a, b;
        cin >> a >> b;
        tree[a].push_back(b);
        tree[b].push_back(a);
    }

    visited = vector<bool>(N + 1, false);

    findLeaves(1, 1);

    if (evenLeaves > oddLeaves) {
        if (evenMid == false)
            cout << evenLeaves - 1;
        else
            cout << evenLeaves;
    }
    else {
        if (oddMid == false)
            cout << oddLeaves - 1;
        else
            cout << oddLeaves;
    }

    return 0;
}