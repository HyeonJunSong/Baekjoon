#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

class Node{
public:
  char word;
  int idx;
  vector<Node*> nodeOf2s;

  Node(char word, Node* lastNode){
    this->word = word;

    if(lastNode == nullptr)
      this->idx = 0;
    else
      this->idx = lastNode->idx + 1;

    while(lastNode != nullptr){
      nodeOf2s.push_back(lastNode);
      if(lastNode->nodeOf2s.size() < nodeOf2s.size())
        break;
      lastNode = lastNode->nodeOf2s[nodeOf2s.size() - 1];
    }
  }

};

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  int L;
  cin >> L;

  vector<Node*> cmdStack;

  for(int l = 0; l < L; l++){
    char cmd;
    cin >> cmd;

    if(cmd == 'T'){
      char letter;
      cin >> letter;

      Node* newNode;
      if(cmdStack.size() == 0)
        newNode = new Node(letter, nullptr);
      else
        newNode = new Node(letter, cmdStack.back());

      cmdStack.push_back(newNode);
    } else if(cmd == 'U'){
      int undoNum;
      cin >> undoNum;

      cmdStack.push_back(cmdStack[cmdStack.size() - 1 - undoNum]);
    } else if(cmd == 'P'){
      int printIdx;
      cin >> printIdx;

      Node* curNode = cmdStack.back();
      int idxLeft = curNode->idx - printIdx;
      while(idxLeft > 0){
        curNode = curNode->nodeOf2s[(int)(floor(log2(idxLeft)))];
        idxLeft -= (int)(pow(2, floor(log2(idxLeft))));
      }

      cout << curNode->word << "\n";
    }
  }
  return 0;
}