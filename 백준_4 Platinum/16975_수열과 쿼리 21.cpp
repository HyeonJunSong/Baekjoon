#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

vector<pair<long long, pair<int, int>>> tree;

void initTree(int& N, vector<long long>& inpArr){
  ////init leafNum
  int leafNum = 1;
  while(leafNum < N) leafNum *= 2;

  ////init Tree
  tree = vector<pair<long long, pair<int, int>>>(leafNum * 2);
  
  //leaf init
  for(int i = 0; i < N; i++){
    tree[leafNum + i].first = inpArr[i];
    tree[leafNum + i].second.first = i;
    tree[leafNum + i].second.second = i + 1;
  }
  for(int i = leafNum + N; i < leafNum * 2; i++){
    tree[i].first = 0;
    tree[i].second.first = i - leafNum;
    tree[i].second.second = i - leafNum + 1;
  }

  //middle init
  for(int i = leafNum - 1; i > 0; i--){
    tree[i].first = 0;
    tree[i].second.first = tree[2 * i].second.first;
    tree[i].second.second = tree[2 * i + 1].second.second;
  }
}

void query1(int i, int j, int curTreeInd, long long val){

  //범위 일치
  if(i == tree[curTreeInd].second.first && j == tree[curTreeInd].second.second - 1){
    tree[curTreeInd].first += val;
    return;
  }

  //왼쪽일때
  if(j < tree[2 * curTreeInd].second.second)
    return query1(i, j, 2 * curTreeInd, val);
  
  //오른쪽일때
  if(i >= tree[2 * curTreeInd + 1].second.first)
    return query1(i, j, 2 * curTreeInd + 1, val);
  
  query1(i, tree[2 * curTreeInd].second.second - 1, 2 * curTreeInd, val);
  query1(tree[2 * curTreeInd + 1].second.first, j, 2 * curTreeInd + 1, val);
  return;
}

void query2(int curTreeInd, int targetInd){

  if(curTreeInd * 2 >= tree.size()){
    cout << tree[curTreeInd].first << '\n';
    return;
  }

  if(tree[curTreeInd].first != 0){
    tree[2 * curTreeInd].first += tree[curTreeInd].first;
    tree[2 * curTreeInd + 1].first += tree[curTreeInd].first;
    tree[curTreeInd].first = 0;
  }

  //왼쪽일때
  if(targetInd < tree[2 * curTreeInd].second.second)
    query2(2 * curTreeInd, targetInd);
  else
    query2(2 * curTreeInd + 1, targetInd);

}

int main(){

  ios_base :: sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  int N;
  cin >> N;
  vector<long long> inpArr(N);
  for(int i = 0; i < N; i++)
    cin >> inpArr[i];
  
  initTree(N, inpArr);
  
  int M;
  cin >> M;
  for(int i = 0; i < M; i++){
    int query;
    cin >> query;
    if(query == 1){
      int i, j;
      long long k;
      cin >> i >> j >> k;
      query1(i - 1, j - 1, 1, k);
    }
    else{
      int x;
      cin >> x;
      query2(1, x - 1);
    }
  }

  return 0;
}