////2022.08.31
//이해 및 설계 : 11m 25s
//입력 : 1m 32s
//구현 : 12m 28s

//tot : 25m 47s

#include <iostream>
#include <vector>

using namespace std;

int minBetTwo(int a, int b);

int main(){
    int N;
    cin >> N;
    vector<vector<int>> cost(N, vector<int>(3));
    for(int i = 0; i < N; i++)
        cin >> cost[i][0] >> cost[i][1] >> cost[i][2];
    
    vector<int> memo = cost[0];

    vector<int> temp;
    for(int i = 1; i < N; i++){
        temp = memo;
        memo[0] = cost[i][0] + minBetTwo(temp[1], temp[2]);
        memo[1] = cost[i][1] + minBetTwo(temp[0], temp[2]);
        memo[2] = cost[i][2] + minBetTwo(temp[1], temp[0]);
    }

    cout << minBetTwo(memo[0], minBetTwo(memo[1], memo[2]));

    return 0;
}

int minBetTwo(int a, int b){
    return a < b ? a : b;
}