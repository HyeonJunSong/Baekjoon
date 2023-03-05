#include <iostream>
#include <vector>

using namespace std;

vector<vector<pair<int, int>>> graph;
vector<vector<int>> cache;

int shortestPath(int st, int ed);

vector<bool> visited;

#define INF 987654321

int main(){
    int N, M, X;
    cin >> N >> M >> X;
    graph = vector<vector<pair<int, int>>>(N + 1);

    int st, ed, t;
    for(int i = 0; i < M; i++){
        cin >> st >> ed >> t;
        graph[st].push_back(pair<int, int>(ed, t));
    }

    cache = vector<vector<int>>(N + 1, vector<int>(N + 1, -1));
    visited = vector<bool>(N + 1, false);

    int curPath;
    int ans = 0;

    for(int i = 1; i <= N; i++){
        if(i == X) continue;
        if(cache[i][X] == -1)
            cache[i][X] = shortestPath(i, X);
        curPath = cache[i][X];

        if(cache[X][i] == -1)
            cache[X][i] = shortestPath(X, i);
        curPath += cache[X][i];
        if(curPath > ans)
            ans = curPath;
    }

    cout << ans;

    return 0;
}

int shortestPath(int st, int ed){
    visited[st] = true;
    int shortest = INF;
    for(auto iter = graph[st].begin(); iter != graph[st].end(); iter++){
        if(visited[iter->first]) continue;
        if(iter->first == ed){
            if(shortest > iter->second)
                shortest = iter->second;
        }
        else{
            if(cache[iter->first][ed] == -1)
                cache[iter->first][ed] = shortestPath(iter->first, ed);
            if(shortest > cache[iter->first][ed] + iter->second)
                shortest = cache[iter->first][ed] + iter->second;
        }
    }
    visited[st] = false;
    return shortest;
}