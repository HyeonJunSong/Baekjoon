#include <iostream>
#include <vector>

using namespace std;

int main(){

  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  int N;
  cin >> N;

  vector<int> arr(N);
  for(int i = 0; i < N; i++)
    cin >> arr[i];
  
  vector<int> ans(N);

  vector<int> stack;
  for(int i = N - 1; i >= 0; i--){
    while(!stack.empty() && stack.back() <= arr[i])
      stack.pop_back();
    
    if(stack.size() == 0) ans[i] = -1;
    else ans[i] = stack.back();
    stack.push_back(arr[i]);
  }

  for(auto e: ans)
    cout << e << " ";


  return 0;
}