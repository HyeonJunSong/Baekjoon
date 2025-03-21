#include <iostream>
#include <vector>
#include <queue>

using namespace std;

#define MAX_VERTEX 303
#define INF 987654321

int flow[MAX_VERTEX][MAX_VERTEX];
int cap[MAX_VERTEX][MAX_VERTEX];

vector<int> graph[MAX_VERTEX];
int nxtV[MAX_VERTEX];
int levelOf[MAX_VERTEX];
int src, snk;

bool bfs(){
	for(int i = 0; i < MAX_VERTEX; i++) levelOf[i] = -1;
	levelOf[src] = 0;
	
	queue<int> Q;
	Q.push(src);
	
	while(!Q.empty()){
		int v = Q.front();
		Q.pop();
		
		for(auto nxt: graph[v]){
			if(levelOf[nxt] != -1) continue;
			if(flow[v][nxt] == cap[v][nxt]) continue;
			
			levelOf[nxt] = levelOf[v] + 1;
			Q.push(nxt);
		}
	}

	return levelOf[snk] != -1;
}

int dfs(int v, int curFlow){
	if(v == snk) return curFlow;
	
	while(nxtV[v] < graph[v].size()){
		int nxt = graph[v][nxtV[v]++];
		if(levelOf[nxt] - levelOf[v] != 1) continue;
        if(flow[v][nxt] == cap[v][nxt]) continue;
		
		int totFlow = dfs(nxt, min(curFlow, cap[v][nxt] - flow[v][nxt]));
		if(totFlow == 0) continue;
		
		flow[v][nxt] += totFlow;
		flow[nxt][v] -= totFlow;
		return totFlow;
	}
	
	return 0;
}

int dinic(){
    int maxFlow = 0;
    while(bfs()){
        for(int j = 0; j < MAX_VERTEX; j++) nxtV[j] = 0;
        while(int curFlow = dfs(src, INF)) maxFlow += curFlow;
    }

    return maxFlow;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int N, K, D;
    cin >> N >> K >> D;
    vector<int> foodLimits(D);
    src = N + D;
    snk = N + D + 1;
    for(int i = 0; i < N; i++){
        graph[src].push_back(i);
        graph[i].push_back(src);
        cap[src][i] = K;
    }

    for(int i = 0; i < D; i++){
        graph[N + i].push_back(snk);
        graph[snk].push_back(N + i);
        cin >> cap[N + i][snk];
    }

    for(int Z, i = 0; i < N; i++){
        cin >> Z;
        for(int food, j = 0; j < Z; j++){
            cin >> food; food--;
            
            cap[i][N + food] = 1;
            graph[i].push_back(N + food);
            graph[N + food].push_back(i);
        }
    }

    cout << dinic();

    return 0;
}