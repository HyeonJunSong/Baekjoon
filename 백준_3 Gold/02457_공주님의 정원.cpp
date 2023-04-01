#include <iostream>
#include <queue>
#include <algorithm>

using namespace std;

int days[13] = {
    0,
    0,
    31,
    59,
    90,
    120,
    151,
    181,
    212,
    243,
    273,
    304,
    334
};

bool comp(pair<int, int> a, pair<int, int> b) {
    if (a.first == b.first)
        return a.second < b.second;
    return a.first < b.first;
}

int main() {
    int N;
    cin >> N;

    int stM, stD, edM, edD;
    vector<pair<int, int>> flowers;
    for (int i = 0; i < N; i++) {
        cin >> stM >> stD >> edM >> edD;
        flowers.push_back(pair<int, int>(days[stM] + stD, days[edM] + edD));
    }

    sort(flowers.begin(), flowers.end(), comp);

    priority_queue<int> PQ;
    int curNeccessary = days[3] + 1;
    int i = 0;
    int cnt = 0;
    while (curNeccessary <= days[12]) {
        for (; i < N && flowers[i].first <= curNeccessary; i++)
            PQ.push(flowers[i].second);

        if(PQ.empty()) break;
        cnt++;
        int topNode = PQ.top();
        PQ.pop();
        curNeccessary = topNode;
    }

    if (curNeccessary <= days[12])
        cout << 0;
    else
        cout << cnt;

}