#include <iostream>
#include <vector>

using namespace std;

int main() {

    int N, M;
    cin >> N >> M;
    vector<vector<int>> map(N, vector<int>(M));
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            cin >> map[i][j];

    vector<vector<vector<int>>>dp(N, vector<vector<int>>(M, vector<int>(3, 987654321)));

    for (int j = 0; j < M; j++)
        for (int d = 0; d < 3; d++)
            dp[0][j][d] = map[0][j];

    for (int i = 1; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (j == 0) {
                dp[i][j][1] = dp[i - 1][j][0] + map[i][j];
                dp[i][j][0] = min(dp[i - 1][j + 1][1], dp[i - 1][j + 1][2]) + map[i][j];
            }
            else if (j == M - 1) {
                dp[i][j][1] = dp[i - 1][j][2] + map[i][j];
                dp[i][j][2] = min(dp[i - 1][j - 1][0], dp[i - 1][j - 1][1]) + map[i][j];
            }
            else {
                dp[i][j][0] = min(dp[i - 1][j + 1][1], dp[i - 1][j + 1][2]) + map[i][j];
                dp[i][j][1] = min(dp[i - 1][j][0], dp[i - 1][j][2]) + map[i][j];
                dp[i][j][2] = min(dp[i - 1][j - 1][0], dp[i - 1][j - 1][1]) + map[i][j];
            }
        }
    }

    int ans = 987654321;
    for (int j = 0; j < M; j++)
        for (int d = 0; d < 3; d++)
            ans = min(ans, dp[N - 1][j][d]);
    cout << ans;

    return 0;
}