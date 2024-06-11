#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

vector<pair<int, int>> primes;

void era(){

  primes.push_back({2, 0});
  for(int i = 3; i <= 100000; i++){

    bool ifPrime = true;
    for(auto e: primes){
      if(e.first > (int)(sqrt(i))) break;
      if(i % e.first == 0){
        ifPrime = false;
        break;
      }
    }
    if(ifPrime)
      primes.push_back({i, primes.back().second^1});
  }

}

vector<vector<int>> accumSum;
void accum(){
  accumSum = vector<vector<int>>(2, vector<int>(primes.size(), 0));
  for(int i = 0; i < 2; i++){
    accumSum[i][0] = primes[0].second ^ i ? -1 * primes[0].first : 3 * primes[0].first;
    for(int j = 1; j < primes.size(); j++)
      accumSum[i][j] = accumSum[i][j - 1] + (primes[j].second ^ i ? -1 * primes[j].first : 3 * primes[j].first);
  }
}

int main(){

  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  era();
  accum();

  int n, a, b;

  cin >> n;
  for(int i = 0; i < n; i++){
    cin >> a >> b;

    int st1 = 0;
    int ed1 = primes.size() - 1;
    while(st1 <= ed1){
      int mid = (st1 + ed1) >> 1;

      if(primes[mid].first < a)
        st1 = mid + 1;
      else
        ed1 = mid - 1;
    }

    int st2 = 0;
    int ed2 = primes.size() - 1;
    while(st2 <= ed2){
      int mid = (st2 + ed2) >> 1;

      if(primes[mid].first <= b)
        st2 = mid + 1;
      else
        ed2 = mid - 1;
    }

    if(st1 == primes.size()) cout << "0\n";
    else if(ed1 == -1)
      cout << accumSum[primes[st1].second][ed2] << "\n";
    else
      cout << accumSum[primes[st1].second][ed2] - accumSum[primes[st1].second][ed1] << "\n";
  }

  return 0;
}