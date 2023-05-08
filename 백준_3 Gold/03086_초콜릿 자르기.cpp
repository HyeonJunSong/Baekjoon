#include <iostream>
#include <vector>

using namespace std;

int minNumOfChocolate(int N, int M);

vector<vector<int>> cache;

int main(){
    int N, M;
    cin >> N >> M;

    if(N < M){
        cache = vector<vector<int>>(N + 1, vector<int>(M + 1, -1));
        cout << minNumOfChocolate(N, M);
    }
    else{
        cache = vector<vector<int>>(M + 1, vector<int>(N + 1, -1));
        cout << minNumOfChocolate(M, N);
    }
    return 0;
}

//N < M
int minNumOfChocolate(int N, int M){
    if(N == 0 || M == 0)
        return 0;
    if(N == M)
        return 1;
    if(N == 1)
        return M;
    if(M == 1)
        return N;

    int ans;

    //안 자른거
    if(cache[M % N][N] == -1)
        cache[M % N][N] = minNumOfChocolate(M % N, N);
    ans = cache[M % N][N] + M / N;

    for(int i = 1; i <= N / 2; i++){
        if(cache[i][M] == -1)
            cache[i][M] = minNumOfChocolate(i, M);
        if(cache[N - i][M] == -1)
            cache[N - i][M] = minNumOfChocolate(N - i, M);

        if(ans > cache[i][M] + cache[N - i][M])
            ans = cache[i][M] + cache[N - i][M];
    }

    for(int i = 1; i <= M / 2; i++){

        if(i < N){
            if(M - i < N){
                if(cache[i][N] == -1)
                    cache[i][N] = minNumOfChocolate(i, N);
                if(cache[M - i][N] == -1)
                    cache[M - i][N] = minNumOfChocolate(M - i, N);

                if(ans > cache[i][N] + cache[M - i][N])
                    ans = cache[i][N] + cache[M - i][N];
            }
            else{
                if(cache[i][N] == -1)
                    cache[i][N] = minNumOfChocolate(i, N);
                if(cache[N][M - i] == -1)
                    cache[N][M - i] = minNumOfChocolate(N, M - i);

                if(ans > cache[i][N] + cache[N][M - i])
                    ans = cache[i][N] + cache[N][M - i];
            }
        }
        else{
            if(M - i < N){
                if(cache[N][i] == -1)
                    cache[N][i] = minNumOfChocolate(N, i);
                if(cache[M - i][N] == -1)
                    cache[M - i][N] = minNumOfChocolate(M - i, N);

                if(ans > cache[N][i] + cache[M - i][N])
                    ans = cache[N][i] + cache[M - i][N];
            }
            else{
                if(cache[N][i] == -1)
                    cache[N][i] = minNumOfChocolate(N, i);
                if(cache[N][M - i] == -1)
                    cache[N][M - i] = minNumOfChocolate(N, M - i);

                if(ans > cache[N][i] + cache[N][M - i])
                    ans = cache[N][i] + cache[N][M - i];
            }
        }
    }

    return ans;
}