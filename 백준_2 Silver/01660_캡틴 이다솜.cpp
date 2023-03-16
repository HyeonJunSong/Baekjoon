#include <iostream>
#include <vector>
#include <map>

using namespace std;

vector<int> neededNum(121, 0);
vector<int> cache;

int minCannonNum(int N);

int main() {
    int N;
    cin >> N;

    for (int i = 1; i < 121; i++) {
        neededNum[i] = (int)(i * (i + 1) * (i + 2) / 6);
    }

    cache = vector<int>(N, -1);

    cout << minCannonNum(N);
    return 0;
}

int minCannonNum(int N) {
    if (N < 4) return N;

    int res = 987654321;
    for (int i = 120; i > 1; i--) {
        if (N >= neededNum[i]) {
            if (cache[N - neededNum[i]] == -1)
                cache[N - neededNum[i]] = minCannonNum(N - neededNum[i]);
            if (cache[N - neededNum[i]] < res)
                res = cache[N - neededNum[i]];
        }
    }

    return res + 1;
}