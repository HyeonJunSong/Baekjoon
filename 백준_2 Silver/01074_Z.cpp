////22.07.24
//이해 및 설계 : 2m 37s
//입력 : 47s
//구현 : 12m 10s

//tot : 15m 34s

#include <iostream>
#include <cmath>

using namespace std;

int retNum(int N, int r, int c);
int main() {

    int N, r, c;
    cin >> N >> r >> c;

    cout << retNum(N, r, c);
}

int retNum(int N, int r, int c) {

    if (N == 1) {
        if (r == 0) {
            if (c == 0) return 0;
            else return 1;
        }
        else {
            if (c == 0) return 2;
            else return 3;
        }
    }

    if (r < (int)(pow(2, N) / 2)) {
        if (c < (int)(pow(2, N) / 2))
            return retNum(N - 1, r, c);
        else
            return 1 * (int)(pow(2, N - 1) * pow(2, N - 1)) + retNum(N - 1, r, c - pow(2, N - 1));
    }
    else {
        if (c < (int)(pow(2, N) / 2))
            return 2 * (int)(pow(2, N - 1) * pow(2, N - 1)) + retNum(N - 1, r - pow(2, N - 1), c);
        else
            return 3 * (int)(pow(2, N - 1) * pow(2, N - 1)) + retNum(N - 1, r - pow(2, N - 1), c - pow(2, N - 1));
    }
}