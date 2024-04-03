#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <set>
#include <algorithm>

using namespace std;

#define ll long long

int dnaToInt(char dna){
  switch(dna){
    case 'A':
      return 0;
    case 'G':
      return 1;
    case 'C':
      return 2;
    case 'T':
      return 3;
  }
}

class Node {
public:

  bool ifEnd;
  vector<Node*> children;
  Node* fail;

  Node() {
    ifEnd = false;
    children = vector<Node*>(4, NULL);
    fail = NULL;
  }

  ~Node(){
    for(auto e: children)
      delete e;
  }
};

char dna[1000001];
char marker[101];

void testCase(){

  int n, m;
  cin >> n >> m;
  cin >> dna;
  cin >> marker;

  //트라이 트리 구축
  Node* root = new Node();
  for(int i = 0; i < m - 1; i++) {
    for(int j = i + 1; j < m; j++){
      Node* curNode = root;
      for (int k = 0; k < m; k++) {
        if(i <= k && k <= j){
          if (curNode->children[dnaToInt(marker[i + j - k])] == NULL)
            curNode->children[dnaToInt(marker[i + j - k])] = new Node();
          curNode = curNode->children[dnaToInt(marker[i + j - k])];
        } else{
          if (curNode->children[dnaToInt(marker[k])] == NULL)
            curNode->children[dnaToInt(marker[k])] = new Node();
          curNode = curNode->children[dnaToInt(marker[k])];
        }
      }
      curNode->ifEnd = true;
    }
  }
  Node* tempNode = root;
  for (int k = 0; k < m; k++) {
    if (tempNode->children[dnaToInt(marker[k])] == NULL)
      tempNode->children[dnaToInt(marker[k])] = new Node();
    tempNode = tempNode->children[dnaToInt(marker[k])];
  }
  tempNode->ifEnd = true;

  //실패함수 매핑
  queue<Node*> Queue;

  //첫번째 레벨 node들의 fail은 루트로 지정해주고, Q에 넣기
  for(auto e: root->children){
    if(e == NULL) continue;
    e->fail = root;
    Queue.push(e);
  }

  while (!Queue.empty()) {
    Node* curNode = Queue.front();
    Queue.pop();

    //현재 노드의 자식들의 실패함수를 매핑해주기.
    for (int i = 0; i < 4; i++) {

      if(curNode->children[i] == NULL) continue;

      Node* curFail = curNode->fail;

      while (curFail != NULL && curFail->children[i] == NULL)
        curFail = curFail->fail;

      if (curFail != NULL){
        if(curFail->children[i]->ifEnd)
          curNode->children[i]->ifEnd = true;
        curNode->children[i]->fail = curFail->children[i];
      }
      else{
        curNode->children[i]->fail = root;
      }

      Queue.push(curNode->children[i]);
    }
  }

  //탐색 수행
  ll ans = 0;
  Node* curNode = root;
  for(int i = 0; i < n; i++){
    if(curNode->children[dnaToInt(dna[i])] != NULL){
      curNode = curNode->children[dnaToInt(dna[i])];
    }
    else{
      while(curNode->fail != NULL && curNode->children[dnaToInt(dna[i])] == NULL){
        curNode = curNode->fail;
        if(curNode->ifEnd) ans += 1;
      }

      if(curNode->children[dnaToInt(dna[i])] != NULL)
        curNode = curNode->children[dnaToInt(dna[i])];
      else
        curNode = root;
    }

    if(curNode->ifEnd) ans += 1;
  }

  cout << ans << "\n";
  delete root;
}

int main(){

  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  int T;
  cin >> T;

  for(int t = 0; t < T; t++)
    testCase();

  return 0;
}