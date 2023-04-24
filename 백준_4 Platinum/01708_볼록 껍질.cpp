#include <iostream>
#include <vector>
#include <set>

using namespace std;

set<int> ansSet;

vector<pair<int, int>> coors;

void quarter(vector<int> curCoors, int leftCoor, int rightCoor, int ifUpper);

int main() {
    int N;
    cin >> N;

    coors = vector<pair<int, int>>(N);
    for (int i = 0; i < N; i++)
        cin >> coors[i].first >> coors[i].second;

    int topLeft = 0;
    int topRight = 0;
    int leftTop = 0;
    int leftBottom = 0;
    int bottomLeft = 0;
    int bottomRight = 0;
    int rightBottom = 0;
    int rightTop = 0;


    vector<int> Q1Box;
    vector<int> Q2Box;
    vector<int> Q3Box;
    vector<int> Q4Box;

    for (int i = 0; i < coors.size(); i++) {
        if (coors[i].second == coors[topLeft].second) {
            if (coors[i].first < coors[topLeft].first)
                topLeft = i;
            if (coors[i].first > coors[topRight].first)
                topRight = i;
        }
        else if (coors[i].second > coors[topLeft].second) {
            topLeft = i;
            topRight = i;
        }

        if (coors[i].first == coors[leftTop].first) {
            if (coors[i].second > coors[leftTop].second)
                leftTop = i;
            if (coors[i].second < coors[leftBottom].second)
                leftBottom = i;
        }
        else if (coors[i].first < coors[leftTop].first) {
            leftTop = i;
            leftBottom = i;
        }

        if (coors[i].second == coors[bottomLeft].second) {
            if (coors[i].first < coors[bottomLeft].first)
                bottomLeft = i;
            if (coors[i].first > coors[bottomRight].first)
                bottomRight = i;
        }
        else if (coors[i].second < coors[bottomLeft].second) {
            bottomLeft = i;
            bottomRight = i;
        }

        if (coors[i].first == coors[rightTop].first) {
            if (coors[i].second > coors[rightTop].second)
                rightTop = i;
            if (coors[i].second < coors[rightBottom].second)
                rightBottom = i;
        }
        else if (coors[i].first > coors[rightTop].first) {
            rightTop = i;
            rightBottom = i;
        }
    }

    for (int i = 0; i < coors.size(); i++) {
        if (coors[topRight].first < coors[i].first && coors[i].first < coors[rightTop].first
            && coors[rightTop].second < coors[i].second && coors[i].second < coors[topRight].second) {
            Q1Box.push_back(i);
        }
        if (coors[leftTop].first < coors[i].first && coors[i].first < coors[topLeft].first
            && coors[leftTop].second < coors[i].second && coors[i].second < coors[topLeft].second) {
            Q2Box.push_back(i);
        }
        if (coors[leftBottom].first < coors[i].first && coors[i].first < coors[bottomLeft].first
            && coors[bottomLeft].second < coors[i].second && coors[i].second < coors[leftBottom].second) {
            Q3Box.push_back(i);
        }
        if (coors[bottomRight].first < coors[i].first && coors[i].first < coors[rightBottom].first
            && coors[bottomRight].second < coors[i].second && coors[i].second < coors[rightBottom].second) {
            Q4Box.push_back(i);
        }
    }

    if (!Q1Box.empty())
        quarter(Q1Box, topRight, rightTop, 1);
    if (!Q2Box.empty())
        quarter(Q2Box, leftTop, topLeft, 1);
    if (!Q3Box.empty())
        quarter(Q3Box, leftBottom, bottomLeft, -1);
    if (!Q4Box.empty())
        quarter(Q4Box, bottomRight, rightBottom, -1);

    ansSet.insert(topLeft);
    ansSet.insert(topRight);
    ansSet.insert(leftTop);
    ansSet.insert(leftBottom);
    ansSet.insert(bottomLeft);
    ansSet.insert(bottomRight);
    ansSet.insert(rightBottom);
    ansSet.insert(rightTop);

    cout << ansSet.size();

    return 0;
}

void quarter(vector<int> curCoors, int leftCoor, int rightCoor, int ifUpper) {
    vector<int> outerCoors;
    double curSlope = (double)(coors[rightCoor].second - coors[leftCoor].second) / (coors[rightCoor].first - coors[leftCoor].first);
    double baseK = coors[leftCoor].second - curSlope * coors[leftCoor].first;
    double curK, largestK = baseK;
    int curLeftCoor = leftCoor;
    int curRightCoor = rightCoor;

    for (auto iter = curCoors.begin(); iter != curCoors.end(); iter++) {
        curK = coors[*iter].second - curSlope * coors[*iter].first;

        if (ifUpper * curK > ifUpper * baseK)
            outerCoors.push_back(*iter);

        if (ifUpper * curK > ifUpper * largestK) {
            largestK = curK;
            curLeftCoor = *iter;
            curRightCoor = *iter;
        }
        if (curK == largestK) {
            if (coors[*iter].first < coors[curLeftCoor].first)
                curLeftCoor = *iter;
            if (coors[*iter].first < coors[curRightCoor].first)
                curRightCoor = *iter;
        }
    }

    if (outerCoors.empty())
        return;

    ////분할정복
    vector<int> leftBox, rightBox;
    for (auto iter = outerCoors.begin(); iter != outerCoors.end(); iter++) {
        if (coors[*iter].first < coors[curLeftCoor].first)
            leftBox.push_back(*iter);
        if (coors[*iter].first > coors[curRightCoor].first)
            rightBox.push_back(*iter);
    }

    if (!leftBox.empty())
        quarter(leftBox, leftCoor, curLeftCoor, ifUpper);

    if (!rightBox.empty())
        quarter(rightBox, curRightCoor, rightCoor, ifUpper);

    ansSet.insert(curLeftCoor);
    ansSet.insert(curRightCoor);
}