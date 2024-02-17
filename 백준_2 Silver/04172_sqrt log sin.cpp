#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

vector<int> memo(1000001, -1);

int mathProblem(int i){
  if(i == 0) return 1;

  if(memo[(int)(floor(i - sqrt(i)))] == -1)
    memo[(int)(floor(i - sqrt(i)))] = mathProblem((int)(floor(i - sqrt(i))));
  if(memo[(int)(floor(log(i)))] == -1)
    memo[(int)(floor(log(i)))] = mathProblem((int)(floor(log(i))));
  if(memo[(int)(floor(i * (sin(i) * sin(i))))] == -1)
    memo[(int)(floor(i * (sin(i) * sin(i))))] = mathProblem((int)(floor(i * (sin(i) * sin(i)))));
  
  return (memo[(int)(floor(i - sqrt(i)))] + memo[(int)(floor(log(i)))] + memo[(int)(floor(i * (sin(i) * sin(i))))]) % 1000000;
}

int main(){

  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  while(true){
    int num;
    cin >> num;
    if(num == -1) break;
    cout << mathProblem(num) << "\n";
  }

  return 0;
}