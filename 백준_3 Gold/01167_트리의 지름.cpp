////23 03 06
//about 1h 20m

#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

vector<vector<pair<int, int>>> tree;

set<int> parents;
vector<int> longestTwoBranchSum;
int getDiameterOfTree();
int getFarthestBranch(int n);

int main(){
    int V;
    cin >> V;
    tree = vector<vector<pair<int, int>>>(V + 1, vector<pair<int, int>>());
    longestTwoBranchSum = vector<int>(V + 1, 0);

    int st, ed, w;
    for(int i = 0; i < V; i++){
        cin >> st;
        cin >> ed;
        while(ed != -1){
            cin >> w;
            tree[st].push_back(pair<int, int>(ed, w));
            cin >> ed;
        }
    }


    cout << getDiameterOfTree();
    return 0;
}

//find longest two branches from root
int getDiameterOfTree(){
    
    vector<int> rootBranchLengths;
    for(auto iter = tree[1].begin(); iter != tree[1].end(); iter++){
        rootBranchLengths.push_back(getFarthestBranch(iter->first) + iter->second);
    }

    int ans;

    switch(rootBranchLengths.size()){
        case 1:
            ans = rootBranchLengths[0];
        case 2:
            ans = rootBranchLengths[0] + rootBranchLengths[1];
        case 3:
            sort(rootBranchLengths.begin(), rootBranchLengths.end());
            ans = *(rootBranchLengths.end() - 1) + *(rootBranchLengths.end() - 2);
    }

    for(auto iter = longestTwoBranchSum.begin(); iter != longestTwoBranchSum.end(); iter++){
        if(ans < *iter)
            ans = *iter;
    }

    return ans;
}

int getFarthestBranch(int n){
   cout << n << ' ';
    parents.insert(n);

    vector<int> branch;
    for(auto iter = tree[n].begin(); iter != tree[n].end(); iter++){
        if(parents.find(iter->first) != parents.end()) continue;

        branch.push_back(getFarthestBranch(iter->first));
    }

    sort(branch.begin(), branch.end());
    switch(branch.size()){
    case 2:
        longestTwoBranchSum[n] = branch[0] + branch[1];
        break;
    case 3:
        longestTwoBranchSum[n] =  *(branch.end() - 1) + *(branch.end() - 2);
        break;
    }

    parents.erase(n);
    return branch.back();
}