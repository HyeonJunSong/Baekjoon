#include <iostream>
#include <vector>

using namespace std;

vector<int> R;
vector<int> G;
vector<int> B;

int** memo;
int N;

int minCost(int curind, int banColor);


int main() {
    cin >> N;

    for (int i = 0; i < N; i++) {
        int r, g, b;
        cin >> r >> g >> b;
        R.push_back(r);
        G.push_back(g);
        B.push_back(b);
    }

    memo = new int* [3];
    for (int i = 0; i < 3; i++) {
        memo[i] = new int[N];
        for (int j = 0; j < N; j++)
            memo[i][j] = 0;
    }

    int minR = minCost(0, 0);
    int minG = minCost(0, 1);
    int minB = minCost(0, 2);

    int min = minR;
    if (min > minG)
        min = minG;
    if (min > minB)
        min = minB;

    cout << min;

    return 0;
}

int minCost(int curind, int banColor) {
    if (memo[banColor][curind])
        return memo[banColor][curind];

    int min = 0;

    if (curind == N - 1) {
        switch (banColor) {
        case 0:
            G[N - 1] < B[N - 1] ? min = G[N - 1] : min = B[N - 1];
            break;

        case 1:
            R[N - 1] < B[N - 1] ? min = R[N - 1] : min = B[N - 1];
            break;

        case 2:
            R[N - 1] < G[N - 1] ? min = R[N - 1] : min = G[N - 1];
            break;
        }
    }
    else {
        switch (banColor) {
        case 0:
            if (G[curind] < B[curind])
                min = G[curind] + minCost(curind + 1, 1);
            else
                min = B[curind] + minCost(curind + 1, 2);

            break;

        case 1:
            if (R[curind] < B[curind])
                min = R[curind] + minCost(curind + 1, 0);
            else
                min = B[curind] + minCost(curind + 1, 2);
            break;

        case 2:
            if (R[curind] < G[curind])
                min = R[curind] + minCost(curind + 1, 0);
            else
                min = G[curind] + minCost(curind + 1, 1);
            break;
        }
    }

    memo[banColor][curind] = min;
    return min;
}