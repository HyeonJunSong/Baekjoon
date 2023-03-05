#include <iostream>
#include <vector>
#include <queue>

using namespace std;

vector<vector<pair<int, int>>> graph;
vector<vector<pair<int, int>>> graph_reversed;

class node{
public:
    int st;
    int ed;
    int weight;

    node(int st, int ed, int weight){
        this->st = st;
        this->ed = ed;
        this->weight = weight;
    }

    bool operator<(node b) const{
        return weight > b.weight;
    }
};

int main(){
    int N, M, X;
    cin >> N >> M >> X;
    graph = vector<vector<pair<int, int>>>(N + 1);
    graph_reversed = vector<vector<pair<int, int>>>(N + 1);

    int st, ed, t;
    for(int i = 0; i < M; i++){
        cin >> st >> ed >> t;
        graph[st].push_back(pair<int, int>(ed, t));
        graph_reversed[ed].push_back(pair<int, int>(st, t));
    }

    vector<bool> visited = vector<bool>(N + 1, false);
    priority_queue<node> PQ;
    
    for(auto iter = graph[X].begin(); iter != graph[X].end(); iter++)
        PQ.push(node(X, iter->first, iter->second));

    visited[X] = true;
    
    vector<int> shortestPath = vector<int>(N + 1, 0);

    while(!PQ.empty()){
        node curNode = PQ.top();
        PQ.pop();

        if(visited[curNode.ed]) continue;
        visited[curNode.ed] = true;

        shortestPath[curNode.ed] = shortestPath[curNode.st] + curNode.weight;

        for(auto iter = graph[curNode.ed].begin(); iter != graph[curNode.ed].end(); iter++)
            PQ.push(node(curNode.ed, iter->first, iter->second));
    }


    visited = vector<bool>(N + 1, false);
    
    for(auto iter = graph_reversed[X].begin(); iter != graph_reversed[X].end(); iter++)
        PQ.push(node(X, iter->first, iter->second));

    visited[X] = true;
    
    vector<int> shortestPath_reversed = vector<int>(N + 1, 0);

    while(!PQ.empty()){
        node curNode = PQ.top();
        PQ.pop();

        if(visited[curNode.ed]) continue;
        visited[curNode.ed] = true;

        shortestPath_reversed[curNode.ed] = shortestPath_reversed[curNode.st] + curNode.weight;

        for(auto iter = graph_reversed[curNode.ed].begin(); iter != graph_reversed[curNode.ed].end(); iter++)
            PQ.push(node(curNode.ed, iter->first, iter->second));
    }

    int longestPath = 0;

    for(int i = 1; i <= N; i++){
        if(longestPath < shortestPath[i] + shortestPath_reversed[i])
            longestPath = shortestPath[i] + shortestPath_reversed[i];
    }

    cout << longestPath;


    return 0;
}