#include <iostream>
#include <vector>

using namespace std;

#define ll long long

vector<ll> runTime;

ll getPeopleNum(ll time);

int main(){

  ll N, M;
  cin >> N >> M;

  runTime = vector<ll>(M);
  for(int i = 0; i < M; i++)
    cin >> runTime[i];

  ll st = 0;
  ll ed = 60000000000;
  
  while(st <= ed){
    ll mid = (st + ed) / 2;

    if(getPeopleNum(mid) < N)
      st = mid + 1;
    else
      ed = mid - 1;
  }

  ll curPeopleNum = getPeopleNum(st);
  for(int i = runTime.size() - 1; i > -1; i--){
    if(st % runTime[i] != 0) continue;

    if(curPeopleNum == N){
      cout << i + 1;
      break;
    }

    curPeopleNum--;
  }

  return 0;
}

ll getPeopleNum(ll time){

  ll peopleNum = 0;
  for(auto e: runTime)
    peopleNum += (time / e) + 1;
  
  return peopleNum;
}