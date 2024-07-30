#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

int main(){

  ios_base::sync_with_stdio(false);
  cout.tie(NULL);

  int N;
  cin >> N;

  vector<long double> x(N);
  for(int i = 0; i < N; i++)
    cin >> x[i];
 
  long double minX = 1.0; 
  for(auto e: x)
    minX = min(minX, e);
  
  for(int i = 0; i < N; i++)
    x[i] /= minX;
  
  long double minErrorRate = 1;
  int minErrorRateIdx = 0;
  for(int i = 1; i <= 10000; i++){

    long double curError = 0;
    for(int j = 0; j < N; j++)
      curError = max(curError, abs(round(x[j] * i) - x[j] * i));
    
    if(minErrorRate > curError){
      minErrorRate = curError;
      minErrorRateIdx = i;
    }

    if(minErrorRate < 0.0001) break;
  }

  for(auto e: x)
    cout << (int)(round(e * minErrorRateIdx)) << "\n";

  return 0;
}