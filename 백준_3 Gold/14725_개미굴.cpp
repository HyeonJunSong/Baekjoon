////230317
//이해 및 설계 : 4m 15s
//입력 : 12m 30s
//구현 : 5m 46s

//tot : 22m 31s

#include <iostream>
#include <string>
#include <map>

using namespace std;

class node{
public:
    map<string, node*> children;
    node(){}
};

void printTree(node* curNode, int depth, string food);

int main(){

    int N;
    cin >> N;

    node* tree = new node();

    int K;
    string inp;
    for(int i = 0; i < N; i++){
        node* curNode = tree;
        cin >> K;
        for(int j = 0; j < K; j++){
            cin >> inp;
            if(curNode->children.find(inp) != curNode->children.end()){
                curNode = curNode->children[inp];
            }
            else{
                curNode->children[inp] = new node();
                curNode = curNode->children[inp];
            }
        }
    }


    for(auto iter = tree->children.begin(); iter != tree->children.end(); iter++){
        printTree(iter->second, 0, iter->first);
    }

    return 0;
}

void printTree(node* curNode, int depth, string food){
    for(int i = 0; i < depth; i++)
        cout << "--";
    cout << food << '\n';

    for(auto iter = curNode->children.begin(); iter != curNode->children.end(); iter++){
        printTree(iter->second, depth + 1, iter->first);
    }
}