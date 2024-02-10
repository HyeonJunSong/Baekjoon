#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

int N;
vector<vector<int>> tree;
vector<vector<int>> parentOf;
vector<int> levelOf;

void DFS_markParents(int parentNode, int curNode, vector<int>& history);
int getMidPoint(int idx1, int idx2);

int main() {

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> N;
    tree = vector<vector<int>>(N + 1);
    for (int i = 0; i < N - 1; i++) {
        int st, ed;
        cin >> st >> ed;
        tree[st].push_back(ed);
        tree[ed].push_back(st);
    }

    parentOf = vector<vector<int>>(N + 1);
    levelOf = vector<int>(N + 1);

    vector<int> history;
    DFS_markParents(0, 1, history);

    int Q;
    cin >> Q;
    for (int q = 0; q < Q; q++) {
        int A, B, C;
        cin >> A >> B >> C;

        int abMid = getMidPoint(A, B);
        if (abMid == -1) {
            cout << -1 << "\n";
            continue;
        }
        int bcMid = getMidPoint(B, C);
        if (bcMid == -1) {
            cout << -1 << "\n";
            continue;
        }

        if (abMid == bcMid) {
            cout << abMid << "\n";
            continue;
        }

        int caMid = getMidPoint(C, A);
        if (caMid == -1) {
            cout << -1 << "\n";
            continue;
        }

        if (abMid != bcMid && bcMid != caMid && caMid != abMid) {
            cout << -1 << "\n";
            continue;
        }

        if (bcMid == caMid) {
            cout << bcMid << "\n";
            continue;
        }
        if (caMid == abMid) {
            cout << caMid << "\n";
            continue;
        }

    }

    return 0;
}

void DFS_markParents(int parentNode, int curNode, vector<int>& history) {

    levelOf[curNode] = history.size();

    history.push_back(curNode);

    int historySize = history.size();
    for (int i = 1; i < historySize; i *= 2) {
        parentOf[curNode].push_back(history[historySize - i - 1]);
    }

    for (auto e : tree[curNode]) {
        if (e == parentNode) continue;
        DFS_markParents(curNode, e, history);
    }
    history.pop_back();
}

int getMidPoint(int idx1, int idx2) {
    //LCA까지 거리 찾기

    int totLength = 0;

    int tempIdx1 = idx1;
    int tempIdx2 = idx2;

    if (levelOf[tempIdx1] > levelOf[tempIdx2]) {
        while (levelOf[tempIdx1] > levelOf[tempIdx2]) {
            int curStep = 0;
            int curStepLength = 1;
            while (curStepLength <= levelOf[tempIdx1] - levelOf[tempIdx2]) {
                curStep++;
                curStepLength *= 2;
            }
            curStep--;
            curStepLength /= 2;

            totLength += curStepLength;
            tempIdx1 = parentOf[tempIdx1][curStep];
        }
    }
    else {
        while (levelOf[tempIdx2] > levelOf[tempIdx1]) {
            int curStep = 0;
            int curStepLength = 1;
            while (curStepLength <= levelOf[tempIdx2] - levelOf[tempIdx1]) {
                curStep++;
                curStepLength *= 2;
            }
            curStep--;
            curStepLength /= 2;

            totLength += curStepLength;
            tempIdx2 = parentOf[tempIdx2][curStep];
        }
    }

    while (true) {
        int next = -1;
        int st = 0;
        int ed = parentOf[tempIdx1].size() - 1;
        while (st <= ed) {
            int mid = (int)((st + ed) / 2);
            if (parentOf[tempIdx1][mid] != parentOf[tempIdx2][mid])
                st = mid + 1;
            else
                ed = mid - 1;
        }

        if (ed == -1)
            break;

        totLength += 2 * (int)(pow(2, ed));
        tempIdx1 = parentOf[tempIdx1][ed];
        tempIdx2 = parentOf[tempIdx2][ed];
    }

    if (tempIdx1 != tempIdx2)
        totLength += 2;


    //긴쪽에서 절반만큼만 가기
    if (totLength % 2 == 1)
        return -1;
    totLength = (int)(totLength / 2);
    if (levelOf[idx1] > levelOf[idx2]) {
        while (totLength > 0) {
            int curStep = 0;
            int curStepLength = 1;
            while (curStepLength <= totLength) {
                curStep++;
                curStepLength *= 2;
            }
            curStep--;
            curStepLength /= 2;

            idx1 = parentOf[idx1][curStep];
            totLength -= curStepLength;
        }
        return idx1;
    }
    else {
        while (totLength > 0) {
            int curStep = 0;
            int curStepLength = 1;
            while (curStepLength <= totLength) {
                curStep++;
                curStepLength *= 2;
            }
            curStep--;
            curStepLength /= 2;

            idx2 = parentOf[idx2][curStep];
            totLength -= curStepLength;
        }
        return idx2;
    }
}