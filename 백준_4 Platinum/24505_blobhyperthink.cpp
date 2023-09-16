#include <iostream>
#include <vector>

using namespace std;

#define modNum 1000000007

class Tree {
public:
    int leafSize;
    vector<pair<int, pair<int, int>>> tree;

    Tree(int n) {

        //tree 배열 사이즈 계산 및 할당
        int k = 1;
        while (k <= n)
            k *= 2;

        leafSize = k;
        k *= 2;
        tree = vector<pair<int, pair<int, int>>>(k, { 0, {0, 0} });

        //말단 노드 초기화
        for (int i = 0; i < leafSize; i++) {
            tree[leafSize + i] = { 0, {i, i + 1} };
        }

        //중간 노드 초기화
        for (int i = leafSize - 1; i > 0; i--) {
            tree[i].first = tree[2 * i].first + tree[2 * i + 1].first;
            tree[i].second.first = tree[2 * i].second.first;
            tree[i].second.second = tree[2 * i + 1].second.second;
        }
    }

    int getSumUpTo(int ind) {
        return getSumRec(0, ind + 1, 1);
    }
    int getSumRec(int st, int ed, int curInd) {

        if (tree[curInd].second.first == st && tree[curInd].second.second == ed)
            return tree[curInd].first;

        //좌측
        if (ed <= tree[2 * curInd].second.second) {
            return getSumRec(st, ed, 2 * curInd);
        }
        //우측
        if (ed <= tree[2 * curInd + 1].second.first) {
            return getSumRec(st, ed, 2 * curInd + 1);
        }

        //가르기
        return (getSumRec(st, tree[2 * curInd].second.second, 2 * curInd) + getSumRec(tree[2 * curInd + 1].second.first, ed, 2 * curInd + 1)) % modNum;

    }

    void addVal(int ind, int val) {

        int curInd = leafSize + ind;
        while (curInd >= 1) {
            tree[curInd].first += val;
            tree[curInd].first %= modNum;
            curInd /= 2;
        }
    }

};


int main() {

    int N;
    cin >> N;
    vector<int> inpArr(N);
    for (int i = 0; i < N; i++) {
        cin >> inpArr[i];
        inpArr[i]--;
    }

    vector<Tree> trees(11, Tree(N));

    for (int i = 0; i < N; i++) {
        trees[0].addVal(inpArr[i], 1);
        if (inpArr[i] == 0) continue;
        for (int j = 1; j < 11; j++) {
            trees[j].addVal(inpArr[i], trees[j - 1].getSumUpTo(inpArr[i] - 1));
        }
    }

    cout << trees[10].getSumUpTo(N - 1);

    return 0;
}