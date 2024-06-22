#include <iostream>
#include <cmath>
#include <cstdio>
#include <climits>

using namespace std;

#define ll long long

void testCase(ll n){
  
  ll minSum = LLONG_MAX;
  ll minA = 0;
  ll minB = 0;
  ll minC = 0;
  for(ll a = 3999; a > 0; a--){
    for(ll b = 1; b <= a; b++){
      ll cCub = (n * (b * b * b) - (a * a * a));
      if(cCub <= 0) continue;

      ll st = 1;
      ll ed = a;
      
      while(st <= ed){
        ll mid = (st + ed) >> 1;
        if(mid * mid * mid <= cCub)
          st = mid + 1;
        else
          ed = mid - 1;
      }

      if(ed * ed * ed == cCub){
        if(a + b + ed + b < minSum){
          minSum = a + b + ed + b;
          minA = a;
          minB = b;
          minC = ed;
        }
      }
    }
  }
  
  if(minSum == LLONG_MAX)
    cout << "No value.\n";
  else
    cout << '(' << minA << '/' << minB << ")^3 + (" << minC << '/' << minB << ")^3 = " << n << '\n';
  return;
}

int main(){
  
  while(true){
    ll inp;
    cin >> inp;
    if(inp == 0) break;
    testCase(inp);
  }

  return 0;
}