////22.09.14
//56m 5s

//별짓 다하다가 결국 메모이제이션으로 해결.
//시간제한 0.15초가 생각보다 넉넉하다.

#include <iostream>
#include <vector>

using namespace std;

vector<int> memo;

int minCnt(int N);
int main(){
    int N;
    cin >> N;
    memo = vector<int>(N, -1);

    cout << minCnt(N);
}

int minCnt(int N){
    if(N == 1) return 0;

    if(memo[N - 1] == -1) memo[N - 1] = minCnt(N - 1) + 1;
    int min = memo[N - 1];
    if(N % 3 == 0){
        if(memo[N / 3] == -1)
            memo[N / 3] = minCnt(N / 3) + 1;
        if(min > memo[N / 3]) min = memo[N / 3];
    }
    if(N % 2 == 0){
        if(memo[N / 2] == -1)
            memo[N / 2] = minCnt(N / 2) + 1;
        if(min > memo[N / 2]) min = memo[N / 2];
    }

    return min;
}