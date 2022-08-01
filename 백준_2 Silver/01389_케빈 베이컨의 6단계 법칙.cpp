#include <iostream>
#include <vector>
#include <set>

using namespace std;

#define MAX 987654321

vector<vector<int>> graph;
vector<vector<int>> memo;

int minDis(int st, int ed, set<int> fromNow);

int main() {
	int N, M;
	cin >> N >> M;
	graph = vector<vector<int>>(N, vector<int>());
	memo = vector<vector<int>>(N, vector<int>(N, -1));
	for (int i = 0; i < M; i++) {
		int inp1, inp2;
		cin >> inp1 >> inp2;
		inp1--; inp2--;
		graph[inp1].push_back(inp2);
		graph[inp2].push_back(inp1);
		memo[inp1][inp2] = 1;
		memo[inp2][inp1] = 1;
	}

	int totMax = MAX;
	int ans;
	for (int i = 0; i < N; i++) {
		int tot = 0;
		for (int j = 0; j < N; j++) {
			set<int> fromNow;
			if (i == j) continue;
			tot += minDis(i, j, fromNow);
		}
		if (totMax > tot) {
			totMax = tot;
			ans = i;
		}
	}
	cout << ans + 1;
	
	return 0;
}

int minDis(int st, int ed, set<int> fromNow) {
	fromNow.insert(st);

	if (memo[st][ed] != -1) return memo[st][ed];

	int min = MAX;
	for (int i = 0; i < graph[st].size(); i++) {
		if (fromNow.find(graph[st][i]) != fromNow.end()) continue;

		int res;
		if (memo[graph[st][i]][ed] == -1) res = minDis(graph[st][i], ed, fromNow);
		else res = 1;
		if (min > res) min = res;
	}

	return min + 1;
}