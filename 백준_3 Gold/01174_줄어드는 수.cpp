////230514
//이해 및 설계 : 10m 35s
//입력 : 1m 4s
//구현 : 46m 9s

//tot : 57m 48s

#include <iostream>
#include <vector>
#include <string>

using namespace std;

vector<vector<int>> cache_combination;

pair<int, int> getDigits(int N);
string getNum(int ed, int n, int N);
int combination(int n, int r);

int main() {
    int N;
    cin >> N;

    cache_combination = vector<vector<int>>(11, vector<int>(11, -1));

    pair<int, int> digit = getDigits(N - 1);
    if (digit.first == -1) {
        cout << -1;
        return 0;
    }

    cout << getNum(9, digit.first, digit.second);

    return 0;
}

//자릿수와 남은 카운트 알아내기
pair<int, int> getDigits(int N) {
    for (int i = 1; i <= 10; i++) {
        if (cache_combination[10][i] == -1)
            cache_combination[10][i] = combination(10, i);

        if (N - cache_combination[10][i] < 0)
            return pair<int, int>(i, N);
        N -= cache_combination[10][i];
    }

    return pair<int, int>(-1, -1);
}

//답 구하기
//파라미터 : 가능한 마지막 숫자, 현재 자리수, 남은 카운트 수
// -> 현재 자리숫에 for문돌며 현재 자릿수 알아내고, 그 뒤는 재귀

string getNum(int ed, int n, int N) {
    if (n == 1) {
        return to_string(N);
    }

    for (int i = n - 1; i <= ed; i++) {
        if (cache_combination[i][n - 1] == -1)
            cache_combination[i][n - 1] = combination(i, n - 1);

        if (N - cache_combination[i][n - 1] < 0)
            return to_string(i) + getNum(i - 1, n - 1, N);

        N -= cache_combination[i][n - 1];
    }

    return "-1";
}

int combination(int n, int r) {
    if (r == 0 || n == r)
        return 1;

    if (cache_combination[n - 1][r - 1] == -1)
        cache_combination[n - 1][r - 1] = combination(n - 1, r - 1);

    if (cache_combination[n - 1][r] == -1)
        cache_combination[n - 1][r] = combination(n - 1, r);

    return cache_combination[n - 1][r - 1] + cache_combination[n - 1][r];
}