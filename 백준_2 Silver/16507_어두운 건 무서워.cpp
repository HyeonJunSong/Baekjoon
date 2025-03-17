#include <iostream>
#include <vector>

using namespace std;

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  int R, C, Q;
  cin >> R >> C >> Q;
  vector<vector<int>> image(R + 1, vector<int>(C + 1, 0));
  for(int i = 1; i <= R; i++)
    for(int j = 1; j <= C; j++)
      cin >> image[i][j];
  
  for(int i = 1; i <= R; i++)
    for(int j = 1; j <= C; j++)
      image[i][j] += image[i - 1][j] + image[i][j - 1] - image[i - 1][j - 1];
  
  for(int q = 0; q < Q; q++){
    int r1, c1, r2, c2;
    cin >> r1 >> c1 >> r2 >> c2;

    r1--, c1--;
    cout << (image[r2][c2] - image[r1][c2] - image[r2][c1] + image[r1][c1]) / ((r2 - r1) * (c2 - c1)) << '\n';
  }

  return 0;
}