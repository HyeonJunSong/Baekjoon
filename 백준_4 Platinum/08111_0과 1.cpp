#include <iostream>
#include <vector>
#include <queue>
#include <set>

using namespace std;

vector<vector<vector<int>>> mulMap;

int num;

class Node{
public:
  int curRes;
  int depth;
  bool ifOneAppeared;
  vector<int> ans;
};

vector<int> getAns(int curRes, int depth, bool ifOneAppeared){

  queue<Node> Q;
  Q.push({curRes, depth, ifOneAppeared, vector<int>()});

  vector<set<int>> memo(2);

  while(!Q.empty()){
    Node curNode = Q.front();
    Q.pop();
    if(memo[curNode.ifOneAppeared].find(curNode.curRes) != memo[curNode.ifOneAppeared].end()) continue;
    memo[curNode.ifOneAppeared].insert(curNode.curRes);

    if(curNode.depth > 100)
      continue;

    if(curNode.ifOneAppeared && curNode.curRes == 0)
      return curNode.ans;
    
    curNode.ans.push_back(1);
    for(auto e : mulMap[num % 10][(11 - curNode.curRes % 10) % 10]){
      if(memo[true].find((curNode.curRes + num * e) / 10) != memo[true].end()) continue;
      Q.push({
        (curNode.curRes + num * e) / 10, curNode.depth + 1, true, curNode.ans
      });
    }
    curNode.ans.pop_back();

    curNode.ans.push_back(0);
    for(auto e: mulMap[num % 10][(10 - curNode.curRes % 10) % 10]){
      if(memo[curNode.ifOneAppeared].find((curNode.curRes + num * e) / 10) != memo[curNode.ifOneAppeared].end()) continue;
      Q.push({ (curNode.curRes + num * e) / 10, curNode.depth + 1, curNode.ifOneAppeared, curNode.ans});
    }
    curNode.ans.pop_back();
  }

  return vector<int>();
}



int main(){

  mulMap = vector<vector<vector<int>>>(10, vector<vector<int>>(10));
  for(int i = 0; i < 10; i++)
    for(int j = 0; j < 10; j++)
      mulMap[i][(i * j) % 10].push_back(j);
    
  int T;
  cin >> T;
  for(int t = 0; t < T; t++){
    cin >> num;
    vector<int> ans = getAns(0, 0, false);
    for(auto iter = ans.rbegin(); iter != ans.rend(); iter++) cout << *iter;
    cout << "\n";
  }

  return 0;
}

