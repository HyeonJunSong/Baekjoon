#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

int N;
int lastN;
vector<long long> numArr;

vector<pair<int, long long>> segTree_min;
vector<long long> segTree_sum;

#define MAX 987654321

void initMinSegTree();
pair<int, long long> getMinNumFromRange(pair<int, int> targetRange, pair<int, int> curRange, int curTreeInd);
void initSumSegTree();
long long getSumFromRange(pair<int, int> targetRange, pair<int, int> curRange, int curTreeInd);
long long getMaxScoreFromRange(pair<int, int> targetRange);

int main() {
    cin >> N;
    numArr = vector<long long>(N);
    for (int i = 0; i < N; i++)
        cin >> numArr[i];

    lastN = (int)(pow(2, ceil(log2(N))));

    initMinSegTree();
    initSumSegTree();
    cout << getMaxScoreFromRange({ 0, lastN - 1 });

    return 0;
}

void initMinSegTree() {
    int depth = (int)(ceil(log2(N)));
    segTree_min = vector<pair<int, long long>>((int)(pow(2, depth + 1)));

    //리프노드에 데이터 초기화
    for (int i = 0; i < N; i++) {
        segTree_min[(int)(pow(2, depth)) + i].first = i;
        segTree_min[(int)(pow(2, depth)) + i].second = numArr[i];
    }
    for (int i = N; i < lastN; i++) {
        segTree_min[(int)(pow(2, depth)) + i].first = i;
        segTree_min[(int)(pow(2, depth)) + i].second = MAX;
    }

    //중간노드들 데이터 초기화
    for (int i = depth - 1; i >= 0; i--) {
        int curLevelStInd = (int)(pow(2, i));
        for (int j = 0; j < curLevelStInd; j++)
            segTree_min[curLevelStInd + j] = segTree_min[(curLevelStInd + j) * 2].second < segTree_min[(curLevelStInd + j) * 2 + 1].second ? segTree_min[(curLevelStInd + j) * 2] : segTree_min[(curLevelStInd + j) * 2 + 1];
    }
}

pair<int, long long> getMinNumFromRange(pair<int, int> targetRange, pair<int, int> curRange, int curTreeInd) {

    //범위 일치
    if (targetRange == curRange)
        return segTree_min[curTreeInd];

    //왼쪽만
    if (targetRange.second <= (curRange.first + curRange.second) / 2)
        return getMinNumFromRange(targetRange, { curRange.first, (curRange.first + curRange.second) / 2 }, curTreeInd * 2);

    //오른쪽만
    if (targetRange.first >= (curRange.first + curRange.second) / 2 + 1)
        return getMinNumFromRange(targetRange, { (curRange.first + curRange.second) / 2 + 1, curRange.second }, curTreeInd * 2 + 1);

    //둘다
    pair<int, int> left = getMinNumFromRange({ targetRange.first, (curRange.first + curRange.second) / 2 }, { curRange.first, (curRange.first + curRange.second) / 2 }, curTreeInd * 2);
    pair<int, int> right = getMinNumFromRange({ (curRange.first + curRange.second) / 2 + 1, targetRange.second }, { (curRange.first + curRange.second) / 2 + 1, curRange.second }, curTreeInd * 2 + 1);

    return left.second < right.second ? left : right;
}

void initSumSegTree() {
    int depth = (int)(ceil(log2(N)));
    segTree_sum = vector<long long>((int)(pow(2, depth + 1)));

    //리프노드에 데이터 초기화
    for (int i = 0; i < N; i++)
        segTree_sum[(int)(pow(2, depth)) + i] = numArr[i];

    //중간노드들 데이터 초기화
    for (int i = depth - 1; i >= 0; i--) {
        int curLevelStInd = (int)(pow(2, i));
        for (int j = 0; j < curLevelStInd; j++)
            segTree_sum[curLevelStInd + j] = segTree_sum[(curLevelStInd + j) * 2] + segTree_sum[(curLevelStInd + j) * 2 + 1];
    }
}

long long getSumFromRange(pair<int, int> targetRange, pair<int, int> curRange, int curTreeInd) {

    //범위 일치
    if (targetRange == curRange)
        return segTree_sum[curTreeInd];

    //왼쪽만
    if (targetRange.second <= (curRange.first + curRange.second) / 2)
        return getSumFromRange(targetRange, { curRange.first, (curRange.first + curRange.second) / 2 }, curTreeInd * 2);

    //오른쪽만
    if (targetRange.first >= (curRange.first + curRange.second) / 2 + 1)
        return getSumFromRange(targetRange, { (curRange.first + curRange.second) / 2 + 1, curRange.second }, curTreeInd * 2 + 1);

    //둘다
    return getSumFromRange({ targetRange.first, (curRange.first + curRange.second) / 2 }, { curRange.first, (curRange.first + curRange.second) / 2 }, curTreeInd * 2)
    + getSumFromRange({ (curRange.first + curRange.second) / 2 + 1, targetRange.second }, { (curRange.first + curRange.second) / 2 + 1, curRange.second }, curTreeInd * 2 + 1);
}

long long getMaxScoreFromRange(pair<int, int> targetRange) {
    if (targetRange.first > targetRange.second)
        return 0;

    pair<int, int> minVal = getMinNumFromRange(targetRange, { 0, lastN - 1 }, 1);

    //최솟값 기준 좌측
    long long leftScore = getMaxScoreFromRange({ targetRange.first, minVal.first - 1 });

    //최솟값 기준 우측
    long long rightScore = getMaxScoreFromRange({ minVal.first + 1, targetRange.second });

    //전체 범위
    long long whole = getSumFromRange(targetRange, { 0, lastN - 1 }, 1) * minVal.second;

    if (leftScore < rightScore) {
        if (rightScore < whole)
            return whole;
        else
            return rightScore;
    }
    else {
        if (leftScore < whole)
            return whole;
        else
            return leftScore;
    }
}