#include <iostream>
#include <vector>

using namespace std;

bool testCase(){
  int n;
  cin >> n;
  if(n == 0) return false;

  vector<vector<int>> matrix(n, vector<int>(n));
  for(int i = 0; i < n; i++){
    for(int j = 0; j < n; j++){
      cin >> matrix[i][j];
    }
  }

  int oddRow = -1;
  for(int i = 0; i < n; i++){
    int curSum = 0;
    for(int j = 0; j < n; j++) curSum += matrix[i][j];
    if(curSum % 2 == 0) continue;
    oddRow = oddRow != -1 ? n : i;
  }

  int oddCol = -1;
  for(int j = 0; j < n; j++){
    int curSum = 0;
    for(int i = 0; i < n; i++) curSum += matrix[i][j];
    if(curSum % 2 == 0) continue;
    oddCol = oddCol != -1 ? n : j;
  }

  if(oddRow == -1 && oddCol == -1)
    cout << "OK\n";
  else if(oddRow == n || oddCol == n)
    cout << "Corrupt\n";
  else
    cout << "Change bit (" << oddRow + 1 <<"," << oddCol + 1 << ")\n";

  return true;
}

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  while(testCase());

  return 0;
}