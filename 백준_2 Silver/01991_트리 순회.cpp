#include <iostream>
#include <vector>

using namespace std;

vector<pair<int, int>> tree;

void preOrder(int idx){
  if(idx == -1) return;
  cout << (char)(65 + idx);
  preOrder(tree[idx].first);
  preOrder(tree[idx].second);

  return;
}
void inOrder(int idx){
  if(idx == -1) return;
  inOrder(tree[idx].first);
  cout << (char)(65 + idx);
  inOrder(tree[idx].second);

  return;
}
void postOrder(int idx){
  if(idx == -1) return;
  postOrder(tree[idx].first);
  postOrder(tree[idx].second);
  cout << (char)(65 + idx);

  return;
}

int main(){
  int N;
  cin >> N;

  tree.assign(N, {-1, -1});
  for(int i = 0; i < N; i++){
    char a, b, c;
    cin >> a >> b >> c;
    if(b == '.')
      tree[(int)(a - 'A')].first = -1;
    else
      tree[(int)(a - 'A')].first = (int)(b - 'A');
    if(c == '.')
      tree[(int)(a - 'A')].second = -1;
    else
      tree[(int)(a - 'A')].second = (int)(c - 'A');
  }

  preOrder(0);
  cout << '\n';
  inOrder(0);
  cout << '\n';
  postOrder(0);

  return 0;
}