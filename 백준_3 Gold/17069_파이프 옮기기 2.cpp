#include <iostream>
#include <vector>

using namespace std;

int N;
vector<vector<int>> house;

#define ll long long

vector<vector<pair<int, vector<pair<int, int>> > >> pipeMoves = {
    {
        {0, {{0, 2}}},
        {2, {{0, 2}, {1, 2}, {1, 1}}}
    },
    {
        {1, {{2, 0}}},
        {2, {{2, 0}, {2, 1}, {1, 1}}}
    },
    {
        {0, {{1, 2}}},
        {1, {{2, 1}}},
        {2, {{1, 2}, {2, 1}, {2, 2}}}
    },
};

int pipeEndPos[3][2] = {
    {0, 1},
    {1, 0},
    {1, 1},
};

vector<vector<ll>> memo;

ll getCnt(int pos, int pipeType){
    int I = pos / N, J = pos % N;
    if(I + pipeEndPos[pipeType][0] == N - 1 && J + pipeEndPos[pipeType][1] == N - 1) return 1;

    if(memo[pos][pipeType] != -1) return memo[pos][pipeType];

    ll ans = 0;

    for(int i = 0; i < pipeMoves[pipeType].size(); i++){
        bool ifPossible = true;
        for(int j = 0; j < pipeMoves[pipeType][i].second.size(); j++){
            int nxtI = I + pipeMoves[pipeType][i].second[j].first, nxtJ = J + pipeMoves[pipeType][i].second[j].second;
            if(0 > nxtI || nxtI >= N || 0 > nxtJ || nxtJ >= N){
                ifPossible = false;
                break;
            }
            if(house[nxtI][nxtJ]){
                ifPossible = false;
                break;
            }
        }
        if(!ifPossible) continue;
        ans += getCnt((I + pipeEndPos[pipeType][0]) * N + J + pipeEndPos[pipeType][1], pipeMoves[pipeType][i].first);
    }

    memo[pos][pipeType] = ans;
    return ans;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> N;
    house.assign(N, vector<int>(N));
    for(int i = 0; i < N; i++)
        for(int j = 0; j < N; j++)
            cin >> house[i][j];
    
    memo.assign(N * N, vector<ll>(3, -1));
    cout << getCnt(0, 0);
    

    return 0;
}