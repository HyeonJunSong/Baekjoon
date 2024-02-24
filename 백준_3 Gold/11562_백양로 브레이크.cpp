#include <iostream>
#include <vector>

using namespace std;


int main(){

  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  int n, m;
  cin >> n >> m;

  vector<vector<int>> tree;
  tree = vector<vector<int>>(n + 1, vector<int>(n + 1, 987654321));
  for(int i = 0; i < m; i++){
    int u, v, b;
    cin >> u >> v >> b;

    if(b == 0){
      tree[u][v] = 0;
      tree[v][u] = 1;
    } else {
      tree[u][v] = 0;
      tree[v][u] = 0;
    }
  }

  for(int i = 1; i < n + 1; i++)
    tree[i][i] = 0;

  for(int k = 1; k < n + 1; k++){
    for(int i = 1; i < n + 1; i++){
      for(int j = 1; j < n + 1; j++){
        tree[i][j] = min(tree[i][j], tree[i][k] + tree[k][j]);
      }
    }
  }

  int k;
  cin >> k;
  for(int i = 0; i < k; i++){
    int s, e;
    cin >> s >> e;

    cout << tree[s][e] << "\n";

  }



  return 0;
}