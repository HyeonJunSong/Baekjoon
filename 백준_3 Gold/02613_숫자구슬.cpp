#include <iostream>
#include <vector>

using namespace std;

#define MAX 987654321

int N, M;
vector<int> marbles;

vector<vector<pair<int, vector<int>>>> cache;

vector<int> reversedAccumSum;

pair<int, vector<int>> retMinSet(int curI, int curM);

int main() {
    cin >> N >> M;
    marbles = vector<int>(N);

    for (int i = 0; i < N; i++)
        cin >> marbles[i];


    cache = vector<vector<pair<int, vector<int>>>>(N, vector<pair<int, vector<int>>>(M + 1, pair<int, vector<int>>(-1, vector<int>())));

    reversedAccumSum = marbles;
    for (int i = N - 2; i >= 0; i--)
        reversedAccumSum[i] += reversedAccumSum[i + 1];

    pair<int, vector<int>> ans = retMinSet(0, M);

    cout << ans.first << '\n';
    for (auto iter = ans.second.rbegin(); iter != ans.second.rend(); iter++)
        cout << *iter << ' ';

    return 0;
}

pair<int, vector<int>> retMinSet(int curI, int curM) {

    if (curM == 1) {
        return pair<int, vector<int>>(reversedAccumSum[curI], vector<int>(1, N - curI));
    }

    int curSum = 0;
    int minSum = MAX;
    vector<int> tempV;

    for (int i = curI; i <= N - curM; i++) {
        curSum += marbles[i];

        if (cache[i + 1][curM - 1].first == -1)
            cache[i + 1][curM - 1] = retMinSet(i + 1, curM - 1);

        if (curSum > cache[i + 1][curM - 1].first) {
            if (curSum < minSum) {
                minSum = curSum;
                tempV = cache[i + 1][curM - 1].second;
                tempV.push_back(i - curI + 1);
            }
        }
        else {
            if (cache[i + 1][curM - 1].first < minSum) {
                minSum = cache[i + 1][curM - 1].first;
                tempV = cache[i + 1][curM - 1].second;
                tempV.push_back(i - curI + 1);
            }
        }

    }

    return pair<int, vector<int>>(minSum, tempV);
}