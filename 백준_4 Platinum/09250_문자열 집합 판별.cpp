#include <iostream>
#include <string>
#include <vector>
#include <queue>

using namespace std;

class Node {
public:

    bool ifEnd;
    vector<Node*> children;
    Node* fail;

    Node() {
        ifEnd = false;
        for (int i = 0; i < 26; i++)
            children = vector<Node*>(26, NULL);
        fail = NULL;
    }
};

int main() {

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int N;
    cin >> N;

    //트라이 트리 구축
    Node* root = new Node();
    for (int i = 0; i < N; i++) {
        string str;
        cin >> str;

        Node* curNode = root;
        for (int j = 0; j < str.size(); j++) {
            if (curNode->children[str[j] - 'a'] == NULL)
                curNode->children[str[j] - 'a'] = new Node();
            curNode = curNode->children[str[j] - 'a'];
        }
        curNode->ifEnd = true;
    }

    //실패함수 매핑
    queue<Node*> Queue;

    //첫번째 레벨 node들의 fail은 루트로 지정해주고, Q에 넣기
    for(int i = 0; i < 26; i++){
      if(root->children[i] == NULL) continue;
      
      root->children[i]->fail = root;
      Queue.push(root->children[i]);
    }

    while (!Queue.empty()) {
        Node* curNode = Queue.front();
        Queue.pop();

        //현재 노드의 자식들의 실패함수를 매핑해주기.
        for (int i = 0; i < 26; i++) {
            if (curNode->children[i] == NULL) continue;

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
    int Q;
    cin >> Q;
    for(int i = 0; i < Q; i++){
      string str;
      cin >> str;

      Node* curNode = root;
      for(int j = 0; j < str.size(); j++){        
        if(curNode->children[str[j] - 'a'] != NULL){
          curNode = curNode->children[str[j] - 'a'];
        }
        else{
          if(curNode->fail == NULL){
            curNode = root;
          } else{
            curNode = curNode->fail;
            j--;
          }
        }

        if(curNode->ifEnd){
          break;
        }
      }

      if(curNode->ifEnd)
        cout << "YES\n";
      else
        cout << "NO\n";
    }


    return 0;
}