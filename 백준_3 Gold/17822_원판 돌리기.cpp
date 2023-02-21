#include <iostream>
#include <vector>

using namespace std;

vector<vector<int>> disk;
vector<int> stInd;
int N, M, T;

void afterRotation();

int main() {
    cin >> N >> M >> T;

    disk = vector<vector<int>>(N, vector<int>(M, 0));
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            cin >> disk[i][j];

    vector<vector<int>> rotate = vector<vector<int>>(T, vector<int>(3, 0));
    for (int i = 0; i < T; i++)
        cin >> rotate[i][0] >> rotate[i][1] >> rotate[i][2];

    stInd = vector<int>(N, 0);

    for (int i = 0; i < T; i++) {
        if (rotate[i][0] != 1) {
            for (int j = rotate[i][0] - 1; j < N; j += rotate[i][0]) {
                if (rotate[i][1] == 1)
                    stInd[j] = (stInd[j] + rotate[i][2]) % M;
                else
                    stInd[j] = (M + stInd[j] - rotate[i][2]) % M;
            }
            afterRotation();
        }
    }

    int tot = 0;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            tot += disk[i][j];
    cout << tot;
    return 0;
}

void afterRotation() {

    ////지울 목록 찾기
    vector<vector<bool>> toErase(N, vector<bool>(M, false));

    //첫줄 마지막-1 줄
    for (int i = 0; i < N - 1; i++) {
        for (int j = 0; j < M; j++) {
            if (disk[i][(stInd[i] + j) % M] == 0) continue;

            if (disk[i][(stInd[i] + j) % M] == disk[i][(stInd[i] + j + 1) % M]) {
                toErase[i][(stInd[i] + j) % M] = true;
                toErase[i][(stInd[i] + j + 1) % M] = true;
            }

            if (disk[i][(stInd[i] + j) % M] == disk[i + 1][(stInd[i + 1] + j) % M]) {
                toErase[i][(stInd[i] + j) % M] = true;
                toErase[i + 1][(stInd[i + 1] + j) % M] = true;
            }
        }
    }

    //마지막줄
    for (int j = 0; j < M; j++) {
        if (disk[N - 1][(stInd[N - 1] + j) % M] == 0) continue;

        if (disk[N - 1][(stInd[N - 1] + j) % M] == disk[N - 1][(stInd[N - 1] + j + 1) % M]) {
            toErase[N - 1][(stInd[N - 1] + j) % M] = true;
            toErase[N - 1][(stInd[N - 1] + j + 1) % M] = true;
        }
    }

    ////지울목록 지우기
    bool ifErased = false;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (toErase[i][j]) {
                disk[i][j] = 0;
                ifErased = true;
            }
        }
    }

    ////지운게 없으면 총합에셔 평균구하고 1빼고 1더하기 작업

    if (!ifErased) {
        double tot = 0;
        int totNum = 0;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                if (disk[i][j] != 0) {
                    tot += disk[i][j];
                    totNum++;
                }
            }
        }

        tot = tot / totNum;

        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                if (disk[i][j] == 0) continue;
                if (tot > (double)(disk[i][j]))
                    disk[i][j]++;
                else if (tot < (double)(disk[i][j]))
                    disk[i][j]--;
            }
        }
    }
}