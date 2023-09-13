////230913
//1h 1m 48s

#include <iostream>
#include <vector>

using namespace std;

class node{
public:
  int marvelNum;
  int marvelSum;
  vector<int> children;
  int childrenSum;
};

vector<node> tree;

void getMarvelSum(int rootInd){
  tree[rootInd].marvelSum = tree[rootInd].marvelNum;
  for(auto iter = tree[rootInd].children.begin(); iter != tree[rootInd].children.end(); iter++){
    getMarvelSum(*iter);
    tree[rootInd].marvelSum += tree[*iter].marvelSum;
  }
}

void getChildrenSum(int rootInd){
  tree[rootInd].childrenSum = 1;
  for(auto iter = tree[rootInd].children.begin(); iter != tree[rootInd].children.end(); iter++){
    getChildrenSum(*iter);
    tree[rootInd].childrenSum += tree[*iter].childrenSum;
  }
}

int getMinMoveNum(int rootInd){
  int minMoveNum = 0;

  for(auto iter = tree[rootInd].children.begin(); iter != tree[rootInd].children.end(); iter++){
    minMoveNum += getMinMoveNum(*iter);
    minMoveNum += abs(tree[*iter].childrenSum - tree[*iter].marvelSum);
  }

  return minMoveNum;
}

bool testCase(){
  int n;
  cin >> n;
  if(n == 0) return false;

  tree = vector<node>(n + 1);
  vector<bool> ifParentExist(n + 1, false);
  for(int i = 0; i < n; i++){
    int v, marvelNum, d;
    cin >> v >> marvelNum >> d;
    tree[v].marvelNum = marvelNum;
    tree[v].children = vector<int>(d);
    for(int i = 0; i < d; i++){
      cin >> tree[v].children[i];
      ifParentExist[tree[v].children[i]] = true;
    }
  }

  int root;
  for(int i = 1; i <= n; i++){
    if(!ifParentExist[i]){
      root = i;
      break;
    }
  }
  getMarvelSum(root);
  getChildrenSum(root);

  cout << getMinMoveNum(root) << endl;



  return true;
}

int main(){
  while(testCase());
  return 0;
}