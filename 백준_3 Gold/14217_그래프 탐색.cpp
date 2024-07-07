#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int n;
vector<vector<bool>> city;

void printMinVisits(){

  vector<int> minVisits(n, -1);

  queue<pair<int, int>> Q;
  Q.push({0, 0});

  vector<bool> visited(n, false);

  while(!Q.empty()){
    pair<int, int> curNode = Q.front();
    Q.pop();

    if(visited[curNode.second]) continue;
    visited[curNode.second] = true;

    minVisits[curNode.second] = -1 * curNode.first;

    for(int i = 0; i < n; i++){
      if(!city[curNode.second][i]) continue;
      if(visited[i]) continue;

      Q.push({curNode.first - 1, i});
    }
  }

  for(auto e: minVisits)
    cout << e << " ";
  cout << "\n";

}

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  int m;
  cin >> n >> m;

  city = vector<vector<bool>>(n, vector<bool>(n, false));
  for(int i = 0; i < m; i++){
    int st, ed;
    cin >> st >> ed;
    st--; ed--;
    city[st][ed] = true;
    city[ed][st] = true;
  }

  int q;
  cin >> q;

  for(int _ = 0; _ < q; _++){
    int a, i, j;
    cin >> a >> i >> j;
    i--; j--;

    switch(a){
      case 1:
        city[i][j] = true;
        city[j][i] = true;
      break;
      case 2:
        city[i][j] = false;
        city[j][i] = false;
      break;
    }

    printMinVisits();
  }


  return 0;
}