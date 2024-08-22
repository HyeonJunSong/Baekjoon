#include <iostream>
#include <queue>

using namespace std;

int main(){

  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  int N;
  cin >> N;

  priority_queue<int> PQ;

  for(int i = 0; i < N; i++){
    int inp;
    cin >> inp;

    if(inp > 0){
      PQ.push(-inp);
    } else {
      if(PQ.empty()){
        cout << "0\n";
      } else {
        cout << -PQ.top() << "\n";
        PQ.pop();
      }
    }
  }


  return 0;
}