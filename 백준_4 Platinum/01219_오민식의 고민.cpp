#include <iostream>
#include <vector>
#include <climits>

using namespace std;

#define NINF LLONG_MIN
#define INF LLONG_MAX

#define ll long long

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int N, st, ed, M;
    cin >> N >> st >> ed >> M;

    vector<vector<int>> edges(M, vector<int>(3));
    for(int i = 0; i < M; i++)
        for(int j = 0; j < 3; j++) cin >> edges[i][j];
    
    vector<ll> earns(N);
    for(int i = 0; i < N; i++) cin >> earns[i];

    vector<ll> curCostOf(N, NINF);
    curCostOf[st] = earns[st];
    for(int i = 0; i < N; i++){
        for(int j = 0; j < M; j++){
            if(curCostOf[edges[j][0]] == NINF) continue;
            curCostOf[edges[j][1]] = max(
                curCostOf[edges[j][1]],
                curCostOf[edges[j][0]] - edges[j][2] + earns[edges[j][1]]
            );
        }
    }
    
    //무한 음수 사이클 체크
    for(int i = 0; i < N; i++){
        for(int j = 0; j < M; j++){
            if(curCostOf[edges[j][0]] == NINF) continue;
            if(curCostOf[edges[j][0]] == INF) {
                curCostOf[edges[j][1]] = INF;
                continue;
            }
            if(curCostOf[edges[j][1]] >= curCostOf[edges[j][0]] - edges[j][2] + earns[edges[j][1]]) continue;
            curCostOf[edges[j][1]] = INF;
        }
    }
    
    if(curCostOf[ed] == INF) cout << "Gee";
    else if(curCostOf[ed] == NINF) cout << "gg";
    else cout << curCostOf[ed];

    return 0;
}