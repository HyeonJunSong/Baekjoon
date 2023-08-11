#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int N;
vector<pair<int, int>> animals;
vector<int> endIndOfSubArrayOfLength;

bool comp(pair<int, int> a, pair<int, int> b) {
    if (a.first == b.first)
        return a.second > b.second;
    return a.first < b.first;
}


bool ifLower(int targetInd, int comparedInd) {
    if (animals[comparedInd].first <= animals[targetInd].first && animals[targetInd].second <= animals[comparedInd].second) {
        if (animals[comparedInd].first == animals[targetInd].first && animals[targetInd].second == animals[comparedInd].second)
            return false;
        return true;
    }
    return false;
}

int findPlace(int ind) {
    int st = 0;
    int ed = N - 1;

    while (st <= ed) {
        int mid = (st + ed) / 2;

        if (endIndOfSubArrayOfLength[mid] == -1 || !ifLower(ind, endIndOfSubArrayOfLength[mid]))
            ed = mid - 1;
        else
            st = mid + 1;
    }

    if (st == N)
        return N - 1;
    if (endIndOfSubArrayOfLength[st] != -1 && ifLower(ind, endIndOfSubArrayOfLength[st]))
        return st;
    if (st == 0)
        return -1;
    if (endIndOfSubArrayOfLength[ed] != -1 && ifLower(ind, endIndOfSubArrayOfLength[ed]))
        return ed;
    if (endIndOfSubArrayOfLength[ed] != -1 && ifLower(ind, endIndOfSubArrayOfLength[ed - 1]))
        return ed - 1;
}


int main() {

    ////입력
    cin >> N;
    animals = vector<pair<int, int>>(N);
    int temp;
    for (int i = 0; i < N; i++)
        cin >> temp >> animals[i].first >> animals[i].second;

    ////정렬
    sort(animals.begin(), animals.end(), comp);

    ////가장 긴 부분수열 찾기
    endIndOfSubArrayOfLength = vector<int>(N, -1);

    for (int i = 0; i < N; i++) {
        endIndOfSubArrayOfLength[findPlace(i) + 1] = i;
    }

    for (int i = N - 1; i >= 0; i--) {
        if (endIndOfSubArrayOfLength[i] != -1) {
            cout << i + 1;
            break;
        }
    }

    return 0;
}