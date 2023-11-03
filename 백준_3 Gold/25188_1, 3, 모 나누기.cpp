////231103
//1h 6m 5s

#include <iostream>
#include <vector>

using namespace std;

#define LL long long
#define NINF -2000000000001
#define NAN -2000000000002

int N;
vector<LL> arr;

vector<vector<vector<LL>>> memo;

long long getMaxSum(int ind, int groupCnt, int ifSeq) {

    if (groupCnt == 0 || ind == N)
        return 0;

    if (ifSeq) {
        //넘기기
        if (memo[ind][groupCnt - 1][0] == NAN)
            memo[ind][groupCnt - 1][0] = getMaxSum(ind, groupCnt - 1, 0);

        //이어가기
        if (memo[ind + 1][groupCnt][1] == NAN)
            memo[ind + 1][groupCnt][1] = getMaxSum(ind + 1, groupCnt, 1);

        return max(memo[ind][groupCnt - 1][0], memo[ind + 1][groupCnt][1] + arr[ind]);
    }
    else {
        long long max = NINF;
        for (int i = ind; i <= N; i++) {
            if (memo[i][groupCnt][1] == NAN)
                memo[i][groupCnt][1] = getMaxSum(i, groupCnt, 1);
            if (max < memo[i][groupCnt][1])
                max = memo[i][groupCnt][1];
        }
        return max;
    }
}

int main() {
    cin >> N;
    arr = vector<LL>(N);
    for (int i = 0; i < N; i++)
        cin >> arr[i];

    memo = vector<vector<vector<LL>>>(N + 1, vector<vector<LL>>(4, vector<LL>(2, NAN)));

    cout << getMaxSum(0, 3, 1);

    return 0;
}