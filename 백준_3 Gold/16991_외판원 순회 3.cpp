//230629
//50m 54s

#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>

using namespace std;

vector<vector<double>> graph;

int N;
vector<int> binaries;
vector<vector<double>> cache;

void initBinaries();
int remainsToInt(vector<bool>& remains);
double getSmallestRoute(vector<bool>& remains, int remainCnt, int lastNode);

int main() {

    cin >> N;

    vector<pair<int, int>> city(N);
    for (int i = 0; i < N; i++)
        cin >> city[i].first >> city[i].second;

    graph = vector<vector<double>>(N, vector<double>(N));
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            graph[i][j] = sqrt(pow(city[j].first - city[i].first, 2) + pow(city[j].second - city[i].second, 2));

    initBinaries();
    cache = vector<vector<double>>((int)(pow(2, N)), vector<double>(N, -1));

    vector<bool> remain(N, true);
    remain[0] = false;

    cout << setprecision(16);
    cout << getSmallestRoute(remain, N - 1, 0);

    return 0;
}

double getSmallestRoute(vector<bool>& remains, int remainCnt, int lastNode) {

    if (remainCnt == 1) {
        for (int i = 1; i < N; i++)
            if (remains[i])
                return graph[lastNode][i] + graph[i][0];
    }

    double smallestRoute = 987654321;
    for (int i = 1; i < N; i++) {
        if (!remains[i]) continue;

        remains[i] = false;
        int curRemain = remainsToInt(remains);
        if (cache[curRemain][i] == -1)
            cache[curRemain][i] = getSmallestRoute(remains, remainCnt - 1, i);

        if (smallestRoute > cache[curRemain][i] + graph[lastNode][i])
            smallestRoute = cache[curRemain][i] + graph[lastNode][i];

        remains[i] = true;
    }

    return smallestRoute;
}

void initBinaries() {
    binaries = vector<int>(N);
    binaries[0] = 1;
    for (int i = 1; i < N; i++)
        binaries[i] = binaries[i - 1] * 2;
}

int remainsToInt(vector<bool>& remains) {
    int tot = 0;
    for (int i = 0; i < N; i++)
        if (remains[i])
            tot += binaries[i];
    return tot;
}