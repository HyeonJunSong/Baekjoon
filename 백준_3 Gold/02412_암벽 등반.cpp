#include <iostream>
#include <vector>
#include <map>
#include <queue>

using namespace std;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    map<int, map<int, int>> wall;
    int n, T;
    cin >> n >> T;

    vector<pair<int, int>> rocks;

    rocks.push_back({0, 0});
    wall[0] = map<int, int>();
    wall[0][0] = 0;

    for(int i = 1; i <= n; i++){
        int x, y;
        cin >> x >> y;
        rocks.emplace_back(x, y);
        if(wall.find(x) == wall.end()){
            wall[x] = map<int, int>();
            wall[x][y] = i;
        } else{
            wall[x][y] = i;
        }
    }

    vector<vector<int>> graph(n + 1);
    for(int i = 0; i < n + 1; i++)
        for(auto e1 = wall.lower_bound(rocks[i].first - 2); e1 != wall.upper_bound(rocks[i].first + 2); e1++)
            for(auto e2 = e1->second.lower_bound(rocks[i].second - 2); e2 != e1->second.upper_bound(rocks[i].second + 2); e2++)
                graph[i].emplace_back(e2->second);
    

    priority_queue<pair<int, int>> PQ;
    PQ.push({0, 0});
    vector<bool> visited(n + 1, false);

    int ans = -1;

    while(!PQ.empty()){
        pair<int, int> curNode = PQ.top();
        PQ.pop();

        if(visited[curNode.second]) continue;
        visited[curNode.second] = true;

        if(rocks[curNode.second].second == T){
            ans = -curNode.first;
            break;
        }


        for(auto e: graph[curNode.second]){
            if(visited[e]) continue;
            PQ.push({curNode.first - 1, e});
        }
    }

    cout << ans;

    return 0;
}