#include <iostream>
#include <vector>

using namespace std;

vector<vector<int>> tree;

int tot = 0;

void DFS(int curNode, int parent);

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N, W;
    cin >> N >> W;
    
    int st, ed;
    tree = vector<vector<int>>(N + 1);
    for(int i = 0; i < N - 1; i++){
        cin >> st >> ed;
        tree[st].push_back(ed);
        tree[ed].push_back(st);
    }

    DFS(1, 0);

    cout.precision(6);
    cout << fixed;
    cout << double(W) / tot;

    return 0;
}

void DFS(int curNode, int parent){
    if(tree[curNode].size() == 1 && curNode != 1){
        tot++;
        return;
    }

    for(auto iter = tree[curNode].begin(); iter != tree[curNode].end(); iter++){
        if(*iter == parent) continue;
        DFS(*iter, curNode);
    }
}