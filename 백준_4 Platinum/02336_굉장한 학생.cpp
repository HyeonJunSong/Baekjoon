#include <iostream>
#include <vector>

using namespace std;

int N;
vector<vector<int>> grade;
vector<vector<int>> indexOfGrade;
vector<vector<pair<pair<int, int>, vector<int>>>> gradeTree;

vector<int> mergeList(vector<int> list1, vector<int> list2);
void initTree();
vector<int> getSetOfRange(int treeInd, int st, int ed);
bool ifGreaterThanExists(int num);

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N;

    grade = vector<vector<int>>(3, vector<int>(N));
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < N; j++)
            cin >> grade[i][j];
    indexOfGrade = vector<vector<int>>(3, vector<int>(N + 1));
    for (int i = 0; i < N; i++) {
        indexOfGrade[0][grade[0][i]] = i;
        indexOfGrade[1][grade[1][i]] = i;
        indexOfGrade[2][grade[2][i]] = i;
    }

    initTree();

    int ans = 0;
    for (int i = 1; i < N + 1; i++)
        if (!ifGreaterThanExists(i))
            ans += 1;

    cout << ans;

    return 0;
}


vector<int> mergeList(vector<int> list1, vector<int> list2) {

    vector<int> newList;
    int idx1 = 0;
    int idx2 = 0;

    while (idx1 < list1.size() && idx2 < list2.size()) {
        if (list1[idx1] < list2[idx2]) {
            newList.push_back(list1[idx1]);
            idx1 += 1;
        }
        else {
            newList.push_back(list2[idx2]);
            idx2 += 1;
        }
    }
    if (idx1 < list1.size())
        newList.insert(newList.end(), list1.begin() + idx1, list1.end());
    if (idx2 < list2.size())
        newList.insert(newList.end(), list2.begin() + idx2, list2.end());
    return newList;
}

void initTree() {
    int leafNum = 1;
    while (leafNum < N)
        leafNum *= 2;
    gradeTree = vector<vector<pair<pair<int, int>, vector<int>>>>(3, vector<pair<pair<int, int>, vector<int>>>(leafNum * 2 + 1));
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < N; j++) {
            gradeTree[i][leafNum + j].first.first = j;
            gradeTree[i][leafNum + j].first.second = j + 1;
            gradeTree[i][leafNum + j].second = vector<int>(1, grade[i][j]);
        }
        for (int j = N; j < leafNum; j++) {
            gradeTree[i][leafNum + j].first.first = j;
            gradeTree[i][leafNum + j].first.second = j + 1;
        }
        for (int j = leafNum - 1; j > 0; j--) {
            gradeTree[i][j].first.first = gradeTree[i][2 * j].first.first;
            gradeTree[i][j].first.second = gradeTree[i][2 * j + 1].first.second;
            gradeTree[i][j].second = mergeList(gradeTree[i][2 * j].second, gradeTree[i][2 * j + 1].second);
        }

    }
}

vector<int> getSetOfRange(int treeInd, int st, int ed) {

    vector<int> res;
    vector<vector<int>> stack(1, { st, ed, 1 });
    while (!stack.empty()) {
        vector<int> cur = stack.back();
        stack.pop_back();

        if (gradeTree[treeInd][cur[2]].first.first == cur[0] && gradeTree[treeInd][cur[2]].first.second == cur[1]) {
            res = mergeList(res, gradeTree[treeInd][cur[2]].second);
            continue;
        }
        if (gradeTree[treeInd][2 * cur[2]].first.second >= cur[1]) {
            stack.push_back({ cur[0], cur[1], 2 * cur[2] });
            continue;
        }
        if (gradeTree[treeInd][2 * cur[2] + 1].first.first <= cur[0]) {
            stack.push_back({ cur[0], cur[1], 2 * cur[2] + 1 });
            continue;
        }
        stack.push_back({ cur[0], gradeTree[treeInd][2 * cur[2]].first.second, 2 * cur[2] });
        stack.push_back({ gradeTree[treeInd][2 * cur[2] + 1].first.first, cur[1], 2 * cur[2] + 1 });
    }

    return res;
}

bool ifGreaterThanExists(int num) {
    vector<int> g1Set = getSetOfRange(0, 0, indexOfGrade[0][num]);
    vector<int> g2Set = getSetOfRange(1, 0, indexOfGrade[1][num]);
    vector<int> g3Set = getSetOfRange(2, 0, indexOfGrade[2][num]);

    int idx1 = 0;
    int idx2 = 0;
    int idx3 = 0;

    while (idx1 < g1Set.size() && idx2 < g2Set.size() && idx3 < g3Set.size()) {
        if (g1Set[idx1] == g2Set[idx2] && g2Set[idx2] == g3Set[idx3])
            return true;

        if (g1Set[idx1] < g2Set[idx2]) {
            if (g1Set[idx1] < g3Set[idx3])
                idx1 += 1;
            else
                idx3 += 1;
        }
        else {
            if (g2Set[idx2] < g3Set[idx3])
                idx2 += 1;
            else
                idx3 += 1;
        }
    }
    return false;
}