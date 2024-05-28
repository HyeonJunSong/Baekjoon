#include <iostream>
#include <vector>

#define INF 987654321

using namespace std;

void testCase(){

    int N, M, W;
    cin >> N >> M >> W;

    int S, E, T;
    vector<vector<pair<int, int>>> graph(N);
    for(int i = 0; i < M; i++){
        cin >> S >> E >> T;
        S--; E--;
        graph[S].emplace_back(E, T);
        graph[E].emplace_back(S, T);
    }
    for(int i = 0; i < W; i++){
        cin >> S >> E >> T;
        S--; E--;
        graph[S].emplace_back(E, -T);
    }

    vector<int> minDis(N, INF);
    for(int i = 0; i < N - 1; i++){
        vector<int> newMinDis = minDis;
        for(int j = 0; j < N; j++)
            for(auto e: graph[j])
                newMinDis[e.first] = min(newMinDis[e.first], minDis[j] + e.second);
        
        minDis = newMinDis;
    }

    //음수 사이클 체크
    bool ifNegExist = false;
    for(int j = 0; j < N; j++){
        for(auto e: graph[j]){
            if(minDis[e.first] > minDis[j] + e.second){
                ifNegExist = true;
                break;
            }
        }
    }

    if(ifNegExist) cout << "YES\n";
    else cout << "NO\n";

}

int main(){

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int TC;
    cin >> TC;

    for(int i = 0; i < TC; i++)
        testCase();

    return 0;
}