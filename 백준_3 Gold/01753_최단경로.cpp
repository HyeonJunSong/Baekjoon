////23.02.24
//이해 및 설계 : 3m 40s
//입력 : 2m 3s
//구현 : 1h 19m 50s

//tot : 1h 25m 33s

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class node{
public:
    int e;
    int w;

    node(int e, int w){
        this->e = e;
        this->w = w;
    }

    bool operator<(node b) const {
        return this->w > b.w;
    }
};

#define INF 987654321

int main(){
    ios_base :: sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int V, E;
    cin >> V >> E;

    int K;
    cin >> K;


    vector<vector<pair<int, int>>> graph = vector<vector<pair<int, int>>>(V + 1, vector<pair<int, int>>());
    
    for(int i = 0; i < E; i++){
        int u, v, w;
        cin >> u >> v >> w;
        graph[u].push_back(pair<int, int>(v, w));
    }

    vector<bool> visited = vector<bool>(V + 1, false);
    vector<int> minRoute(V + 1, INF);

    priority_queue<node> PQ;

    ////////////////////////////////////////////////////////////
    visited[K] = true;
    minRoute[K] = 0;
    for(auto iter = graph[K].begin(); iter != graph[K].end(); iter++){
        PQ.push(node(iter->first, iter->second));
    }

    while(!PQ.empty()){
        node curNode = PQ.top();

        PQ.pop();
        if(visited[curNode.e] == true) continue;
        visited[curNode.e] = true;
        minRoute[curNode.e] = curNode.w;

        for(auto iter = graph[curNode.e].begin(); iter != graph[curNode.e].end(); iter++){
            if(visited[iter->first] == false)
                PQ.push(node(iter->first, curNode.w + iter->second));
        }
    }

    for(auto iter = minRoute.begin() + 1; iter != minRoute.end(); iter++){
        if(*iter == INF)
            cout << "INF" << '\n';
        else
            cout << *iter << '\n';
    }

    return 0;
}