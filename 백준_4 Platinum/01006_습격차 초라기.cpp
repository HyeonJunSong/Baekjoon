#include <iostream>
#include <vector>

using namespace std;

int main() {

    int T;
    cin >> T;
    for (int t = 0; t < T; t++) {
        int N, W;
        cin >> N >> W;
        vector<int> inner(N, 0);
        vector<int> outer(N, 0);

        for (int i = 0; i < N; i++) cin >> inner[i];
        for (int i = 0; i < N; i++) cin >> outer[i];

        vector<int> innerCnt(N, 0);
        vector<int> outerCnt(N, 0);

        if (N == 1) {
            if (inner[0] + outer[0] <= W) {
                innerCnt[0]++;
                outerCnt[0]++;
            }
        }
        else if (N == 2) {
            if (inner[0] + outer[0] <= W) {
                innerCnt[0]++;
                outerCnt[0]++;
            }
            if (inner[1] + outer[1] <= W) {
                innerCnt[1]++;
                outerCnt[1]++;
            }
            if (inner[0] + inner[1] <= W) {
                innerCnt[0]++;
                innerCnt[1]++;
            }
            if (outer[0] + outer[1] <= W) {
                outerCnt[0]++;
                outerCnt[1]++;
            }

        }
        else {
            for (int i = 0; i < N; i++) {
                if (inner[i] + inner[(i + 1) % N] <= W) {
                    innerCnt[i]++;
                    innerCnt[(i + 1) % N]++;
                }

                if (inner[i] + outer[i] <= W) {
                    innerCnt[i]++;
                    outerCnt[i]++;
                }
            }

            for (int i = 0; i < N; i++) {
                if (outer[i] + outer[(i + 1) % N] <= W) {
                    outerCnt[i]++;
                    outerCnt[(i + 1) % N]++;
                }
            }
        }

        bool ifChanged = true;
        while (ifChanged) {
            ifChanged = false;
            for (int i = 0; i < N; i++) {

                if (innerCnt[i] == 1) {
                    int target = W - inner[i];
                    innerCnt[i] = 4;
                    if (innerCnt[(i - 1 + N) % N] != 4 && target >= inner[(i - 1 + N) % N]) {
                        innerCnt[(i - 1 + N) % N] = 4;

                        int target2 = W - inner[(i - 1 + N) % N];
                        if (innerCnt[(i - 2 + N) % N] != 4 && target2 >= inner[(i - 2 + N) % N]) innerCnt[(i - 2 + N) % N]--;
                        if (outerCnt[(i - 1 + N) % N] != 4 && target2 >= outer[(i - 1 + N) % N]) outerCnt[(i - 1 + N) % N]--;
                    }
                    else if (innerCnt[(i + 1 + N) % N] != 4 && target >= inner[(i + 1 + N) % N]) {
                        innerCnt[(i + 1 + N) % N] = 4;

                        int target2 = W - inner[(i + 1 + N) % N];
                        if (innerCnt[(i + 2 + N) % N] != 4 && target2 >= inner[(i + 2 + N) % N]) innerCnt[(i + 2 + N) % N]--;
                        if (outerCnt[(i + 1 + N) % N] != 4 && target2 >= outer[(i + 1 + N) % N]) outerCnt[(i + 1 + N) % N]--;
                    }
                    else if (outerCnt[(i + 0 + N) % N] != 4 && target >= outer[(i + 0 + N) % N]) {
                        outerCnt[(i + 0 + N) % N] = 4;

                        int target2 = W - outer[(i + 0) % N];
                        if (outerCnt[(i - 1 + N) % N] != 4 && target2 >= outer[(i - 1 + N) % N]) outerCnt[(i - 1 + N) % N]--;
                        if (outerCnt[(i + 1 + N) % N] != 4 && target2 >= outer[(i + 1 + N) % N]) outerCnt[(i + 1 + N) % N]--;
                    }

                    ifChanged = true;
                }

                if (outerCnt[i] == 1) {
                    int target = W - outer[i];
                    outerCnt[i] = 4;
                    if (outerCnt[(i - 1 + N) % N] != 4 && target >= outer[(i - 1 + N) % N]) {
                        outerCnt[(i - 1 + N) % N] = 4;

                        int target2 = W - outer[(i - 1 + N) % N];
                        if (outerCnt[(i - 2 + N) % N] != 4 && target2 >= outer[(i - 2 + N) % N]) outerCnt[(i - 2 + N) % N]--;
                        if (innerCnt[(i - 1 + N) % N] != 4 && target2 >= inner[(i - 1 + N) % N]) innerCnt[(i - 1 + N) % N]--;
                    }
                    else if (outerCnt[(i + 1 + N) % N] != 4 && target >= outer[(i + 1 + N) % N]) {
                        outerCnt[(i + 1 + N) % N] = 4;

                        int target2 = W - outer[(i + 1) % N];
                        if (outerCnt[(i + 2 + N) % N] != 4 && target2 >= outer[(i + 2 + N) % N]) outerCnt[(i + 2 + N) % N]--;
                        if (innerCnt[(i + 1 + N) % N] != 4 && target2 >= inner[(i + 1 + N) % N]) innerCnt[(i + 1 + N) % N]--;
                    }
                    else if (innerCnt[(i + 0 + N) % N] != 4 && target >= inner[(i + 0 + N) % N]) {
                        innerCnt[(i + 0 + N) % N] = 4;

                        int target2 = W - inner[(i + 0) % N];
                        if (innerCnt[(i - 1 + N) % N] != 4 && target2 >= inner[(i - 1 + N) % N]) innerCnt[(i - 1 + N) % N]--;
                        if (innerCnt[(i + 1 + N) % N] != 4 && target2 >= inner[(i + 1 + N) % N]) innerCnt[(i + 1 + N) % N]--;
                    }

                    ifChanged = true;
                }



            }

        }



        vector<int> totCnt(5, 0);
        for (int i = 0; i < N; i++) {
            totCnt[innerCnt[i]]++;
            totCnt[outerCnt[i]]++;
        }

//        for (int i = 0; i < 5; i++) cout << totCnt[i] << ' ';
//        cout << endl;

        cout << totCnt[0] + totCnt[2] / 2 + totCnt[3] / 2 + totCnt[4] / 2 << endl;

    }

}