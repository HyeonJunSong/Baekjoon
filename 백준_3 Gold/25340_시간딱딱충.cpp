#include <iostream>
#include <set>
#include <vector>

using namespace std;

int main() {

    int TC, N, T;
    vector<int> A, B, C, D, E;
    vector<int> accumSum;

    cin >> TC;
    for (int tc = 0; tc < TC; tc++) {

        cin >> N >> T;
        A = vector<int>(N);
        B = vector<int>(N);
        C = vector<int>(N);
        D = vector<int>(N);
        for (int i = 0; i < N; i++)
            cin >> A[i] >> B[i] >> C[i] >> D[i];


        E = vector<int>(N + 1);
        for (int i = 0; i < N + 1; i++)
            cin >> E[i];

        accumSum = vector<int>(N + 1);
        accumSum[0] = 0;
        for(int i = 0; i < N; i++){
            accumSum[i + 1] = accumSum[i] + D[i] + E[i];
        }

        set<int> arriveAvailableTime;
        arriveAvailableTime.insert(T - E[N]);

        int curInd = N - 1;

        while (!arriveAvailableTime.empty() && curInd >= 0) {
            set<int> newArriveAvailableTime;
            for (auto iter = arriveAvailableTime.begin(); iter != arriveAvailableTime.end(); iter++) {
                if ((*iter - D[curInd] - C[curInd]) % A[curInd] <= B[curInd] - D[curInd]) {
                    if (*iter - D[curInd] - C[curInd] >= 0 && (*iter - D[curInd] - C[curInd]) % A[curInd] == 0) {

                        for (int i = *iter - D[curInd]; i > *iter - D[curInd] - (A[curInd] - B[curInd] + D[curInd]); i--)
                            if (i - E[curInd] >= accumSum[curInd]) newArriveAvailableTime.insert(i - E[curInd]);
                        
                    }
                    else {
                        if (*iter - D[curInd] - E[curInd] >= accumSum[curInd]) newArriveAvailableTime.insert(*iter - D[curInd] - E[curInd]);
                    }
                }
            }
            arriveAvailableTime = newArriveAvailableTime;
            curInd--;
        }

        if (arriveAvailableTime.empty())
            cout << "NO" << "\n";
        else
            cout << "YES" << "\n";

    }

    return 0;
}