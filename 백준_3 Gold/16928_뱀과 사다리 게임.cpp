////22.12.13
//1h 52m 09s

#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <algorithm>
#include <map>

using namespace std;

bool comp(vector<int> a, vector<int> b) {
    return a[0] < b[0];
}

class node {
public:
    int cnt;
    int pos;

    node(int cnt, int pos) {
        this->cnt = cnt;
        this->pos = pos;
    };

    bool operator<(node a) const {
        return cnt > a.cnt;
    }
};

int main() {
    int N, M;
    cin >> N >> M;
    // 0: 사다리, 1: 뱀

    map<int, int> dic;

    for (int i = 0; i < N; i++) {
        int u, v;
        cin >> u >> v;
        dic.emplace(u, v);
    }

    for (int i = 0; i < M; i++) {
        int u, v;
        cin >> u >> v;
        dic.emplace(u, v);
    }

    priority_queue<node> PQ;
    PQ.push(node(0, 1));

    while (true) {
        node cur = PQ.top();
        PQ.pop();

        if (cur.pos >= 100) {
            cout << cur.cnt;
            break;
        }

        int maxPath;
        for (int i = 1; i <= 6; i++) {
            auto dicFind = dic.find(cur.pos + i);
            if (dicFind != dic.end()) {
                PQ.push(node(cur.cnt + 1, dicFind->second));
            }
            else {
                maxPath = i;
            }
        }
        PQ.push(node(cur.cnt + 1, cur.pos + maxPath));

    }

    return 0;
}