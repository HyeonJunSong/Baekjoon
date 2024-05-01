#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

#define ll long long

class Node{
public:

  //범위 : [st, ed]
  int st;
  int ed;
  ll val;

  Node* L;
  Node* R;

  Node(){
    st = 0;
    ed = 0;
    val = 0;
    L = nullptr;
    R = nullptr;
  }

  Node(Node* a){
    st = a->st;
    ed = a->ed;
    val = a->val;
    L = a->L;
    R = a->R;
  }

  ~Node(){
    delete L;
    delete R;
  }
};

void segInit(Node*& node, int st, int ed){

  node = new Node();
  node->st = st;
  node->ed = ed;

  if(st == ed){
    node->val = 0;
    return;
  }
  
  segInit(node->L, st, st + (ed - st) / 2);
  segInit(node->R, st + (ed - st) / 2 + 1, ed);
  node->val = 0;
}

void segUpdate(Node* prvTree, Node* curTree, int targetIdx){
  if(prvTree->st == prvTree->ed){
    curTree->val += 1;
    return;
  }

  if(prvTree->L->ed >= targetIdx){
    curTree->L = new Node(prvTree->L);
    segUpdate(prvTree->L, curTree->L, targetIdx);
  } else{
    curTree->R = new Node(prvTree->R);
    segUpdate(prvTree->R, curTree->R, targetIdx);
  } 
  curTree->val = curTree->L->val + curTree->R->val;
  return;
}

ll segGetVal(Node* tree, int st, int ed){
  if(tree->st == st && tree->ed == ed){
    return tree->val;
  }

  if(tree->L->ed >= ed)
    return segGetVal(tree->L, st, ed);
  if(tree->R->st <= st)
    return segGetVal(tree->R, st, ed);
  return segGetVal(tree->L, st, tree->L->ed) + segGetVal(tree->R, tree->R->st, ed);
}

void testCase(){

  int n, m;
  cin >> n >> m;

  vector<pair<int, int>> points(n);
  for(int i = 0; i < n; i++)
    cin >> points[i].first >> points[i].second;
  sort(points.begin(), points.end());
  
  vector<Node*> rootOf(n + 1);
  segInit(rootOf[0], 0, 100000);

  map<int, int> idxOf;
  for(int i = 1; i < n + 1; i++){
    rootOf[i] = new Node(rootOf[i - 1]);
    segUpdate(rootOf[i - 1], rootOf[i], points[i - 1].second);
    idxOf[-1 * points[i - 1].first] = i;
  }

  ll ans = 0;
  for(int i = 0; i < m; i++){
    int l, r, b, t;
    cin >> l >> r >> b >> t;
    
    ans += segGetVal(rootOf[idxOf.lower_bound(-1 * r)->second], b, t);
    if(idxOf.upper_bound(-1 * l) != idxOf.end())
      ans -= segGetVal(rootOf[idxOf.upper_bound(-1 * l)->second], b, t);
  }
  cout << ans << "\n";

}

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int T;
  cin >> T;
  for(int t = 0; t < T; t++)
    testCase();

  return 0;
}

