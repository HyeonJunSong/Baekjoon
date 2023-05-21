#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

int main(){
    int k;
    cin >> k;
    vector<int> tree(pow(2, k + 1));

    for(int i = 2; i < pow(2, k + 1); i++)
        cin >> tree[i];


    int curStInd = pow(2, k);
    for(int i = 0; i < pow(2, k - 1); i++){
        if(tree[curStInd + i * 2] > tree[curStInd + i * 2 + 1])
            tree[curStInd + i * 2 + 1] = tree[curStInd + i * 2];
        else
            tree[curStInd + i * 2] = tree[curStInd + i * 2 + 1];
    }

    vector<int> sumTree = tree;

    for(int i = k - 1; i >= 1; i--){
        curStInd = pow(2, i);
        for(int j = 0; j < pow(2, i - 1); j++){
            if(tree[curStInd + j * 2] + sumTree[(curStInd + j * 2) * 2] > tree[curStInd + j * 2 + 1] + sumTree[(curStInd + j * 2 + 1) * 2])
                tree[curStInd + j * 2 + 1] = tree[curStInd + j * 2] + sumTree[(curStInd + j * 2) * 2] - sumTree[(curStInd + j * 2 + 1) * 2];
            else
                tree[curStInd + j * 2] = tree[curStInd + j * 2 + 1] + sumTree[(curStInd + j * 2 + 1) * 2] - sumTree[(curStInd + j * 2) * 2];

            sumTree[curStInd + j * 2] = tree[curStInd + j * 2] + sumTree[(curStInd + j * 2) * 2];
            sumTree[curStInd + j * 2 + 1] = tree[curStInd + j * 2] + sumTree[(curStInd + j * 2) * 2];
        }
    }

    int tot = 0;
    for(int i = 2; i < tree.size(); i++)
        tot += tree[i];
    cout << tot;


    return 0;
}