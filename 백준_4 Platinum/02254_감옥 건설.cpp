#include <iostream>
#include <vector>

using namespace std;

int N, Px, Py;

vector<pair<int, int>> pillars;
vector<bool> visited;

bool stripTheSkin();
void quantile(vector<int> indexes, int top, int right, int ifUpper);

int main() {

    cin >> N >> Px >> Py;

    pillars = vector<pair<int, int>>(N);
    for (int i = 0; i < N; i++)
        cin >> pillars[i].first >> pillars[i].second;
    pillars.push_back(pair<int, int>(Px, Py));

    visited = vector<bool>(N + 1, false);

    int ans = 0;
    while (!stripTheSkin())
        ans++;
    cout << ans;

    return 0;
}

bool stripTheSkin() {
    //topLeft, topRight, rightTop, rightBottom, bottomRight, bottomLeft, leftBottom, leftTop
    vector<int> endPoints;

    int i;
    for (i = 0; i < N + 1; i++) {
        if (visited[i])
            continue;
        endPoints = vector<int>(8, i);
        break;
    }

    for (; i < N + 1; i++) {
        if (visited[i])
            continue;

        if (pillars[endPoints[0]].second < pillars[i].second) {
            endPoints[0] = i;
            endPoints[1] = i;
        }
        else if (pillars[endPoints[0]].second == pillars[i].second) {
            if (pillars[endPoints[0]].first > pillars[i].first)
                endPoints[0] = i;
            else if (pillars[endPoints[1]].first < pillars[i].first)
                endPoints[1] = i;
        }
        else if (pillars[endPoints[4]].second > pillars[i].second) {
            endPoints[4] = i;
            endPoints[5] = i;
        }
        else if (pillars[endPoints[4]].second == pillars[i].second) {
            if (pillars[endPoints[5]].first > pillars[i].first)
                endPoints[5] = i;
            else if (pillars[endPoints[4]].first < pillars[i].first)
                endPoints[4] = i;
        }

        if (pillars[endPoints[2]].first < pillars[i].first) {
            endPoints[2] = i;
            endPoints[3] = i;
        }
        else if (pillars[endPoints[2]].first == pillars[i].first) {
            if (pillars[endPoints[3]].second > pillars[i].second)
                endPoints[3] = i;
            else if (pillars[endPoints[2]].second < pillars[i].second)
                endPoints[2] = i;
        }
        else if (pillars[endPoints[6]].first > pillars[i].first) {
            endPoints[6] = i;
            endPoints[7] = i;
        }
        else if (pillars[endPoints[6]].first == pillars[i].first) {
            if (pillars[endPoints[6]].second > pillars[i].second)
                endPoints[6] = i;
            else if (pillars[endPoints[7]].second < pillars[i].second)
                endPoints[7] = i;
        }
    }

    vector<vector<int>> quantiles(4);
    for (i = 0; i < N + 1; i++) {
        if (visited[i])
            continue;

        if (pillars[endPoints[1]].first < pillars[i].first && pillars[i].first < pillars[endPoints[2]].first
            && pillars[endPoints[2]].second < pillars[i].second && pillars[i].second < pillars[endPoints[1]].second)
            quantiles[0].push_back(i);
        else if (pillars[endPoints[7]].first < pillars[i].first && pillars[i].first < pillars[endPoints[0]].first
            && pillars[endPoints[7]].second < pillars[i].second && pillars[i].second < pillars[endPoints[0]].second)
            quantiles[1].push_back(i);
        else if (pillars[endPoints[6]].first < pillars[i].first && pillars[i].first < pillars[endPoints[5]].first
            && pillars[endPoints[5]].second < pillars[i].second && pillars[i].second < pillars[endPoints[6]].second)
            quantiles[2].push_back(i);
        else if (pillars[endPoints[4]].first < pillars[i].first && pillars[i].first < pillars[endPoints[3]].first
            && pillars[endPoints[4]].second < pillars[i].second && pillars[i].second < pillars[endPoints[3]].second)
            quantiles[3].push_back(i);
    }

    if (!quantiles[0].empty())
        quantile(quantiles[0], endPoints[1], endPoints[2], 1);
    if (!quantiles[1].empty())
        quantile(quantiles[1], endPoints[7], endPoints[0], 1);
    if (!quantiles[2].empty())
        quantile(quantiles[2], endPoints[6], endPoints[5], -1);
    if (!quantiles[3].empty())
        quantile(quantiles[3], endPoints[4], endPoints[3], -1);

    for (int i = 0; i < 8; i++)
        visited[endPoints[i]] = true;

    if (visited[N])
        return true;
    else
        return false;
}

void quantile(vector<int> indexes, int left, int right, int ifUpper) {

    double slope = (double)(pillars[right].second - pillars[left].second) / (pillars[right].first - pillars[left].first);

    double largestK = pillars[right].second - slope * pillars[right].first;
    int largestKInd = -1;

    for (auto iter = indexes.begin(); iter != indexes.end(); iter++) {
        double curK = pillars[*iter].second - slope * pillars[*iter].first;
        if (curK * ifUpper > largestK * ifUpper) {
            largestK = curK;
            largestKInd = *iter;
        }
    }

    if (largestKInd == -1)
        return;
    visited[largestKInd] = true;

    vector<int> leftIndexes;
    vector<int> rightIndexes;

    double leftSlope = (double)(pillars[largestKInd].second - pillars[left].second) / (pillars[largestKInd].first - pillars[left].first);
    double rightSlope = (double)(pillars[right].second - pillars[largestKInd].second) / (pillars[right].first - pillars[largestKInd].first);
    double leftK = pillars[largestKInd].second - leftSlope * pillars[largestKInd].first;
    double rightK = pillars[largestKInd].second - rightSlope * pillars[largestKInd].first;

    for (auto iter = indexes.begin(); iter != indexes.end(); iter++) {

        if (pillars[left].first < pillars[*iter].first && pillars[*iter].first < pillars[largestKInd].first
            && (pillars[*iter].second - leftSlope * pillars[*iter].first) * ifUpper > leftK * ifUpper)
            leftIndexes.push_back(*iter);
        else if (pillars[largestKInd].first < pillars[*iter].first && pillars[*iter].first < pillars[right].first
            && (pillars[*iter].second - rightSlope * pillars[*iter].first) * ifUpper > rightK * ifUpper)
            rightIndexes.push_back(*iter);
    }

    if (!leftIndexes.empty())
        quantile(leftIndexes, left, largestKInd, ifUpper);
    if (!rightIndexes.empty())
        quantile(rightIndexes, largestKInd, right, ifUpper);

}