#include <iostream>
#include <vector>
#include <string>

using namespace std;

int N;
vector<string> words;
string ansString;
int strLen;

#define LL long long

class node{
public:

  LL cnt;
  vector<node*> next;

  node(){
    cnt = 0;
    next = vector<node*>(26, nullptr);
  }

};

node* tri = new node;

vector<LL> memo;

LL getCombNum(int curIdx){
  if(curIdx == strLen)
    return 1;
  
  LL ans = 0;
  node* curTri = tri;

  while(curIdx < strLen && curTri->next[ansString[curIdx] - 'a'] != nullptr){
    curTri = curTri->next[ansString[curIdx] - 'a'];
    curIdx++;

    if(memo[curIdx] == -1)
      memo[curIdx] = getCombNum(curIdx);
    
    ans = (ans + (memo[curIdx] * curTri->cnt)) % 1000000007;
  }

  return ans;
}

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);


  cin >> N;
  words = vector<string>(N);
  for(int i = 0; i < N; i++)
    cin >> words[i];
  cin >> ansString;
  strLen = ansString.size();

  for(auto e : words){
    node* curTri = tri;

    for(auto e2: e){
      if(curTri->next[e2 - 'a'] == nullptr)
        curTri->next[e2 - 'a'] = new node;
      curTri = curTri->next[e2 - 'a'];
      curTri->cnt++;
    }
  }

  memo = vector<LL>(strLen + 1, -1);

  cout << getCombNum(0);

  return 0;
}