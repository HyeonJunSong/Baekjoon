#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#define INF 1e9

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int N, M, s;
    cin >> N >> M >> s;
    vector<vector<int>> edges(M, vector<int>(3));
    for(int i = 0; i < M; i++) cin >> edges[i][0] >> edges[i][1] >> edges[i][2];

    vector<int> distance(N, INF);
    vector<int> parentOf(N, -1);

    distance[s] = 0;

    int cycleRoot;
    for(int i = 0; i < N; i++){
        cycleRoot = -1;
        for(int j = 0; j < M; j++){
            if(distance[edges[j][1]] <= distance[edges[j][0]] + edges[j][2]) continue;
            distance[edges[j][1]] = distance[edges[j][0]] + edges[j][2];
            parentOf[edges[j][1]] = edges[j][0];
            cycleRoot = edges[j][1];
        }
    }

    if(cycleRoot == -1){
        cout << "PATH\n";
        for(auto e: distance) cout << e << " ";
    } else {
        for(int i = 0; i < N; i++) cycleRoot = parentOf[cycleRoot];

        vector<int> cycle;
        cycle.push_back(cycleRoot);
        for(int cur = parentOf[cycleRoot]; cur != cycleRoot; cur = parentOf[cur]) cycle.push_back(cur);

        reverse(cycle.begin(), cycle.end());
        
        cout << "CYCLE\n";
        cout << cycle.size() <<'\n';
        cout << cycleRoot << " ";
        for(auto e: cycle) cout << e << " ";
    }


    return 0;
}