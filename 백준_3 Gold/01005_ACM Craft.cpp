#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class node {
public:
    int NeededTime;
    int parentNum;
    vector<int> children;

    node() {
        NeededTime = 0;
        parentNum = 0;
        children = vector<int>();
    }
};

void pushRootNode(queue<int>& Q, vector<node>& tree, vector<int>& D);
void obtainMaxNode(queue<int>& Q, vector<node>& tree, vector<int>& D);

int main() {
    int T;
    cin >> T;

    for (int t = 0; t < T; t++) {
        int N, K;
        cin >> N >> K;
        vector<int> D(N + 1);
        for (int i = 1; i <= N; i++)
            cin >> D[i];

        vector<node> tree(N + 1, node());

        for (int i = 0; i < K; i++) {
            int st, ed;
            cin >> st >> ed;
            tree[st].children.push_back(ed);
            tree[ed].parentNum++;
        }

        int targetBuilding;
        cin >> targetBuilding;

        queue<int> Q;

        while (true) {
            pushRootNode(Q, tree, D);
            if (Q.empty())
                break;
            obtainMaxNode(Q, tree, D);
        }
        cout << D[targetBuilding] << endl;
    }

}

void pushRootNode(queue<int>& Q, vector<node>& tree, vector<int>& D) {
    for (int i = 1; i < tree.size(); i++) {
        if (tree[i].parentNum == 0) {
            Q.push(i);
            D[i] += tree[i].NeededTime;
            tree[i].parentNum--;
        }
    }
}

void obtainMaxNode(queue<int>& Q, vector<node>& tree, vector<int>& D) {
    while (!Q.empty()) {
        int curNode = Q.front();
        Q.pop();

        for (int i = 0; i < tree[curNode].children.size(); i++) {
            if (tree[tree[curNode].children[i]].NeededTime < D[curNode])
                tree[tree[curNode].children[i]].NeededTime = D[curNode];
            tree[tree[curNode].children[i]].parentNum--;
        }
    }
}