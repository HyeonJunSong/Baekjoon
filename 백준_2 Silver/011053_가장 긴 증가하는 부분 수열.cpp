////2022.09.04
//39m 44s

#include <iostream>
#include <vector>

using namespace std;

vector<int> memo;
vector<int> arr;

int retMaxSubArr(int st);

int main() {
    int N;
    cin >> N;
    arr = vector<int>(N, 0);
    for (int i = 0; i < N; i++)
        cin >> arr[i];

    memo = vector<int>(N, -1);

    int ans = 0;
    for (int i = 0; i < N; i++) {
        if (memo[i] == -1) memo[i] = retMaxSubArr(i);
        if (ans < memo[i]) ans = memo[i];
    }
    cout << ans;
    return 0;
}

int retMaxSubArr(int st) {
    if (st == arr.size() - 1) return 1;

    int maxArrLen = 1;
    for (int i = st + 1; i < arr.size(); i++) {
        if (arr[st] < arr[i]) {
            if (memo[i] == -1) memo[i] = retMaxSubArr(i);
            if (maxArrLen < memo[i] + 1) maxArrLen = memo[i] + 1;
        }
    }

    return maxArrLen;
}