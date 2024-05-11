#include <iostream>
#include <vector>
#include <set>

using namespace std;

int main(){

  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  int N;
  cin >> N;
  
  set<int> stackTops;
  for(int i = 0; i < N; i++){
    int cur;
    cin >> cur;

    if(stackTops.upper_bound(-cur) == stackTops.end()){
      if(stackTops.size() < 4)
        stackTops.insert(-cur);
      else{
        cout << "NO";
        return 0;
      }
    } else{
      stackTops.erase(stackTops.lower_bound(-cur));
      stackTops.insert(-cur);
    }
  }

  cout << "YES";
  return 0;
}