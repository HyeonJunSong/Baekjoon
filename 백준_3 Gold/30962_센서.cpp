#include <iostream>
#include <vector>
#include <cmath>
#include <cstdio>
#include <climits>

using namespace std;

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  int Q;
  cin >> Q;
  for(int q = 0; q < Q; q++){
    long double x1, y1, x2, y2, w;
    cin >> x1 >> y1 >> x2 >> y2 >> w;

    int ans = 0;
    long double st = ceil(sqrt(w) * cos(atan(y1 / x1)) - 0.0000000001);
    long double ed = floor(sqrt(w) * cos(atan(y2 / x2)) + 0.0000000001);
    for(long double x = st; x <= ed; x += (long double)1)
      if(ceil(sqrt((w - x * x))) == floor(sqrt((w - x * x)))) ans++;
    
    cout << ans << '\n';
  }

  return 0;
}