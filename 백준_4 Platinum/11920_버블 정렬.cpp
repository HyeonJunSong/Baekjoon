#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  int N, K;
  cin >> N >> K;
  int num;

  priority_queue<int> PQ;

  if(K >= N - 1){
    for(int i = 0; i < N; i++){
      cin >> num;
      PQ.push(-num);
    }
    for(int i = 0; i < N; i++){
      cout << -PQ.top() << " ";
      PQ.pop();
    }
    return 0;
  }
  

  for(int i = 0; i < K + 1; i++){
    cin >> num;
    PQ.push(-num);
  }
  
  for(int i = 0; i < N - (K + 1); i++){
    cout << -PQ.top() << " ";
    PQ.pop();
    cin >> num;
    PQ.push(-num);
  }
  for(int i = N - (K + 1); i < N; i++){
    cout << -PQ.top() << " ";
    PQ.pop();
  }
  
  return 0;
}