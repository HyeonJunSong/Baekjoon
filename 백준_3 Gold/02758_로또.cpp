#include <iostream>
#include <vector>

using namespace std;

vector<vector<long long>> cache;
int T, N, M;

long long numOfLottery(int n, int st);

int main(){
    cin >> T;

    for(int t = 0; t < T; t++){
        cin >> N >> M;
        cache = vector<vector<long long>>(N + 1, vector<long long>(M + 1, -1));
        cout << numOfLottery(N, 1) << '\n';
    }

    return 0;
}

long long numOfLottery(int n, int st){

    if(n == 1)
        return (long long)(M - st + 1);

    long long tot = 0;
    for(int i = st; i * 2 <= M; i++){
        if(cache[n - 1][i * 2] == -1)
            cache[n - 1][i * 2] = numOfLottery(n - 1, i * 2);
        tot += cache[n - 1][i * 2];
    }

    return tot;
}