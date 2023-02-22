////23.02.22
//이해 및 설계 : 1m 45s
//입력 : 2m 2s
//구현 : 24m 12s

//tot : 27m 59s

#include <iostream>
#include <queue>
#include <vector>
#include <string>

using namespace std;

int dir[4][2] = {
    { -1, 0 },
    { 0, 1 },
    { 1, 0},
    { 0, -1}
};
class node {
public:
    int th;
    int i;
    int j;

    node(int th, int i, int j) {
        this->th = th;
        this->i = i;
        this->j = j;
    }

    bool operator< (node b) const {
        return this->th > b.th;
    }
};

int main() {
    int N, M;
    cin >> N >> M;
    vector<string> maze(N);
    for (int i = 0; i < N; i++)
        cin >> maze[i];

    priority_queue<node> PQ;

    PQ.push(node(1, 0, 0));

    vector<vector<bool>> ifPassed(N, vector<bool>(M, false));

    while (!PQ.empty()) {
        node curNode = PQ.top();
        PQ.pop();
        if (ifPassed[curNode.i][curNode.j]) continue;
        if (curNode.i == N - 1 && curNode.j == M - 1) {
            cout << curNode.th;
            break;
        };
        ifPassed[curNode.i][curNode.j] = true;

        for (int i = 0; i < 4; i++) {
            if (0 <= curNode.i + dir[i][0] && curNode.i + dir[i][0] < N) {
                if (0 <= curNode.j + dir[i][1] && curNode.j + dir[i][1] < M) {
                    if (maze[curNode.i + dir[i][0]][curNode.j + dir[i][1]] == '1') {
                        PQ.push(node(curNode.th + 1, curNode.i + dir[i][0], curNode.j + dir[i][1]));
                    }
                }
            }
        }

    }

    return 0;
}