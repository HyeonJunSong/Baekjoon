////22.08.13
//이해 및 설계 : 17m 02s
//입력 : 1m 54s
//구현 : 47m 40s

//tot : 1h 6m 36s

#include <iostream>
#include <vector>
#include <string>
#include <deque>

using namespace std;

int N, M;

int main() {
    cin >> N >> M;
    vector<string> adjMatrix(N);
    for (int i = 0; i < N; i++)
        cin >> adjMatrix[i];

    //도시들 간 연결 먼저 추가
    vector<bool> cityCheck(N, false);
    vector<vector<bool>> roadCheck(N, vector<bool>(N, false));
    vector<int> ans(N, 0);

    cityCheck[0] = true;

    while (true) {
        bool ifDone = false;
        for (int i = 0; i < N; i++) {
            if (ifDone) break;
            for (int j = 0; j < N; j++) {
                if (adjMatrix[i][j] == 'Y') {
                    if (cityCheck[i] ^ cityCheck[j]) {
                        if(cityCheck[i] == true)
                            cityCheck[j] = true;
                        else
                            cityCheck[i] = true;

                        roadCheck[i][j] = true;
                        roadCheck[j][i] = true;
                        ans[i]++;
                        ans[j]++;
                        ifDone = true;
                        break;
                    }
                }
            }
        }
        if (!ifDone) break;
    }

    //다 연결됐는지 확인
    bool ifConnected = true;
    for (int i = 0; i < N; i++) {
        if (!cityCheck[i]) {
            ifConnected = false;
            break;
        }
    }

    if (!ifConnected) {
        cout << -1;
        return 0;
    }

    //남은 M으로 우선순위 가장 높은 도로들 추가
    M -= N - 1;
    bool ifDone = false;
    for (int i = 1; i < N; i++) {
        if (ifDone) break;
        for (int j = i + 1; j < N; j++) {
            if (M == 0) {
                ifDone = true;
                break;
            }
            if (adjMatrix[i][j] == 'Y' && (!roadCheck[i][j])) {
                M--;
                roadCheck[i][j] = true;
                roadCheck[j][i] = true;
                ans[i]++;
                ans[j]++;
            }
        }
    }

    if (M != 0)
        cout << -1;
    else {
        for (int i = 0; i < N; i++)
            cout << ans[i] << ' ';
    }
    return 0;
}