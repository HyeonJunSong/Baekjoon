#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class node{
public:
    int st;
    int ed;
    int T;

    bool operator<(node b) const{
        return T > b.T;
    }
};

int main(){
    int N, M, X;
    cin >> N >> M >> X;

    //입력
    vector<vector<pair<int,int>>> graph(N + 1);
    vector<vector<pair<int,int>>> graphReverse(N + 1);
    for(int i = 0; i < M; i++){
        int st, ed, T;
        cin >> st >> ed >> T;
        graph[st].push_back({ed, T});
        graphReverse[ed].push_back({st, T});
    }

    ////두 다익스트라 공통으로 사용할 변수
    priority_queue<node> PQ;
    vector<bool> visited(N + 1, false);

    //다익스트라 _ X부터 최단경로
    vector<int> shortestFromX(N + 1);
    PQ.push({X, X, 0});
    
    while(!PQ.empty()){
        node curNode = PQ.top();
        PQ.pop();
        
        if(visited[curNode.ed])
            continue;
        visited[curNode.ed] = true;
        
        shortestFromX[curNode.ed] = curNode.T;

        for(auto iter = graph[curNode.ed].begin(); iter != graph[curNode.ed].end(); iter++)
            if(!visited[iter->first])
                PQ.push({curNode.ed, iter->first, curNode.T + iter->second});
    }

    //다익스트라 _ X까지 최단경로
    vector<int> shortestToX(N + 1);
    visited = vector<bool>(N + 1, false);
    PQ.push({X, X, 0});
    
    while(!PQ.empty()){
        node curNode = PQ.top();
        PQ.pop();
        
        if(visited[curNode.ed])
            continue;
        visited[curNode.ed] = true;
        
        shortestToX[curNode.ed] = curNode.T;

        for(auto iter = graphReverse[curNode.ed].begin(); iter != graphReverse[curNode.ed].end(); iter++)
            if(!visited[iter->first])
                PQ.push({curNode.ed, iter->first, curNode.T + iter->second});
    }


    //답구하기
    int longestPath = 0;
    for(int i = 1; i < N + 1; i++)
        if(shortestFromX[i] + shortestToX[i] > longestPath)
            longestPath = shortestFromX[i] + shortestToX[i];
    
    cout << longestPath;
    return 0;
}