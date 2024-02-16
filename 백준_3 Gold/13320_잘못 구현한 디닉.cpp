#include <iostream>
#include <vector>
#include <random>

using namespace std;

int main(){

  // int N = 382;
  // int M = 251502;

  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<int> dis(1, 100000000);

  int N = 502;
  int M = 251502;

  cout << N << " " << M << "\n";
  for(int i = 1; i <= 502; i++){
    for(int j = 1; j <= 502; j++){
      if(i == j) continue;
      cout << i << ' ' << j << ' ' << dis(gen) << "\n";
    }
  }
  

  return 0;
}