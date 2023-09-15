////230915
//43m 06s

#include <iostream>
#include <vector>
#include <queue>
#include <cmath>

using namespace std;

vector<vector<int>> graph;

class node{
public:
  int visited;
  int cur;
  int costSum;

  bool operator< (node b) const{
    return costSum > b.costSum;
  }
};

int main(){

  int N;
  cin >> N;

  graph = vector<vector<int>>(N, vector<int>(N));
  for(int i = 0; i < N; i++)
    for(int j = 0; j < N; j++)
      cin >> graph[i][j];
  
  priority_queue<node> PQ;

  PQ.push({1, 0, 0});

  int oneLeft = (int)(pow(2, N)) - 1;
  int endVisited = (int)(pow(2, N));

  while(!PQ.empty()){
    node curNode = PQ.top();
    PQ.pop();

    if(curNode.visited == endVisited){
      cout << curNode.costSum + graph[curNode.cur][0];
      break;
    }

    for(int i = 0; i < N; i++){
      if(graph[curNode.cur][i] != 0 && ((curNode.visited & (int)(pow(2, i))) == 0)){
        PQ.push({(curNode.visited | (int)(pow(2, i))), i, curNode.costSum + graph[curNode.cur][i]});
      }
      if(curNode.visited == oneLeft && graph[curNode.cur][0] != 0){
        PQ.push({endVisited, 0, curNode.costSum + graph[curNode.cur][0]});
      }
    }
  }

  return 0;
}