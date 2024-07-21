#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <map>

using namespace std;

class Node{
public:
    Node* l;
    Node* r;
    int st, ed;
    int val;
};

Node* segRoot;
vector<Node*> segRootOf;

void segInit(Node* curNode, int st, int ed){
    curNode->l = nullptr;
    curNode->r = nullptr;
    curNode->st = st;
    curNode->ed = ed;
    curNode->val = 0;
    if(st == ed) return;

    curNode->l = new Node();
    curNode->r = new Node();
    segInit(curNode->l, st, ((st + ed) >> 1));
    segInit(curNode->r, ((st + ed) >> 1) + 1, ed);
}

void segUpdate(Node* prvNode, Node* curNode, int target){

    curNode->l = prvNode->l;
    curNode->r = prvNode->r;
    curNode->st = prvNode->st;
    curNode->ed = prvNode->ed;
    curNode->val = prvNode->val + 1;

    if(curNode->st == curNode->ed){
        return;
    }

    if(target <= prvNode->l->ed){
        curNode->l = new Node();
        segUpdate(prvNode->l, curNode->l, target);
    } else {
        curNode->r = new Node();
        segUpdate(prvNode->r, curNode->r, target);
    }

    return;
}

int segGetVal(Node* lca, Node* lcaP, Node* a, Node* b, int k){
    if(lca->st == lca->ed) return lca->st;

    if(a->l->val + b->l->val - lca->l->val - lcaP->l->val >= k)
        return segGetVal(lca->l, lcaP->l, a->l, b->l, k);
    else
        return segGetVal(lca->r, lcaP->r, a->r, b->r, k - (a->l->val + b->l->val - lca->l->val - lcaP->l->val));
}

int N;
vector<int> valOf;
vector<vector<int>> graph;
vector<int> levelOf;
vector<vector<int>> parentOf;
void treeInit(int cur, int level, vector<int>& parentStack){

    segRootOf[cur] = new Node();
    if(cur == 1)
        segUpdate(segRoot, segRootOf[cur], valOf[cur]);
    else 
        segUpdate(segRootOf[parentStack.back()], segRootOf[cur], valOf[cur]);

    levelOf[cur] = level;

    for(int i = 1; i <= parentStack.size(); i *= 2)
        parentOf[cur].push_back(parentStack[parentStack.size() - i]);
    
    parentStack.push_back(cur);
    for(auto e: graph[cur]){
        if(parentStack.size() > 1 && e == parentStack[parentStack.size() - 2]) continue;
        treeInit(e, level + 1, parentStack);
    }
    parentStack.pop_back();
}
int lca(int a, int b){

    while(levelOf[a] > levelOf[b])
        a = parentOf[a][(int)(log2(levelOf[a] - levelOf[b]))];
    while(levelOf[b] > levelOf[a])
        b = parentOf[b][(int)(log2(levelOf[b] - levelOf[a]))];
    
    while(a != b){
        int st = 0;
        int ed = parentOf[a].size() - 1;

        while(st <= ed){
            int mid = (st + ed) / 2;
            if(parentOf[a][mid] != parentOf[b][mid])
                st = mid + 1;
            else
                ed = mid - 1;
        }

        if(ed == -1) ed = 0;

        a = parentOf[a][ed];
        b = parentOf[b][ed];
    }
    return a;
}

// void segPrint(Node* curNode){
//     cout << curNode->st << " " << curNode->ed << " " << curNode->val << " " << "\n";
//     if(curNode->l == nullptr) return;
//     segPrint(curNode->l);
//     segPrint(curNode->r);
// }

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int M;
    cin >> N >> M;
    valOf.assign(N + 1, 0);
    map<int, int> vals;
    for(int i = 1; i <= N; i++){
        cin >> valOf[i];
        vals[valOf[i]] = 0;
    }
    int valsSize = 0;
    for(auto e: vals)
        vals[e.first] = valsSize++;
    
    vector<int> originValOf(valsSize);
    for(int i = 1; i <= N; i++)
        originValOf[vals[valOf[i]]] = valOf[i];

    for(int i = 1; i <= N; i++)
        valOf[i] = vals[valOf[i]];
    
    
    graph.assign(N + 1, {});
    for(int i = 0; i < N - 1; i++){
        int st, ed;
        cin >> st >> ed;
        graph[st].push_back(ed);
        graph[ed].push_back(st);
    }

    segRoot = new Node();
    segInit(segRoot, 0, valsSize - 1);
    segRootOf.assign(N + 1, nullptr);

    levelOf.assign(N + 1, 0);
    parentOf.assign(N + 1, {});

    vector<int> parentStack;
    treeInit(1, 1, parentStack);

    // segPrint(segRootOf[4]);

    for(int i = 0; i < M; i++){
        int X, Y, K;
        cin >> X >> Y >> K;

        int curLCA = lca(X, Y);

        cout << originValOf[segGetVal(segRootOf[curLCA], (curLCA == 1 ? segRoot : segRootOf[parentOf[curLCA][0]]), segRootOf[X], segRootOf[Y], K)] << "\n";
    }

    return 0;
}