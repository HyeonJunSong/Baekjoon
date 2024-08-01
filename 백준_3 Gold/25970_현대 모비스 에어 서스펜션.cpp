#include <iostream>
#include <map>
#include <vector>
#include <string>

using namespace std;

class TriNode{
public:
  TriNode* left;
  TriNode* right;
  int cnt;

  TriNode(){
    left = nullptr;
    right = nullptr;
    cnt = 0;
  }

};

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  int B;
  cin >> B;
  vector<string> highs(B);
  for(int i = 0; i < B; i++)
    cin >> highs[i];
  vector<string> lows(B);
  for(int i = 0; i < B; i++)
    cin >> lows[i];
  
  int N;
  cin >> N;
  for(int t = 0; t < N; t++){

    string data;
    cin >> data;

    TriNode* root = new TriNode();
    for(int i = 0; i < data.size(); i++){
      TriNode* curNode = root;
      for(int j = i; j < data.size(); j++){
        if(data[j] == '0'){
          if(curNode->left == nullptr)
            curNode->left = new TriNode();
          curNode = curNode->left;
          curNode->cnt++;
        } else{
          if(curNode->right == nullptr)
            curNode->right = new TriNode();
          curNode = curNode->right;
          curNode->cnt++;
        }
      }
    }

    int highCnt = 0;
    for(int i = 0; i < B; i++){
      TriNode* curNode = root;
      for(int j = 0; j < highs[i].size(); j++){
        if(curNode == nullptr) break;
        if(highs[i][j] == '0') curNode = curNode->left;
        else curNode = curNode->right;
      }

      if(curNode == nullptr) continue;
      highCnt += curNode->cnt;
    }

    int lowCnt = 0;
    for(int i = 0; i < B; i++){
      TriNode* curNode = root;
      for(int j = 0; j < lows[i].size(); j++){
        if(curNode == nullptr) break;
        if(lows[i][j] == '0') curNode = curNode->left;
        else curNode = curNode->right;
      }

      if(curNode == nullptr) continue;
      lowCnt += curNode->cnt;
    }

    if(highCnt > lowCnt)
      cout << "HIGH " << highCnt - lowCnt << "\n";
    else if (highCnt < lowCnt)
      cout << "LOW " << lowCnt - highCnt << "\n";
    else
      cout << "GOOD\n";
  }

  return 0;
}