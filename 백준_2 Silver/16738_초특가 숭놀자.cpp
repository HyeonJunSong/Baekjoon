#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  int N, Q;
  cin >> N >> Q;
  vector<bool> isRoomEmpty(N + 1, true);
  vector<pair<int, pair<int, int>>> customors;

  for(int q = 0; q < Q; q++){
    string query;
    cin >> query;

    if(query == "new"){
      int X, Y;
      cin >> X >> Y;

      int L = -1, R;
      int curCnt = 0;
      for(int i = 1; i <= N; i++){
        if(isRoomEmpty[i]){
          curCnt++;
          if(curCnt == Y){
            R = i;
            L = i - Y + 1;
            break;
          }
        }
        else
          curCnt = 0;
      }

      if(L == -1){
        cout << "REJECTED\n";
      } else {
        customors.push_back({X, {L, R}});
        cout << L << " " << R << '\n';
        for(int i = L; i <= R; i++)
          isRoomEmpty[i] = false;
      }
    } else if(query == "in"){
      int A, B;
      cin >> A >> B;
      customors[A - 1].first += B;
    } else {
      int A, B;
      cin >> A >> B;
      customors[A - 1].first -= B;
      if(customors[A - 1].first == 0){
        for(int i = customors[A - 1].second.first; i <= customors[A - 1].second.second; i++)
          isRoomEmpty[i] = true;
        cout << "CLEAN " << customors[A - 1].second.first << " " << customors[A - 1].second.second << '\n';
      }
    }

  }


  return 0;
}