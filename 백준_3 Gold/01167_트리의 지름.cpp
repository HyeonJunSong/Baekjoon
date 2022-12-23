#include <iostream>
#include <vector>
#include <set>
#include <map>

using namespace std;

vector<map<int, int>> tree;

int main() {
    int V;
    cin >> V;

    tree = vector<map<int, int>>(V, map<int, int>());

    vector<int> edgeNodes;


    for (int i = 0; i < V; i++) {
        int nodeNum;
        cin >> nodeNum;
        nodeNum--;

        int targetNode, edgeVal;
        cin >> targetNode;
        targetNode--;
        while (targetNode != -2) {
            cin >> edgeVal;
            tree[nodeNum][targetNode] = edgeVal;
            cin >> targetNode;
            targetNode--;
        }
        if (tree[nodeNum].size() == 1) edgeNodes.push_back(nodeNum);
    }

    int longest = 0;

    vector<int> maxVals(V, 0);

    vector<int> nextNodes;
    do{
        for(int i = 0; i < edgeNodes.size(); i++){
            maxVals[tree[edgeNodes[i]].begin()->first] = tree[edgeNodes[i]].begin()->second;

        }

    }while(nextNodes.size() != 0);


    cout << longest;

    return 0;
}