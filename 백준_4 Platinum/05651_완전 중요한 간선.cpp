#include <iostream>
#include <vector>
#include <queue>

using namespace std;

#define INF 987654321

class Edge{
	public:
	int e;
	int cap, flow;
	int revIdx;
};

class Graph{
	public:
	vector<vector<Edge>> graph;
	vector<int> levelOf;
	vector<int> edgeIdx;
	int src, snk;

	Graph(int vertexNum, int src, int snk) : src(src), snk(snk) {
		graph.assign(vertexNum + 1, {});
		levelOf.assign(vertexNum + 1, -1);
		edgeIdx.assign(vertexNum + 1, 0);
	}

	void addEdge(int s, int e, int v){
		graph[s].push_back({e, v, 0, (int)graph[e].size()});
		graph[e].push_back({s, 0, 0, (int)graph[s].size() - 1});
	}

	int dfs(int v, int flow){
		if(v == snk) return flow;

		while(edgeIdx[v] < graph[v].size()){
			int i = edgeIdx[v]++;

			if(levelOf[graph[v][i].e] - levelOf[v] != 1) continue;
			if(graph[v][i].flow == graph[v][i].cap) continue;

			int totFlow = dfs(graph[v][i].e, min(flow, graph[v][i].cap - graph[v][i].flow));
			if(totFlow == 0) continue;
			
			graph[v][i].flow += totFlow;
			graph[graph[v][i].e][graph[v][i].revIdx].flow -= totFlow;
			return totFlow;
		}

		return 0;
	}

	bool bfs(){
		fill(levelOf.begin(), levelOf.end(), -1);

		queue<int> Q;
		Q.push(src);
		levelOf[src] = 0;

		while(!Q.empty()){
			int cur = Q.front(); Q.pop();
			for(auto edge: graph[cur]){
				if(levelOf[edge.e] != -1) continue;
				if(edge.flow == edge.cap) continue;
				levelOf[edge.e] = levelOf[cur] + 1;
				Q.push(edge.e);
			}
		}

		return levelOf[snk] != -1;
	}

	int dinic(){
		int maxFlow = 0;
		while(bfs()){
			fill(edgeIdx.begin(), edgeIdx.end(), 0);
			while(int flow = dfs(src, INF)) maxFlow += flow;
		}
		return maxFlow;
	}
};

void testCase(){

	int N, M;
	cin >> N >> M;

	Graph g(N, 1, N);

	for(int f, t, b, i = 0; i < M; i++){
		cin >> f >> t >> b;
		g.addEdge(f, t, b);
	}

	g.dinic();

	int ans = 0;

	vector<vector<bool>> ifReachable(N + 1, vector<bool>(N + 1, false));

	for(int s = 1; s <= N; s++){
		ifReachable[s][s] = true;
		queue<int> Q; Q.push(s);
		while(!Q.empty()){
			int cur = Q.front(); Q.pop();
			for(auto e: g.graph[cur]){
				if(ifReachable[s][e.e]) continue;
				if(e.flow == e.cap) continue;
				ifReachable[s][e.e] = true;
				Q.push(e.e);
			}
		}
	}
	for(int v = 1; v <= N; v++){
		for(auto edge: g.graph[v]){
			if(edge.cap == 0) continue;
			if(edge.cap > edge.flow) continue;

			if(!ifReachable[v][edge.e]) ans++;
		}
	}

	cout << ans << '\n';


}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int T;
	cin >> T;
	for(int t = 0; t < T; t++) testCase();

	return 0;
}