#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>

using namespace std;

class Node{
public:
  bool ifEnd;
  map<char, Node*> next;
};

int main(){

  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  int C, N;
  cin >> C >> N;

  Node* colorTriTree = new Node();
  for(int i = 0; i < C; i++){
    string color;
    cin >> color;

    Node* curTriNode = colorTriTree;
    for(auto e: color){
      if(curTriNode->next[e] == NULL)
        curTriNode->next[e] = new Node();
      curTriNode = curTriNode->next[e];
    }
    curTriNode->ifEnd = true;
  }

  Node* nameTriTree = new Node();
  for(int i = 0; i < N; i++){
    string name;
    cin >> name;
    reverse(name.begin(), name.end());

    Node* curTriNode = nameTriTree;
    for(auto e: name){
      if(curTriNode->next[e] == NULL)
        curTriNode->next[e] = new Node();
      curTriNode = curTriNode->next[e];
    }
    curTriNode->ifEnd = true;
  }


  int Q;
  cin >> Q;
  for(int q = 0; q < Q; q++){
    string teamName;
    cin >> teamName;

    vector<pair<bool, bool>> ifEnded(teamName.size(), {false, false});

    Node* colorNode = colorTriTree;
    for(int i = 0; i < teamName.size(); i++){
      if(colorNode->next[teamName[i]] == NULL) break;
      colorNode = colorNode->next[teamName[i]];
      if(colorNode->ifEnd) ifEnded[i].first = true;
    }

    Node* nameNode = nameTriTree;
    for(int i = 0; i < teamName.size(); i++){
      if(nameNode->next[teamName[teamName.size() - i - 1]] == NULL) break;
      nameNode = nameNode->next[teamName[teamName.size() - i - 1]];
      if(nameNode->ifEnd) ifEnded[teamName.size() - i - 1].second = true;
    }

    bool ifSooSang = false;
    for(int i = 0; i < teamName.size() - 1; i++){
      if(ifEnded[i].first && ifEnded[i + 1].second){
        ifSooSang = true;
        break;
      }
    }

    if(ifSooSang)
      cout << "Yes\n";
    else
      cout << "No\n";
  }

  return 0;
}