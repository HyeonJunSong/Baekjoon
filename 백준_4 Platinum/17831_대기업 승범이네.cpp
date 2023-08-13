////230812
//28m 21s

#include <iostream>
#include <vector>

using namespace std;

int N;
vector<pair<int, vector<int>>> tree;

vector<vector<int>> cache;

int getMaxSynergy(int ind, bool ifCurNodeAvailable){

  int maxSynergy = 0;

  //시너지 안맺었을 때
  int totChildSynergy = 0;
  for(auto iter = tree[ind].second.begin(); iter != tree[ind].second.end(); iter++){
    if(cache[*iter][1] == -1)
      cache[*iter][1] = getMaxSynergy(*iter, true);
    totChildSynergy += cache[*iter][1];
  }
  maxSynergy = totChildSynergy;

  //내 자식노드들과 시너지 맺었을 때
  if(ifCurNodeAvailable){
    for(auto iter = tree[ind].second.begin(); iter != tree[ind].second.end(); iter++){
      int curSynergy = 0;
      curSynergy += tree[ind].first * tree[*iter].first;

      if(cache[*iter][0] == -1)
        cache[*iter][0] = getMaxSynergy(*iter, false);
      curSynergy += cache[*iter][0];
      curSynergy += totChildSynergy - cache[*iter][1];

      if(maxSynergy < curSynergy)
        maxSynergy = curSynergy;
    }
  }

  //이 중에서 최고 값 리턴
  return maxSynergy;
}

int main(){

  cin >> N;
  tree = vector<pair<int, vector<int>>>(N + 1);

  for(int i = 2; i <= N; i++){
    int parent;
    cin >> parent;
    tree[parent].second.push_back(i);
  }
  for(int i = 1; i <= N; i++)
    cin >> tree[i].first;
    
  cache = vector<vector<int>>(N + 1, vector<int>(2, -1));

  cout << getMaxSynergy(1, true);
  return 0;
}