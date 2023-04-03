#include <iostream>
#include <vector>

using namespace std;

vector<int> s;
vector<vector<int>> tree;
vector<bool> visited;

void DFS(int curNode);

int main(){

    int N, M;
    cin >> N >> M;

    int st, ed;
    tree = vector<vector<int>>(N + 1, vector<int>());
    for(int i = 0; i < M; i++){
        cin >> st >> ed;
        tree[st].push_back(ed);
    }

    visited = vector<bool>(N + 1, false);
    for(int i = 1; i <= N; i++)
        if(!visited[i])
            DFS(i);
    
    for(auto iter = s.rbegin(); iter != s.rend(); iter++)
        cout << *iter << ' ';
    
    return 0;
}

void DFS(int curNode){
    visited[curNode] = true;
    for(auto iter = tree[curNode].begin(); iter != tree[curNode].end(); iter++)
        if(!visited[*iter])
            DFS(*iter);
    s.push_back(curNode);
}