#include <iostream>
#include <vector>

using namespace std;

int main() {
    int N;
    cin >> N;
    vector<int> A(N);
    vector<int> B(N);
    for (int i = 0; i < N; i++)
        cin >> A[i];
    for (int i = 0; i < N; i++)
        cin >> B[i];


    ////숫자 개수로 정리 가능 여부 판단
    vector<int> cnt(N, 0);
    for (int i = 0; i < N; i++) {
        cnt[A[i] - 1]++;
        cnt[B[i] - 1]++;
    }
    for (int i = 0; i < N; i++) {
        if (cnt[i] != 2) {
            cout << -1;
            return 0;
        }
    }

    ////////////////////////////////////////
    vector<vector<int>> ATargets(N + 1);
    vector<vector<int>> BTargets(N + 1);

    for (int i = 0; i < N; i++) {
        ATargets[A[i]].push_back(B[i]);
        BTargets[B[i]].push_back(A[i]);
    }

    vector<bool> Avisited(N + 1, false);
    vector<bool> Bvisited(N + 1, false);

    int swapCnt = 0;

    for (int i = 1; i <= N; i++) {
        if (Avisited[i]) continue;

        int curNode;
        if (ATargets[i].size() > 0) {
            curNode = ATargets[i].back();
            Avisited[i] = true;
            Bvisited[curNode] = true;
            ATargets[i].pop_back();
            for (auto iter = BTargets[curNode].begin(); iter != BTargets[curNode].end(); iter++) {
                if (*iter == i) {
                    BTargets[curNode].erase(iter);
                    break;
                }
            }
        }
        else {
            swapCnt++;
            curNode = BTargets[i].back();
            Avisited[i] = true;
            Bvisited[curNode] = true;
            BTargets[i].pop_back();
            for (auto iter = ATargets[curNode].begin(); iter != ATargets[curNode].end(); iter++) {
                if (*iter == i) {
                    ATargets[curNode].erase(iter);
                    break;
                }
            }
        }

        while (true) {
            if (ATargets[curNode].size() == 1) {
                //A에 있는 경우
                if (Avisited[curNode]) break;
                int prevNode = curNode;
                curNode = ATargets[curNode].back();
                Avisited[prevNode] = true;
                Bvisited[curNode] = true;

                ATargets[prevNode].pop_back();
                for (auto iter = BTargets[curNode].begin(); iter != BTargets[curNode].end(); iter++) {
                    if (*iter == prevNode) {
                        BTargets[curNode].erase(iter);
                        break;
                    }
                }
            }
            else {
                //B에 있는 경우
                if (Avisited[curNode]) break;
                int prevNode = curNode;
                curNode = BTargets[curNode].back();
                Avisited[prevNode] = true;
                Bvisited[curNode] = true;
                swapCnt++;

                BTargets[prevNode].pop_back();
                for (auto iter = ATargets[curNode].begin(); iter != ATargets[curNode].end(); iter++) {
                    if (*iter == prevNode) {
                        ATargets[curNode].erase(iter);
                        break;
                    }
                }
            }
        }
    }
    
    if (swapCnt > N / 2) {
        cout << N / 2 - swapCnt;
    }
    else {
        cout << swapCnt;
    }

    return 0;
}