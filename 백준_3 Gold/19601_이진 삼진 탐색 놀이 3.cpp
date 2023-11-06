#include <iostream>

using namespace std;

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  int Q;
  cin >> Q;

  for(int i = 0; i < Q; i++){
    long long N;
    cin >> N;

    long long temp = N;
    int B = 0;

    while(N >= 2){
      N = max(N / 2, N - N / 2 - 1);
      B += 1;
    }

    int T = 0;
    N = temp;
    while(N >= 3){
      N = max(N / 3, N - 2 * N / 3 - 2);
      T += 2;
    }
    if(N == 2)
      T++;
    
    cout << B << ' ' << T << "\n";
  }

  return 0;
}