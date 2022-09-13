////22.09.13
//23m 8s

#include <iostream>
#include <deque>
#include <set>
#include <algorithm>

using namespace std;
int N, M, V;
deque<deque<int>> graph;

void DFS(int start);
void BFS(int start);
int main() {
    cin >> N >> M >> V;
    graph = deque<deque<int>>(N + 1, deque<int>());
    for (int i = 0; i < M; i++) {
        int st, ed;
        cin >> st >> ed;

        graph[st].push_back(ed);
        graph[ed].push_back(st);
    }

    for(int i = 0; i < graph.size(); i++)
        sort(graph[i].begin(), graph[i].end());

    DFS(V);
    cout << endl;
    BFS(V);

    return 0;
}

void DFS(int start) {
    deque<int> stack;
    stack.push_back(start);
    set<int> visted;

    while (!stack.empty()) {
        int curNode = stack.back();
        stack.pop_back();
        if (visted.find(curNode) != visted.end()) continue;

        cout << curNode << ' ';
        visted.insert(curNode);

        for (int i = graph[curNode].size() - 1; i >= 0; i--) {
            if (visted.find(graph[curNode][i]) == visted.end()) {
                stack.push_back(graph[curNode][i]);
            }
        }
    }
}

void BFS(int start) {
    deque<int> queue;
    queue.push_back(start);
    set<int> visted;

    while (!queue.empty()) {
        int curNode = queue.front();
        queue.pop_front();
        if (visted.find(curNode) != visted.end()) continue;

        cout << curNode << ' ';
        visted.insert(curNode);

        for (int i = 0; i < graph[curNode].size(); i++) {
            if (visted.find(graph[curNode][i]) == visted.end()) {
                queue.push_back(graph[curNode][i]);
            }
        }
    }
}