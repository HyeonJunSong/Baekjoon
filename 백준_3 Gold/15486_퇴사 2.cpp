#include <iostream>
#include <vector>

using namespace std;

int N;
vector<vector<int>> TP;
vector<int> memo;

int maxProfit(int ind);

int main(){
    cin >> N;
    TP = vector<vector<int>>(N, vector<int>(2));
    for(int i = 0; i < N; i++)
        cin >> TP[i][0] >> TP[i][1];

    memo = vector<int>(N + 1, -1);

    cout << maxProfit(0);
}

int maxProfit(int ind){
    if(ind == N || ind + TP[ind][0] > N) return 0;

    if(memo[ind + 1] == -1)
        memo[ind + 1] = maxProfit(ind + 1);

    if(memo[ind + TP[ind][0]] == -1)
        memo[ind + TP[ind][0]] = maxProfit(ind + TP[ind][0]);

    return memo[ind + 1] > memo[ind + TP[ind][0]] + TP[ind][1] ? memo[ind + 1] : memo[ind + TP[ind][0]] + TP[ind][1];

}