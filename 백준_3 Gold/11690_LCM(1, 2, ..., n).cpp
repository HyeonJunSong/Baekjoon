#include <iostream>
#include <vector>
#include <cmath>

using namespace std;


int main() {
    int N;
    cin >> N;

    vector<bool> ifPrime(N + 1, true);
    long long divisor = (long long) (pow(2, 32));

    long long ans = 1;

    for (long long i = 2; i < N + 1; i++) {
        if (!ifPrime[i]) continue;

        if (i * i < N + 1) {
            for (int j = i * i; j < N + 1; j += i)
                ifPrime[j] = false;
        }

        ans *= (long long)(pow(i, floor(log(N) / log(i))));
        ans %= divisor;
    }

    cout << ans;


    return 0;
}