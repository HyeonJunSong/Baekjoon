#include <iostream>
#include <vector>

using namespace std;

vector<vector<pair<int, int>>> topLeft = {

  //일자
  {
    {0, 1},
    {0, 2},
    {0, 3},
  },
  {
    {1, 0},
    {2, 0},
    {3, 0},
  },

  //네모
  {
    {0, 1},
    {1, 0},
    {1, 1},
  },

  //니은
  {
    {1, 0},
    {2, 0},
    {2, 1},
  },
  {
    {0, 1},
    {1, 0},
    {0, 2},
  },
  {
    {0, 1},
    {1, 1},
    {2, 1},
  },
  {
    {0, 1},
    {0, 2},
    {-1, 2},
  },
  {
    {1, 0},
    {2, 0},
    {2, -1},
  },
  {
    {1, 0},
    {1, 1},
    {1, 2},
  },
  {
    {1, 0},
    {2, 0},
    {0, 1},
  },
  {
    {0, 1},
    {0, 2},
    {1, 2},
  },

  //리을
  {
    {1, 0},
    {1, 1},
    {2, 1},
  },
  {
    {0, 1},
    {-1, 1},
    {-1, 2},
  },
  {
    {0, 1},
    {1, 1},
    {1, 2}
  },
  {
    {1, 0},
    {1, -1},
    {2, -1}
  },

  //ㅗ자
  {
    {0, 1},
    {0, 2},
    {1, 1},
  },
  {
    {0, 1},
    {0, 2},
    {-1, 1},
  },
  {
    {1, 0},
    {2, 0},
    {1, 1},
  },
  {
    {1, 0},
    {2, 0},
    {1, -1},
  },
};

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int N, M;
  cin >> N >> M;

  vector<vector<int>> board(N, vector<int>(M));
  for(int i = 0; i < N; i++)
    for(int j = 0; j < M; j++)
      cin >> board[i][j];

  int ans = 0;
  for(int i = 0; i < N; i++){
    for(int j = 0; j < M; j++){

      for(auto e: topLeft){
        int curSum = board[i][j];

        for(auto e2: e){
          if(0 <= i + e2.first && i + e2.first < N
          && 0 <= j + e2.second && j + e2.second < M)
            curSum += board[i + e2.first][j + e2.second];
          else{
            curSum = -987654321;
            break;
          }
        }

        ans = max(curSum, ans);
      }
    }
  }

  cout << ans;


  return 0;
}