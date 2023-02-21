////23.02.21
//이해 및 설계 : 24m 23s
//입력 : 1m 31s
//구현 : 1h 54m 47s

//tot : 2h 20m 41s

#include <iostream>
#include <vector>

using namespace std;

vector<vector<long long>> cache_comb;
vector<long long> cache_fact;
vector<vector<long long>> cache;

#define div 1000000007

long long getnumOfCases(int N, int L, int R);
long long getnumOfCases_half(int N, int L);
long long combination(int N, int R);
long long factorial(int N);

int main() {
    int N, L, R;
    cin >> N >> L >> R;

    cache_comb = vector<vector<long long>>(N + 1, vector<long long>(N + 1, -1));
    cache_fact = vector<long long>(N + 1, -1);
    cache = vector<vector<long long>>(N + 1, vector<long long>(N + 1, -1));


    cout << getnumOfCases(N, L, R);
    return 0;
}

long long getnumOfCases(int N, int L, int R) {

    if (L == 1 && R == 1) {
        if (N == 1) return 1;
        else return 0;
    }
    if (L == 1) {
        if (cache[N - 1][R - 1] == -1)
            cache[N - 1][R - 1] = getnumOfCases_half(N - 1, R - 1);
        return cache[N - 1][R - 1];
    }
    if (R == 1) {
        if (cache[N - 1][L - 1] == -1)
            cache[N - 1][L - 1] = getnumOfCases_half(N - 1, L - 1);
        return cache[N - 1][L - 1];
    }

    long long tot = 0;
    for (int t = L; t <= N - R + 1; t++) {
        if (cache[t - 1][L - 1] == -1)
            cache[t - 1][L - 1] = getnumOfCases_half(t - 1, L - 1);

        if (cache[N - t][R - 1] == -1)
            cache[N - t][R - 1] = getnumOfCases_half(N - t, R - 1);

        if (cache_comb[N - 1][t - 1] == -1)
            cache_comb[N - 1][t - 1] = combination(N - 1, t - 1);

        tot += (((cache[t - 1][L - 1] * cache[N - t][R - 1]) % div) * cache_comb[N - 1][t - 1]) % div;
        tot = tot % div;
    }

    return tot;
}

long long getnumOfCases_half(int N, int L) {
    if (N == L) return 1;
    if (L == 0) return 0;
    if (L == 1) {
        return factorial(N - 1);
    };

    long long tot = 0;

    for (int t = L; t <= N; t++) {
        if (cache[t - 1][L - 1] == -1)
            cache[t - 1][L - 1] = getnumOfCases_half(t - 1, L - 1);
        if (cache_fact[N - t] == -1)
            cache_fact[N - t] = factorial(N - t);
        if (cache_comb[N - 1][t - 1] == -1)
            cache_comb[N - 1][t - 1] = combination(N - 1, t - 1);
        tot += (((cache[t - 1][L - 1] * cache_fact[N - t]) % div) * cache_comb[N - 1][t - 1]) % div;
        tot = tot % div;
    }

    return tot;
}

long long combination(int N, int R) {
    if (R == 0 || R == N) return 1;
    //    if(R == 1 || R == N - 1) return N;

    if (cache_comb[N - 1][R] == -1)
        cache_comb[N - 1][R] = combination(N - 1, R);
    if (cache_comb[N - 1][R - 1] == -1)
        cache_comb[N - 1][R - 1] = combination(N - 1, R - 1);

    return (cache_comb[N - 1][R] + cache_comb[N - 1][R - 1]) % div;
}

long long factorial(int N) {
    if (N == 0) return 1;

    if (cache_fact[N] == -1)
        cache_fact[N] = (factorial(N - 1) * N) % div;

    return cache_fact[N];
}