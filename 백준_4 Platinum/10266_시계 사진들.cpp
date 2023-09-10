#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {

    int n;
    cin >> n;
    vector<int> firstClock(n);
    vector<int> secondClock(n);
    for (int i = 0; i < n; i++)
        cin >> firstClock[i];
    for (int i = 0; i < n; i++)
        cin >> secondClock[i];

    //시계 정렬 및 첫 초침 초기화 
    sort(firstClock.begin(), firstClock.end());
    sort(secondClock.begin(), secondClock.end());
    int lastElement_first = firstClock[n - 1];
    int lastElement_second = secondClock[n - 1];
    for (int i = n - 1; i > 0; i--) {
        firstClock[i] -= firstClock[i - 1];
        secondClock[i] -= secondClock[i - 1];
    }
    firstClock[0] += 360000 - lastElement_first;
    secondClock[0] += 360000 - lastElement_second;

    //탐색배열 초기화
    vector<int> searchArr(n);
    searchArr[0] = -1;
    int curCompareInd = 0;
    for (int i = 1; i < n; i++) {
        if (secondClock[i] == secondClock[curCompareInd]) {
            searchArr[i] = curCompareInd++;
        }
        else {
            if (curCompareInd == 0) {
                searchArr[i] = -1;
            }
            else {
                i--;
                curCompareInd = 0;
            }
        }
    }

    //탐색
    int curSearchInd = 0;
    bool ifPossible = false;
    for (int i = 0; i < 2 * n; i++) {
        if (curSearchInd == n) {
            ifPossible = true;
            break;
        }

        if (firstClock[i % n] == secondClock[curSearchInd]) {
            curSearchInd++;
        }
        else {
            if (searchArr[curSearchInd] == -1) {
                curSearchInd = 0;
            }
            else {
                curSearchInd = searchArr[curSearchInd];
                i--;
            }
        }
    }

    if (curSearchInd == n) {
        ifPossible = true;
    }

    if (ifPossible)
        cout << "possible";
    else
        cout << "impossible";


    return 0;
}